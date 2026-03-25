#include "music_app.h"
#include <ui.h>
#include <images.h>
#include <lvgl.h>
#include <Arduino.h>
#include <M5Cardputer.h>
#include <config_manager.h>
#include <SD.h>
#include <MP3DecoderHelix.h>
#include <driver/i2s_std.h>

// I2S pins for M5Cardputer
#define I2S_DOUT_PIN 42
#define I2S_BCLK_PIN 41
#define I2S_LRCK_PIN 43

// ============================================================
// LVGL timer callback
// ============================================================

void MusicApp::animTimerCb(lv_timer_t* t) {
    MusicApp* self = (MusicApp*)lv_timer_get_user_data(t);
    if (self) self->onAnimUpdate();
}

// ============================================================
// I2S setup / teardown
// ============================================================

void MusicApp::setupI2S(uint32_t sample_rate, bool stereo) {
    teardownI2S();

    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.dma_desc_num = 8;
    chan_cfg.dma_frame_num = 256;
    i2s_new_channel(&chan_cfg, &_i2s_tx, NULL);

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sample_rate),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(
            I2S_DATA_BIT_WIDTH_16BIT,
            stereo ? I2S_SLOT_MODE_STEREO : I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = (gpio_num_t)I2S_BCLK_PIN,
            .ws = (gpio_num_t)I2S_LRCK_PIN,
            .dout = (gpio_num_t)I2S_DOUT_PIN,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = { .mclk_inv = false, .bclk_inv = false, .ws_inv = false },
        },
    };

    i2s_channel_init_std_mode(_i2s_tx, &std_cfg);
    i2s_channel_enable(_i2s_tx);
    _i2s_running = true;
}

void MusicApp::teardownI2S() {
    if (_i2s_tx) {
        if (_i2s_running) {
            i2s_channel_disable(_i2s_tx);
            _i2s_running = false;
        }
        i2s_del_channel(_i2s_tx);
        _i2s_tx = nullptr;
    }
}

// ============================================================
// MP3 decoder + I2S write
// ============================================================

static libhelix::MP3DecoderHelix* s_mp3 = nullptr;
static i2s_chan_handle_t s_i2s_tx = nullptr;
static int16_t s_volume = 16;
static volatile bool s_first_frame = true;

static void mp3DataCb(MP3FrameInfo &info, short *pcm, size_t len, void *ref) {
    if (len == 0 || !s_i2s_tx) return;

    if (s_first_frame) {
        i2s_channel_disable(s_i2s_tx);
        i2s_std_clk_config_t clk = I2S_STD_CLK_DEFAULT_CONFIG(info.samprate);
        i2s_channel_reconfig_std_clock(s_i2s_tx, &clk);
        i2s_channel_enable(s_i2s_tx);
        s_first_frame = false;
        Serial.printf("[MUSIC] MP3: %dHz %dch %dkbps\n",
                      info.samprate, info.nChans, info.bitrate / 1000);
    }

    for (size_t i = 0; i < len; i++) {
        pcm[i] = (int32_t)pcm[i] * s_volume / 21;
    }

    size_t bytes_written;
    i2s_channel_write(s_i2s_tx, pcm, len * sizeof(short), &bytes_written, pdMS_TO_TICKS(100));
}

// ============================================================
// Audio decode/feed task (Core 0)
// ============================================================

void MusicApp::audioTaskFunc(void* param) {
    MusicApp* self = (MusicApp*)param;
    uint8_t buf[1024];

    while (self->_audio_task_run) {
        if (!self->_playing || !self->_active || self->_data_remaining <= 0) {
            vTaskDelay(10);
            continue;
        }

        if (self->_track_type == TRACK_MP3) {
            size_t to_read = (self->_data_remaining < (int32_t)sizeof(buf))
                           ? self->_data_remaining : sizeof(buf);
            size_t rd = self->_file.read(buf, to_read);
            if (rd > 0) {
                self->_data_remaining -= rd;
                if (s_mp3) s_mp3->write(buf, rd);
            }
        } else if (self->_track_type == TRACK_WAV) {
            size_t to_read = (self->_data_remaining < (int32_t)sizeof(buf))
                           ? self->_data_remaining : sizeof(buf);
            size_t rd = self->_file.read(buf, to_read);
            if (rd > 0) {
                self->_data_remaining -= rd;
                if (!self->_wav_16bit) {
                    int16_t tmp[512];
                    for (size_t i = 0; i < rd; i++) {
                        tmp[i] = ((int16_t)buf[i] - 128) * s_volume * 256 / 21;
                    }
                    size_t written;
                    i2s_channel_write(self->_i2s_tx, tmp, rd * 2, &written, pdMS_TO_TICKS(100));
                } else {
                    int16_t* samples = (int16_t*)buf;
                    size_t count = rd / 2;
                    for (size_t i = 0; i < count; i++) {
                        samples[i] = (int32_t)samples[i] * s_volume / 21;
                    }
                    size_t written;
                    i2s_channel_write(self->_i2s_tx, buf, rd, &written, pdMS_TO_TICKS(100));
                }
            }
        }

        // Track finished
        if (self->_data_remaining <= 0) {
            self->_active = false;
            self->_file.close();
            if (self->_track_type == TRACK_MP3 && s_mp3) s_mp3->end();
            self->_track_type = TRACK_NONE;
        }

        vTaskDelay(1);
    }
    vTaskDelete(NULL);
}

// ============================================================
// ID3v2 helpers
// ============================================================

static uint32_t id3_syncsafe(const uint8_t b[4]) {
    return ((uint32_t)b[0] << 21) | ((uint32_t)b[1] << 14) |
           ((uint32_t)b[2] << 7)  | (uint32_t)b[3];
}
static uint32_t id3_be32(const uint8_t b[4]) {
    return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) |
           ((uint32_t)b[2] << 8)  | (uint32_t)b[3];
}

// Read a null-terminated ID3 text frame value into dst (skips encoding byte)
static void id3_read_text(File &f, uint32_t frame_size, char* dst, size_t dst_size) {
    dst[0] = '\0';
    if (frame_size < 2) { f.seek(frame_size, SeekCur); return; }

    uint8_t enc;
    f.read(&enc, 1);
    uint32_t text_len = frame_size - 1;
    if (text_len >= dst_size) text_len = dst_size - 1;

    if (enc == 0 || enc == 3) {
        // ISO-8859-1 or UTF-8
        f.read((uint8_t*)dst, text_len);
        dst[text_len] = '\0';
    } else {
        // UTF-16: skip BOM, read and simplify to ASCII
        uint8_t bom[2];
        f.read(bom, 2);
        text_len -= 2;
        size_t out = 0;
        for (uint32_t i = 0; i < text_len / 2 && out < dst_size - 1; i++) {
            uint8_t lo, hi;
            f.read(&lo, 1);
            f.read(&hi, 1);
            if (lo && !hi) dst[out++] = (char)lo;
            else if (lo || hi) dst[out++] = '?';
        }
        dst[out] = '\0';
    }
}

void MusicApp::extractID3Meta(int track_idx) {
    _artist[0] = '\0';
    _album[0] = '\0';
    if (track_idx < 0 || track_idx >= _track_count) return;

    const char* name = _track_names[track_idx];
    size_t nlen = strlen(name);
    if (nlen < 4 || strcasecmp(name + nlen - 4, ".mp3") != 0) return;

    char path[128];
    snprintf(path, sizeof(path), "%s/%s", MUSIC_PATH, name);
    File f = SD.open(path, FILE_READ);
    if (!f) return;

    uint8_t hdr[10];
    if (f.read(hdr, 10) != 10 || memcmp(hdr, "ID3", 3) != 0) { f.close(); return; }

    uint8_t ver = hdr[3];
    if (ver < 3) { f.close(); return; }

    uint32_t tag_size = id3_syncsafe(&hdr[6]);
    uint32_t pos = 10, tag_end = 10 + tag_size;

    while (pos + 10 <= tag_end) {
        uint8_t fh[10];
        if (f.read(fh, 10) != 10) break;
        pos += 10;
        if (fh[0] == 0) break;

        uint32_t fsz = (ver == 4) ? id3_syncsafe(&fh[4]) : id3_be32(&fh[4]);
        if (fsz == 0 || pos + fsz > tag_end) break;

        if (memcmp(fh, "TPE1", 4) == 0) {
            id3_read_text(f, fsz, _artist, sizeof(_artist));
        } else if (memcmp(fh, "TALB", 4) == 0) {
            id3_read_text(f, fsz, _album, sizeof(_album));
        } else {
            f.seek(fsz, SeekCur);
        }
        pos += fsz;

        // Stop early if we have both
        if (_artist[0] && _album[0]) break;
    }
    f.close();
}

// ============================================================
// Next track index (handles shuffle)
// ============================================================

int MusicApp::nextTrackIndex() {
    if (_track_count <= 1) return 0;
    if (_shuffle) {
        int next;
        do { next = random(0, _track_count); } while (next == _current_track);
        return next;
    }
    return (_current_track + 1) % _track_count;
}

// ============================================================
// Track scanning
// ============================================================

void MusicApp::scanTracks() {
    _track_count = 0;
    _current_track = 0;

    File dir = SD.open(MUSIC_PATH);
    if (!dir || !dir.isDirectory()) {
        Serial.printf("[MUSIC] Failed to open %s\n", MUSIC_PATH);
        return;
    }

    while (_track_count < MAX_TRACKS) {
        File entry = dir.openNextFile();
        if (!entry) break;
        if (entry.isDirectory()) { entry.close(); continue; }

        const char* name = entry.name();
        if (name[0] == '.' || name[0] == '_') { entry.close(); continue; }

        size_t len = strlen(name);
        bool valid = false;
        if (len > 4) {
            const char* ext = name + len - 4;
            valid = (strcasecmp(ext, ".wav") == 0 || strcasecmp(ext, ".mp3") == 0);
        }
        if (!valid && len > 5) {
            const char* ext = name + len - 5;
            valid = (strcasecmp(ext, ".flac") == 0);
        }

        if (valid) {
            strncpy(_track_names[_track_count], name, 63);
            _track_names[_track_count][63] = '\0';
            _track_count++;
        }
        entry.close();
    }

    dir.close();
    Serial.printf("[MUSIC] Found %d tracks\n", _track_count);
}

// ============================================================
// Track opening
// ============================================================

bool MusicApp::openTrack(int track_idx) {
    if (track_idx < 0 || track_idx >= _track_count) return false;
    const char* name = _track_names[track_idx];
    size_t len = strlen(name);
    if (len > 4 && strcasecmp(name + len - 4, ".mp3") == 0)
        return openMp3(track_idx);
    return openWav(track_idx);
}

bool MusicApp::openWav(int track_idx) {
    stopPlayback();
    if (track_idx < 0 || track_idx >= _track_count) return false;

    char path[128];
    snprintf(path, sizeof(path), "%s/%s", MUSIC_PATH, _track_names[track_idx]);
    _file = SD.open(path);
    if (!_file) return false;

    wav_header_t hdr;
    if (_file.read((uint8_t*)&hdr, sizeof(hdr)) != sizeof(hdr)) { _file.close(); return false; }

    if (memcmp(hdr.RIFF, "RIFF", 4) || memcmp(hdr.WAVEfmt, "WAVEfmt ", 8) ||
        hdr.audiofmt != 1 || hdr.bit_per_sample < 8 || hdr.bit_per_sample > 16 ||
        hdr.channel == 0 || hdr.channel > 2) {
        _file.close(); return false;
    }

    _wav_16bit = (hdr.bit_per_sample == 16);
    _wav_stereo = (hdr.channel > 1);
    _wav_sample_rate = hdr.sample_rate;

    _file.seek(offsetof(wav_header_t, audiofmt) + hdr.fmt_chunk_size);
    sub_chunk_t sub;
    _file.read((uint8_t*)&sub, sizeof(sub));
    while (memcmp(sub.identifier, "data", 4)) {
        if (!_file.seek(sub.chunk_size, SeekMode::SeekCur)) break;
        if (_file.read((uint8_t*)&sub, sizeof(sub)) != sizeof(sub)) break;
    }
    if (memcmp(sub.identifier, "data", 4)) { _file.close(); return false; }

    _data_remaining = sub.chunk_size;
    _data_total = sub.chunk_size;
    _active = true;
    _track_type = TRACK_WAV;
    _play_start_ms = millis();
    _pause_elapsed_ms = 0;

    setupI2S(_wav_sample_rate, _wav_stereo);
    return true;
}

bool MusicApp::openMp3(int track_idx) {
    stopPlayback();
    if (track_idx < 0 || track_idx >= _track_count) return false;

    char path[128];
    snprintf(path, sizeof(path), "%s/%s", MUSIC_PATH, _track_names[track_idx]);
    _file = SD.open(path, FILE_READ);
    if (!_file) return false;

    uint8_t hdr[10];
    if (_file.read(hdr, 10) == 10 && memcmp(hdr, "ID3", 3) == 0) {
        uint32_t tag_size = id3_syncsafe(&hdr[6]);
        _file.seek(10 + tag_size);
    } else {
        _file.seek(0);
    }

    _data_remaining = _file.size() - _file.position();
    _data_total = _data_remaining;
    _active = true;
    _track_type = TRACK_MP3;
    _play_start_ms = millis();
    _pause_elapsed_ms = 0;
    s_first_frame = true;

    setupI2S(44100, true);
    s_i2s_tx = _i2s_tx;

    if (!s_mp3) s_mp3 = new libhelix::MP3DecoderHelix();
    s_mp3->setDataCallback(mp3DataCb);
    s_mp3->begin();

    Serial.printf("[MUSIC] Playing: %s\n", _track_names[track_idx]);
    return true;
}

void MusicApp::stopPlayback() {
    _active = false;
    _playing = false;

    // Disable I2S to unblock any i2s_channel_write() stuck in audio task
    if (_i2s_tx && _i2s_running) {
        i2s_channel_disable(_i2s_tx);
        _i2s_running = false;
    }

    // Wait for audio task to exit its read/write loop
    vTaskDelay(pdMS_TO_TICKS(50));

    if (_track_type == TRACK_MP3 && s_mp3) s_mp3->end();
    _track_type = TRACK_NONE;
    if (_file) _file.close();
    _pause_elapsed_ms = 0;
}

void MusicApp::seekRelative(int seconds) {
    if (!_active || _data_total == 0) return;

    // Stop audio task's read loop first
    bool was_playing = _playing;
    _playing = false;

    // Disable I2S to unblock any stuck i2s_channel_write
    if (_i2s_tx && _i2s_running) {
        i2s_channel_disable(_i2s_tx);
        _i2s_running = false;
    }

    // Wait for audio task to fully exit its read/write iteration
    vTaskDelay(pdMS_TO_TICKS(30));

    // Calculate byte offset for the seek
    int32_t consumed = _data_total - _data_remaining;
    int32_t byte_offset = 0;

    if (_track_type == TRACK_WAV) {
        uint32_t bps = _wav_sample_rate * (_wav_16bit ? 2 : 1) * (_wav_stereo ? 2 : 1);
        byte_offset = seconds * (int32_t)bps;
    } else if (_track_type == TRACK_MP3) {
        byte_offset = seconds * 40000;
    }

    int32_t new_consumed = consumed + byte_offset;
    if (new_consumed < 0) new_consumed = 0;
    if (new_consumed > _data_total) new_consumed = _data_total;

    // Seek the file
    int32_t delta = new_consumed - consumed;
    _file.seek(delta, SeekCur);
    _data_remaining = _data_total - new_consumed;

    // Reset MP3 decoder to resync to next valid frame
    if (_track_type == TRACK_MP3 && s_mp3) {
        s_mp3->end();
        s_mp3->begin();
    }

    // Recalculate elapsed time from position
    if (_track_type == TRACK_WAV) {
        uint32_t bps = _wav_sample_rate * (_wav_16bit ? 2 : 1) * (_wav_stereo ? 2 : 1);
        _pause_elapsed_ms = (uint32_t)((uint64_t)new_consumed * 1000 / bps);
    } else {
        _pause_elapsed_ms = (uint32_t)((uint64_t)new_consumed * 1000 / 40000);
    }
    _play_start_ms = millis();

    // Re-enable I2S before resuming playback
    if (was_playing && _i2s_tx && !_i2s_running) {
        i2s_channel_enable(_i2s_tx);
        _i2s_running = true;
    }

    // Resume playback
    _playing = was_playing;
    updateTimeUI();
}

// ============================================================
// Lifecycle
// ============================================================

void MusicApp::onCreate() {
    _playing = false;
    _muted = false;
    _shuffle = false;
    _vinyl_angle = 0;

    // Create screen on demand (not created at boot)
    if (!objects.music) {
        create_screen_music();
    }

    delay(30); // Let OK tone finish before killing speaker
    M5.Speaker.stop();
    M5.Speaker.end();

    s_volume = _volume;

    scanTracks();

    _audio_task_run = true;
    xTaskCreatePinnedToCore(audioTaskFunc, "audio_task", 16384, this, 5, &_audio_task, 0);

    loadScreen(SCREEN_ID_MUSIC);

    // Update UI after screen is loaded (widgets now exist)
    updateTrackUI();
    updateTimeUI();
    updatePlayPauseUI();
    updateVolumeUI();

    _tmr_anim = lv_timer_create(animTimerCb, 50, this);
}

void MusicApp::onUpdate() {
    // Auto-advance when track finishes
    if (_playing && !_active && _track_type == TRACK_NONE) {
        if (_track_count > 0) {
            _current_track = nextTrackIndex();
            updateTrackUI();
            openTrack(_current_track);
        } else {
            _playing = false;
            updatePlayPauseUI();
        }
    }
}

void MusicApp::onDestroy() {
    stopPlayback();
    _playing = false;

    _audio_task_run = false;
    vTaskDelay(pdMS_TO_TICKS(50));
    _audio_task = nullptr;

    teardownI2S();
    M5.Speaker.begin();

    if (_tmr_anim) {
        lv_timer_delete(_tmr_anim);
        _tmr_anim = nullptr;
    }
}

// ============================================================
// Keyboard input
// Keys: ; = vol up, . = vol down
//       , and / = cycle control focus left/right
//       OK (enter/space) = activate focused control
//       ` = back
// ============================================================

// Flash focus on a control icon briefly then restore proper state
void MusicApp::flashControl(lv_obj_t* obj) {
    if (!obj) return;
    lv_obj_add_state(obj, LV_STATE_FOCUS_KEY);
    // Remove focus after 150ms via a one-shot timer
    lv_timer_create([](lv_timer_t* t) {
        lv_obj_t* o = (lv_obj_t*)lv_timer_get_user_data(t);
        if (o) lv_obj_remove_state(o, LV_STATE_FOCUS_KEY);
        lv_timer_delete(t);
    }, 150, obj);
}

void MusicApp::onKeyPressed(char key) {
    Serial.printf("[MUSIC] key '%c' playing=%d active=%d i2s=%d remain=%ld\n",
                  key, _playing, _active, _i2s_running, (long)_data_remaining);
    if (key == '`') {
        if (atoi(ConfigManager::getTone()) > 0) M5.Speaker.tone(3000, 20);
        if (_back_app) _manager.switchApp(_back_app);
        return;
    }

    switch (key) {
        // p = Play / Pause
        case 'p': case 'P':
            if (_track_count == 0) break;
            flashControl(objects.music_image_play_pause);
            if (_playing) {
                _pause_elapsed_ms += millis() - _play_start_ms;
                _playing = false;
                // Wait for audio task to exit its read/write loop
                vTaskDelay(pdMS_TO_TICKS(30));
                if (_i2s_tx && _i2s_running) {
                    i2s_channel_disable(_i2s_tx);
                    _i2s_running = false;
                }
            } else {
                if (_active && _data_remaining > 0) {
                    if (_i2s_tx && !_i2s_running) {
                        i2s_channel_enable(_i2s_tx);
                        _i2s_running = true;
                    }
                    _play_start_ms = millis();
                    _playing = true;
                } else {
                    openTrack(_current_track);
                    _playing = true;
                }
            }
            updatePlayPauseUI();
            break;

        // m = Mute toggle
        case 'm': case 'M':
            _muted = !_muted;
            s_volume = _muted ? 0 : _volume;
            updateVolumeUI();
            break;

        // = Volume up
        case '=': case '+':
            _muted = false;
            _volume += VOL_STEP;
            if (_volume > 21) _volume = 21;
            s_volume = _volume;
            updateVolumeUI();
            break;

        // - Volume down
        case '-': case '_':
            _volume -= VOL_STEP;
            if (_volume < 0) _volume = 0;
            s_volume = _volume;
            updateVolumeUI();
            break;

        // s = Shuffle toggle
        case 's': case 'S':
            _shuffle = !_shuffle;
            flashControl(objects.music_image_shuffle);
            if (objects.music_image_shuffle) {
                if (_shuffle)
                    lv_obj_add_state(objects.music_image_shuffle, LV_STATE_CHECKED);
                else
                    lv_obj_remove_state(objects.music_image_shuffle, LV_STATE_CHECKED);
            }
            break;

        // ; = Previous track
        case ';':
            if (_track_count > 0) {
                flashControl(objects.music_image_previous);
                _playing = false;
                vTaskDelay(pdMS_TO_TICKS(20));
                _current_track = (_current_track - 1 + _track_count) % _track_count;
                updateTrackUI();
                if (openTrack(_current_track)) {
                    _playing = true;
                }
                updatePlayPauseUI();
            }
            break;

        // . = Next track
        case '.':
            if (_track_count > 0) {
                flashControl(objects.music_image_next);
                _playing = false;
                vTaskDelay(pdMS_TO_TICKS(20));
                _current_track = nextTrackIndex();
                updateTrackUI();
                if (openTrack(_current_track)) {
                    _playing = true;
                }
                updatePlayPauseUI();
            }
            break;

        // , = Seek backward 5 seconds
        case ',':
            seekRelative(-5);
            break;

        // / = Seek forward 5 seconds
        case '/':
            seekRelative(5);
            break;

        default:
            break;
    }
}

// ============================================================
// UI helpers
// ============================================================

void MusicApp::updateTrackUI() {
    // Extract metadata before displaying
    extractID3Meta(_current_track);

    if (_track_count > 0) {
        char display[64];
        strncpy(display, _track_names[_current_track], sizeof(display));
        display[63] = '\0';
        char* dot = strrchr(display, '.');
        if (dot) *dot = '\0';

        lv_label_set_text(objects.music_label_name, display);

        char nosBuf[16];
        snprintf(nosBuf, sizeof(nosBuf), "%d/%d", _current_track + 1, _track_count);
        lv_label_set_text(objects.music_label_track_nos, nosBuf);

        // Show artist - album
        if (objects.music_label_album_artist) {
            if (_artist[0] && _album[0]) {
                char meta[128];
                snprintf(meta, sizeof(meta), "%s - %s", _artist, _album);
                lv_label_set_text(objects.music_label_album_artist, meta);
            } else if (_artist[0]) {
                lv_label_set_text(objects.music_label_album_artist, _artist);
            } else if (_album[0]) {
                lv_label_set_text(objects.music_label_album_artist, _album);
            } else {
                lv_label_set_text(objects.music_label_album_artist, "");
            }
        }
    } else {
        lv_label_set_text(objects.music_label_name, "No Tracks");
        lv_label_set_text(objects.music_label_track_nos, "0/0");
        if (objects.music_label_album_artist)
            lv_label_set_text(objects.music_label_album_artist, "");
    }
}

void MusicApp::updateTimeUI() {
    // Elapsed only
    uint32_t elapsed_sec = 0;
    if (_active) {
        if (_playing) {
            elapsed_sec = (_pause_elapsed_ms + millis() - _play_start_ms) / 1000;
        } else {
            elapsed_sec = _pause_elapsed_ms / 1000;
        }
    }

    char buf[10];
    snprintf(buf, sizeof(buf), "%02lu:%02lu", elapsed_sec / 60, elapsed_sec % 60);
    lv_label_set_text(objects.music_label_time, buf);

    // Update progress bar
    if (objects.music_bar_time && _data_total > 0 && _active) {
        int32_t progress = 100 - (_data_remaining * 100 / _data_total);
        if (progress < 0) progress = 0;
        if (progress > 100) progress = 100;
        lv_bar_set_value(objects.music_bar_time, progress, LV_ANIM_OFF);
    } else if (objects.music_bar_time) {
        lv_bar_set_value(objects.music_bar_time, 0, LV_ANIM_OFF);
    }
}

void MusicApp::updatePlayPauseUI() {
    if (objects.music_image_play_pause) {
        if (_playing) {
            lv_image_set_src(objects.music_image_play_pause, &img_music_pause);
            lv_obj_add_state(objects.music_image_play_pause, LV_STATE_CHECKED);
        } else {
            lv_image_set_src(objects.music_image_play_pause, &img_music_play);
            lv_obj_remove_state(objects.music_image_play_pause, LV_STATE_CHECKED);
        }
    }
}

void MusicApp::updateVolumeUI() {
    if (objects.music_arc_volume) {
        int16_t display_vol = _muted ? 0 : (_volume * 100 / 21);
        lv_arc_set_value(objects.music_arc_volume, display_vol);
    }
}

// ============================================================
// Animation
// ============================================================

void MusicApp::onAnimUpdate() {
    if (_playing && _active) updateTimeUI();
    if (!_playing) return;

    _vinyl_angle = (_vinyl_angle + VINYL_SPEED) % 3600;
    if (objects.music_vinyl_disk)
        lv_image_set_rotation(objects.music_vinyl_disk, _vinyl_angle);
}
