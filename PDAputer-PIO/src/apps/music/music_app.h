#pragma once

#include "../../app_manager/app_base.h"
#include "../../app_manager/app_manager.h"
#include <lvgl.h>
#include <SD.h>
#include <driver/i2s_std.h>

struct __attribute__((packed)) wav_header_t {
    char     RIFF[4];
    uint32_t chunk_size;
    char     WAVEfmt[8];
    uint32_t fmt_chunk_size;
    uint16_t audiofmt;
    uint16_t channel;
    uint32_t sample_rate;
    uint32_t byte_per_sec;
    uint16_t block_size;
    uint16_t bit_per_sample;
};

struct __attribute__((packed)) sub_chunk_t {
    char     identifier[4];
    uint32_t chunk_size;
};

class MusicApp : public AppBase {
public:
    MusicApp(AppManager& manager) : _manager(manager) {}

    void setBackApp(AppBase* back) { _back_app = back; }

    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
    void onKeyPressed(char key) override;
    const char* getName() override { return "Music"; }

private:
    AppManager& _manager;
    AppBase* _back_app = nullptr;

    lv_timer_t* _tmr_anim = nullptr;
    bool _playing = false;
    bool _muted = false;
    bool _shuffle = false;
    int16_t _vinyl_angle = 0;
    int16_t _volume = 16; // 0-21

    static constexpr int16_t VINYL_SPEED = 30;
    static constexpr int16_t VOL_STEP = 2;

    // Track list
    static constexpr int MAX_TRACKS = 64;
    static constexpr const char* MUSIC_PATH = "/PDAputer/Music";
    char _track_names[MAX_TRACKS][64];
    int _track_count = 0;
    int _current_track = 0;

    // I2S output
    i2s_chan_handle_t _i2s_tx = nullptr;
    bool _i2s_running = false;
    void setupI2S(uint32_t sample_rate, bool stereo);
    void teardownI2S();

    // Playback
    enum TrackType { TRACK_NONE, TRACK_WAV, TRACK_MP3 };
    TrackType _track_type = TRACK_NONE;
    File _file;
    volatile bool _active = false;
    int32_t _data_remaining = 0;
    int32_t _data_total = 0;
    uint32_t _play_start_ms = 0;
    uint32_t _pause_elapsed_ms = 0; // accumulated elapsed before pause

    // ID3v2 metadata
    char _artist[64];
    char _album[64];

    // WAV format info
    bool _wav_16bit = false;
    bool _wav_stereo = false;
    uint32_t _wav_sample_rate = 44100;

    // Audio decode task
    TaskHandle_t _audio_task = nullptr;
    volatile bool _audio_task_run = false;

    void scanTracks();
    bool openTrack(int track_idx);
    bool openWav(int track_idx);
    bool openMp3(int track_idx);
    void stopPlayback();
    void seekRelative(int seconds);
    void extractID3Meta(int track_idx);
    int nextTrackIndex();

    void updateTrackUI();
    void updateTimeUI();
    void updatePlayPauseUI();
    void updateVolumeUI();
    void flashControl(lv_obj_t* obj);

    static void animTimerCb(lv_timer_t* t);
    void onAnimUpdate();
    static void audioTaskFunc(void* param);
};
