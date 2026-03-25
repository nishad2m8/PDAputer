#include "fm_radio_app.h"
#include <ui.h>
#include <lvgl.h>
#include <Arduino.h>
#include <M5Cardputer.h>
#include <battery_manager.h>
#include <config_manager.h>
#include <math.h>

// ============================================================
// LVGL timer callback — forwards to instance method
// ============================================================

void FMRadioApp::radioTimerCb(lv_timer_t* t) {
    FMRadioApp* self = (FMRadioApp*)lv_timer_get_user_data(t);
    if (self) self->onRadioTimerUpdate();
}

// ============================================================
// Lifecycle
// ============================================================

void FMRadioApp::onCreate() {
    // Create screen on demand (not created at boot)
    if (!objects.fm_radio) {
        create_screen_fm_radio();
    }

    // Initialize radio hardware once
    if (!_radio_initialized) {
        _radio.begin();
        _radio_initialized = true;
    }

    // Start muted — user presses 'p' to play
    if (_radio_initialized && _radio.isConnected()) {
        _radio.setMute(true);
    }

    // Cache preset label pointers
    _preset_objs[0] = objects.fmradio_label_pre1;
    _preset_objs[1] = objects.fmradio_label_pre2;
    _preset_objs[2] = objects.fmradio_label_pre3;

    // Build the adaptive frequency scale
    createScaleLines();

    // Set initial scale + labels
    float freq = _radio.getFrequency();
    float minF = _radio.getBandMinFreq();
    float maxF = _radio.getBandMaxFreq();
    updateScale(freq, minF, maxF);

    char minBuf[8], maxBuf[8];
    snprintf(minBuf, sizeof(minBuf), "%g", minF);
    snprintf(maxBuf, sizeof(maxBuf), "%g", maxF);
    lv_label_set_text(objects.fmradio_label_min, minBuf);
    lv_label_set_text(objects.fmradio_label_max, maxBuf);

    updateBatteryBar();
    updatePlaybackStatusUI();

    // Show error if TEA5767 not found
    if (!_radio.isConnected()) {
        lv_label_set_text(objects.fmradio_label_main, "ERR");
        lv_label_set_text(objects.fmradio_label_sub, "No TEA5767");
        if (objects.fmradio_image_playpause)
            lv_obj_remove_state(objects.fmradio_image_playpause, LV_STATE_CHECKED);
        if (objects.fmradio_image_headphone)
            lv_obj_add_state(objects.fmradio_image_headphone, LV_STATE_CHECKED);
    }

    // Initialize preset labels immediately (avoid flash of stale values)
    if (_radio.isConnected()) {
        float curFreq = _radio.getFrequency();
        for (int i = 0; i < 3; i++) {
            float pf = _radio.getPresetFreq(i);
            if (pf > 0.0f && fabsf(pf - curFreq) < 0.05f)
                lv_obj_add_state(_preset_objs[i], LV_STATE_CHECKED);
            else
                lv_obj_remove_state(_preset_objs[i], LV_STATE_CHECKED);

            char buf[12];
            if (pf > 0.0f)
                snprintf(buf, sizeof(buf), "%d|%.1f", i + 1, pf);
            else
                snprintf(buf, sizeof(buf), "%d| --.-", i + 1);
            lv_label_set_text(_preset_objs[i], buf);
        }
    }

    // Switch to FM Radio screen
    loadScreen(SCREEN_ID_FM_RADIO);

    // Start 250ms status update timer
    _tmr_radio = lv_timer_create(radioTimerCb, 250, this);
}

void FMRadioApp::onUpdate() {
    // All periodic work handled by LVGL timer callback
}

void FMRadioApp::onDestroy() {
    // Stop the status update timer
    if (_tmr_radio) {
        lv_timer_delete(_tmr_radio);
        _tmr_radio = nullptr;
    }

    // Safely stop all radio activity (cancel seek, save freq, mute)
    if (_radio_initialized) {
        _radio.stop();
    }
}

// ============================================================
// Keyboard input
// ============================================================

void FMRadioApp::onKeyPressed(char key) {
    // Backtick → return to main menu
    if (key == '`') {
        if (atoi(ConfigManager::getTone()) > 0) M5.Speaker.tone(3000, 20);
        if (_back_app) _manager.switchApp(_back_app);
        return;
    }

    if (!_radio.isConnected()) return;

    // Fn + number → save preset
    auto& kstate = M5Cardputer.Keyboard.keysState();
    if (kstate.fn && key >= '1' && key <= '3') {
        _radio.savePreset(key - '1');
        return;
    }

    switch (key) {
        // Seek
        case ';': _radio.seekUp();   break;
        case '.': _radio.seekDown(); break;
        // Fine tune
        case ',': _radio.tuneDown(); break;
        case '/': _radio.tuneUp();   break;
        // Presets 1-3
        case '1': case '2': case '3':
            _radio.loadPreset(key - '1');
            break;
        // Mute
        case 'm': case 'M': case ' ':
            _radio.toggleMute();
            updatePlaybackStatusUI();
            break;
        // Play / Pause
        case 'p': case 'P':
            _radio.toggleMute();
            updatePlaybackStatusUI();
            break;
        // Stereo / Mono
        case 's':
            _radio.setForceMono(!_radio.isForceMono());
            break;
        // Band switch
        case 'b':
            _radio.setBand(_radio.getBand() == 0 ? 1 : 0);
            break;
        default:
            break;
    }
}

// ============================================================
// Frequency scale — Gaussian-curve adaptive visualizer
// ============================================================

void FMRadioApp::createScaleLines() {
    if (!objects.fmradio_scale) return;

    lv_obj_t* scale = objects.fmradio_scale;
    lv_obj_clean(scale);
    _active_scale_line = -1;

    // Configure the scale container
    lv_obj_set_pos(scale, 0, -30);
    lv_obj_set_size(scale, LV_PCT(100), LV_PCT(20));
    lv_obj_set_style_pad_left(scale, SCALE_PAD_LR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scale, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scale, SCALE_PAD_LR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scale, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scale, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scale, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scale, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(scale, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_align(scale, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(scale, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(scale, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(scale, LV_FLEX_ALIGN_SPACE_EVENLY, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(scale, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(scale, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Overlay container configurator (shared for bg grid + front curve)
    auto configureContainer = [this](lv_obj_t* obj) {
        lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
        lv_obj_set_style_pad_left(obj, SCALE_PAD_LR, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(obj, SCALE_PAD_LR, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_IGNORE_LAYOUT);
        lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
    };

    // Background grid layer
    lv_obj_t* grid_container = lv_obj_create(scale);
    configureContainer(grid_container);

    // Foreground curve layer
    lv_obj_t* curve_container = lv_obj_create(scale);
    configureContainer(curve_container);
    lv_obj_move_foreground(curve_container);

    lv_value_precise_t max_h = (lv_value_precise_t)SCALE_MAX_HEIGHT;
    lv_value_precise_t init_start = max_h - (lv_value_precise_t)SCALE_MIN_HEIGHT;
    if (init_start < 0) init_start = 0;

    // Create background tick lines (fixed-height, dark)
    for (int i = 0; i < SCALE_LINES; i++) {
        lv_obj_t* bg_line = lv_line_create(grid_container);
        lv_obj_set_size(bg_line, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_line_width(bg_line, SCALE_LINE_WIDTH, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_rounded(bg_line, true, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(bg_line, lv_color_hex(SCALE_COLOR_BACK_HEX), LV_PART_MAIN | LV_STATE_DEFAULT);

        _scale_bg_pts[i][0] = {0, 0};
        _scale_bg_pts[i][1] = {0, max_h};
        lv_line_set_points(bg_line, _scale_bg_pts[i], 2);
    }

    // Create foreground curve lines (variable-height, colored)
    for (int i = 0; i < SCALE_LINES; i++) {
        lv_obj_t* front_line = lv_line_create(curve_container);
        _scale_lines[i] = front_line;
        lv_obj_set_size(front_line, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_line_width(front_line, SCALE_LINE_WIDTH, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_rounded(front_line, true, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(front_line, lv_color_hex(SCALE_COLOR_CURVE_HEX), LV_PART_MAIN | LV_STATE_DEFAULT);

        _scale_pts[i][0] = {0, init_start};
        _scale_pts[i][1] = {0, max_h};
        lv_line_set_points(front_line, _scale_pts[i], 2);
    }
}

void FMRadioApp::updateScale(float freq, float minFreq, float maxFreq) {
    if (SCALE_LINES <= 0 || maxFreq <= minFreq) return;

    float clamped = freq;
    if (clamped < minFreq) clamped = minFreq;
    if (clamped > maxFreq) clamped = maxFreq;

    float span       = maxFreq - minFreq;
    float normalized = (clamped - minFreq) / span;
    float pos        = normalized * (float)(SCALE_LINES - 1);
    float linesPerMHz = (float)(SCALE_LINES - 1) / span;
    float sigmaLines = SCALE_CURVE_SIGMA_MHZ * linesPerMHz;
    if (sigmaLines < 0.001f) sigmaLines = 0.001f;
    float amplitude  = (float)(SCALE_MAX_HEIGHT - SCALE_MIN_HEIGHT);

    for (int i = 0; i < SCALE_LINES; i++) {
        float delta  = (float)i - pos;
        float scaled = delta / sigmaLines;
        float curve  = expf(-0.5f * scaled * scaled);
        float h      = (float)SCALE_MIN_HEIGHT + amplitude * curve;

        float startF = (float)SCALE_MAX_HEIGHT - h;
        if (startF < 0.0f) startF = 0.0f;
        lv_value_precise_t startVal = (lv_value_precise_t)lroundf(startF);
        lv_value_precise_t endVal   = (lv_value_precise_t)SCALE_MAX_HEIGHT;

        _scale_pts[i][0] = {0, startVal};
        _scale_pts[i][1] = {0, endVal};
        lv_line_set_points(_scale_lines[i], _scale_pts[i], 2);
    }

    // Highlight the active frequency line
    int newActive = (int)lroundf(pos);
    if (newActive < 0) newActive = 0;
    if (newActive >= SCALE_LINES) newActive = SCALE_LINES - 1;

    if (newActive != _active_scale_line) {
        if (_active_scale_line >= 0 && _active_scale_line < SCALE_LINES) {
            lv_obj_set_style_line_color(
                _scale_lines[_active_scale_line],
                lv_color_hex(SCALE_COLOR_CURVE_HEX),
                LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        _active_scale_line = newActive;
        lv_obj_set_style_line_color(
            _scale_lines[_active_scale_line],
            lv_color_hex(SCALE_COLOR_ACTIVE_HEX),
            LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

// ============================================================
// UI status helpers
// ============================================================

void FMRadioApp::updateBatteryBar() {
    BatteryManager::update();
    if (objects.fmradio_bar_battery) {
        lv_bar_set_value(objects.fmradio_bar_battery, BatteryManager::getLevel(), LV_ANIM_OFF);
    }
}

void FMRadioApp::updatePlaybackStatusUI() {
    if (!_radio.isConnected()) {
        if (objects.fmradio_image_playpause)
            lv_obj_remove_state(objects.fmradio_image_playpause, LV_STATE_CHECKED);
        if (objects.fmradio_image_headphone)
            lv_obj_add_state(objects.fmradio_image_headphone, LV_STATE_CHECKED);
        if (objects.fmradio_image_signal)
            lv_obj_add_state(objects.fmradio_image_signal, LV_STATE_CHECKED);
        return;
    }

    bool playing = !_radio.isMuted();
    if (objects.fmradio_image_playpause) {
        if (playing)
            lv_obj_add_state(objects.fmradio_image_playpause, LV_STATE_CHECKED);
        else
            lv_obj_remove_state(objects.fmradio_image_playpause, LV_STATE_CHECKED);
    }

    bool muted = _radio.isMuted();
    if (objects.fmradio_image_headphone) {
        if (muted)
            lv_obj_add_state(objects.fmradio_image_headphone, LV_STATE_CHECKED);
        else
            lv_obj_remove_state(objects.fmradio_image_headphone, LV_STATE_CHECKED);
    }
}

// ============================================================
// Periodic radio status update (called every 250ms via timer)
// ============================================================

void FMRadioApp::onRadioTimerUpdate() {
    updatePlaybackStatusUI();
    updateBatteryBar();

    if (!_radio.isConnected()) return;

    _radio.updateStatus();

    float freq    = _radio.getFrequency();
    float bandMin = _radio.getBandMinFreq();
    float bandMax = _radio.getBandMaxFreq();

    // Frequency display
    if (_radio.isSeeking()) {
        lv_label_set_text(objects.fmradio_label_main, "SEEK");
        lv_label_set_text(objects.fmradio_label_sub, "...");
    } else {
        char buf[10];
        snprintf(buf, sizeof(buf), "%.1f", freq);
        lv_label_set_text(objects.fmradio_label_main, buf);
        lv_label_set_text(objects.fmradio_label_sub, "MHz");
    }

    // Stereo/Mono indicator
    lv_label_set_text(objects.fmradio_label_most, _radio.isStereo() ? "ST" : "MO");

    // Band indicator
    lv_label_set_text(objects.fmradio_label_mode, _radio.getBand() == 1 ? "JP" : "FM");

    // Min/Max frequency labels
    char minBuf[8], maxBuf[8];
    snprintf(minBuf, sizeof(minBuf), "%g", bandMin);
    snprintf(maxBuf, sizeof(maxBuf), "%g", bandMax);
    lv_label_set_text(objects.fmradio_label_min, minBuf);
    lv_label_set_text(objects.fmradio_label_max, maxBuf);

    // Signal strength bar
    if (objects.fmradio_bar_signal) {
        lv_bar_set_value(objects.fmradio_bar_signal, _radio.getSignalLevel(), LV_ANIM_OFF);
    }

    // Update frequency scale visualization
    updateScale(freq, bandMin, bandMax);

    // Update preset station labels
    for (int i = 0; i < 3; i++) {
        float pf = _radio.getPresetFreq(i);
        bool match = (pf > 0.0f && fabsf(pf - freq) < 0.05f);
        if (match)
            lv_obj_add_state(_preset_objs[i], LV_STATE_CHECKED);
        else
            lv_obj_remove_state(_preset_objs[i], LV_STATE_CHECKED);

        char buf[12];
        if (pf > 0.0f)
            snprintf(buf, sizeof(buf), "%d|%.1f", i + 1, pf);
        else
            snprintf(buf, sizeof(buf), "%d| --.-", i + 1);
        lv_label_set_text(_preset_objs[i], buf);
    }
}
