#include "main_menu_app.h"
#include <ui.h>
#include <lvgl.h>
#include <Arduino.h>
#include <M5Cardputer.h>
#include <battery_manager.h>
#include <config_manager.h>
#include <sd_manager.h>
#include <wifi_manager.h>
#include <time_manager.h>
#include <images.h>

using namespace smooth_ui_toolkit;

// ============================================================
// Slot positions: off-left, visible 0-4, off-right
// ============================================================
static const SlotPos SLOTS[] = {
    {   0, 135, 170 },  // [0] OFF_LEFT
    {  -2,  90, 170 },  // [1] SLOT 0  (leftmost visible)
    {  35,  68, 200 },  // [2] SLOT 1
    {  95,  53, 256 },  // [3] SLOT 2  (center / selected)
    { 149,  68, 200 },  // [4] SLOT 3
    { 190,  90, 170 },  // [5] SLOT 4  (rightmost visible)
    { 190, 135, 170 },  // [6] OFF_RIGHT
};

// Maps circular distance to slot index (11 apps)
// raw: 0=center, 1=right1, 2=right2, 3..8=hidden, 9=left2, 10=left1
static const int RAW_TO_SLOT[] = { 3, 4, 5, -1, -1, -1, -1, -1, -1, 1, 2 };

// ============================================================
// App definitions
// ============================================================
static const AppDef APP_DEFS[] = {
    { "Notes",     0xff2a1800, 0xffffcc66 },  // 0 - default
    { "Music",     0xff002b4a, 0xff55b4ff },  // 1
    { "Web Radio", 0xff0a2800, 0xff2ef900 },  // 2
    { "FM Radio",  0xff2c1e00, 0xffffaa00 },  // 3
    { "AI Chat",   0xff4f0f21, 0xffff9b9d },  // 4
    { "Games",     0xff3a0830, 0xffff7acd },  // 5
    { "LoRa Chat", 0xff282b00, 0xffd8e800 },  // 6
    { "GPS",       0xff001758, 0xff98b0ff },  // 7
    { "Calendar",  0xff0a2800, 0xff2ef900 },  // 8
    { "Remote",    0xff2b2b2b, 0xffffffff },  // 9
    { "Settings",  0xff002c2d, 0xff03ffee },  // 10
};

// Label default X position and bounce offset
static constexpr int16_t LABEL_X = 48;
static constexpr int16_t LABEL_BOUNCE = 10;

// Panel default Y position and bounce offset
static constexpr int16_t PANEL_Y = 106;
static constexpr int16_t PANEL_BOUNCE = 12;

// Tone feedback
static constexpr int TONE_FREQ = 4000;
static constexpr int TONE_MS   = 20;

// ============================================================
// Lifecycle
// ============================================================

void MainMenuApp::onCreate() {
    loadScreen(SCREEN_ID_MAIN);

    // Map LVGL objects to icon array (matches APP_DEFS order)
    _icons[0] = objects.main_image_app_notes;
    _icons[1] = objects.main_image_app_music;
    _icons[2] = objects.main_image_app_webradio;
    _icons[3] = objects.main_image_app_fmradio;
    _icons[4] = objects.main_image_app_ai;
    _icons[5] = objects.main_image_app_games;
    _icons[6] = objects.main_image_app_lorachat;
    _icons[7] = objects.main_image_app_gps;
    _icons[8] = objects.main_image_app_calendar;
    _icons[9] = objects.main_image_app_remote;
    _icons[10] = objects.main_image_app_setting;

    _selected_index = 0;
    _is_scrolling = false;

    // Sync volume from config
    _saved_volume = atoi(ConfigManager::getTone());
    if (_saved_volume < 0) _saved_volume = 0;
    if (_saved_volume > 255) _saved_volume = 255;
    _muted = (_saved_volume == 0);
    M5.Speaker.setVolume(_muted ? 0 : _saved_volume);

    setRestPositions();
    updateLabel();
    updatePanelColor();

    // Label bounce spring animation
    _label_x.springOptions().stiffness = 300;
    _label_x.springOptions().damping = 20;
    _label_x.springOptions().mass = 1.0f;
    _label_x.begin();
    _label_x.teleport((float)LABEL_X);

    // Panel Y bounce spring animation
    _panel_y.springOptions().stiffness = 250;
    _panel_y.springOptions().damping = 15;
    _panel_y.springOptions().mass = 1.0f;
    _panel_y.begin();
    _panel_y.teleport((float)PANEL_Y);
}

void MainMenuApp::onUpdate() {
    if (_is_scrolling) {
        _scroll_anim.update();
        float progress = _scroll_anim.value();
        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;
        applyPositions(progress);

        if (_scroll_anim.done()) {
            _is_scrolling = false;
            setRestPositions();
        }
    }

    // Update label X with spring bounce
    lv_obj_set_x(objects.main_label_menu_selected, (int16_t)_label_x.value());

    // Update panel Y with spring bounce
    lv_obj_set_y(objects.main_panel_menu_selected, (int16_t)_panel_y.value());

    // Update battery + status icons (BatteryManager throttles internally)
    BatteryManager::update();
    if (objects.main_bar_battery) {
        lv_bar_set_value(objects.main_bar_battery, BatteryManager::getLevel(), LV_ANIM_OFF);
    }
    if (objects.main_label_battery) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%d%%", BatteryManager::getLevel());
        lv_label_set_text(objects.main_label_battery, buf);
    }
    // Update WiFi state machine
    WifiManager::update();

    // Update time display
    if (objects.main_label_time && TimeManager::isSynced()) {
        lv_label_set_text(objects.main_label_time, TimeManager::getTimeHHMM().c_str());
    }

    // Update date display (e.g. "Tue 24 Mar")
    if (objects.main_label_date && TimeManager::isSynced()) {
        static const char* DAY_ABBR[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
        static const char* MON_ABBR[] = {"Jan","Feb","Mar","Apr","May","Jun",
                                         "Jul","Aug","Sep","Oct","Nov","Dec"};
        int d = TimeManager::getDay();
        int w = TimeManager::getDayOfWeek();
        int m = TimeManager::getMonth();
        char dbuf[16];
        snprintf(dbuf, sizeof(dbuf), "%s %d %s", DAY_ABBR[w], d, MON_ABBR[m - 1]);
        lv_label_set_text(objects.main_label_date, dbuf);
    }

    // Update WiFi icon based on signal strength
    if (objects.main_image_wifi) {
        if (!WifiManager::isConnected()) {
            lv_image_set_src(objects.main_image_wifi, &img_wifi_04);
        } else {
            const lv_img_dsc_t* wifi_icons[] = {
                &img_wifi_00, &img_wifi_01, &img_wifi_02, &img_wifi_03
            };
            int level = WifiManager::getSignalLevel();
            if (level < 0) level = 0;
            if (level > 3) level = 3;
            lv_image_set_src(objects.main_image_wifi, wifi_icons[level]);
        }
    }

    updateStatusIcons();
}

void MainMenuApp::updateStatusIcons() {
    // Tone icon: tone-00 = muted, tone-01 = unmuted
    if (objects.main_image_tone) {
        lv_image_set_src(objects.main_image_tone,
                         _muted ? &img_tone_00 : &img_tone_01);
    }
    // SD card icon: sd-card-00 = unmounted, sd-card-01 = mounted
    if (objects.main_image_sdcard) {
        lv_image_set_src(objects.main_image_sdcard,
                         SDManager::isMounted() ? &img_sd_card_01 : &img_sd_card_00);
    }
}

void MainMenuApp::onDestroy() {
    _label_x.stop();
    _panel_y.stop();
}

// ============================================================
// App targets
// ============================================================

void MainMenuApp::setAppTarget(int index, AppBase* app) {
    if (index >= 0 && index < APP_COUNT) {
        _app_targets[index] = app;
    }
}

// ============================================================
// Keyboard input
// ============================================================

void MainMenuApp::onKeyPressed(char key) {
    if (_is_scrolling) return;

    // Support common right/left variants: ',', '<' for left and '/', '.', '>' for right
    Serial.printf("[APP] onKeyPressed '%c' (0x%02X)\n", (key >= 32 && key < 127) ? key : '.', (uint8_t)key);

    if (key == ',' || key == '<' || key == '.') {
        scrollLeft();
        if (!_muted) M5.Speaker.tone(TONE_FREQ, TONE_MS);
    } else if (key == '/' || key == ';' || key == '>') {
        scrollRight();
        if (!_muted) M5.Speaker.tone(TONE_FREQ, TONE_MS);
    } else if (key == '\n') {
        // OK/Enter → launch selected app
        if (!_muted) M5.Speaker.tone(TONE_FREQ, TONE_MS);
        if (_app_targets[_selected_index]) {
            _manager.switchApp(_app_targets[_selected_index]);
        }
    } else if (key == 'm' || key == 'M') {
        // Toggle mute / restore last saved volume
        _muted = !_muted;
        M5.Speaker.setVolume(_muted ? 0 : (_saved_volume > 0 ? _saved_volume : 128));
        updateStatusIcons();
    }
}

// ============================================================
// Scroll logic
// ============================================================

void MainMenuApp::scrollRight() {
    int old_sel = _selected_index;
    int new_sel = (_selected_index + 1) % APP_COUNT;

    setupScrollAnimation(old_sel, new_sel, 1);
    _selected_index = new_sel;
    updateLabel();
    updatePanelColor();

    // Bounce label from right
    _label_x.teleport((float)(LABEL_X + LABEL_BOUNCE));
    _label_x.move((float)LABEL_X);

    // Bounce panel Y
    _panel_y.teleport((float)(PANEL_Y + PANEL_BOUNCE));
    _panel_y.move((float)PANEL_Y);
}

void MainMenuApp::scrollLeft() {
    int old_sel = _selected_index;
    int new_sel = ((_selected_index - 1) + APP_COUNT) % APP_COUNT;

    setupScrollAnimation(old_sel, new_sel, -1);
    _selected_index = new_sel;
    updateLabel();
    updatePanelColor();

    // Bounce label from left
    _label_x.teleport((float)(LABEL_X - LABEL_BOUNCE));
    _label_x.move((float)LABEL_X);

    // Bounce panel Y
    _panel_y.teleport((float)(PANEL_Y + PANEL_BOUNCE));
    _panel_y.move((float)PANEL_Y);
}

void MainMenuApp::setupScrollAnimation(int old_sel, int new_sel, int dir) {
    for (int i = 0; i < APP_COUNT; i++) {
        int old_raw = ((i - old_sel) % APP_COUNT + APP_COUNT) % APP_COUNT;
        int new_raw = ((i - new_sel) % APP_COUNT + APP_COUNT) % APP_COUNT;

        int from = RAW_TO_SLOT[old_raw];
        int to   = RAW_TO_SLOT[new_raw];

        // Entering icon (was hidden) - comes from off-screen
        if (from == -1) from = (dir > 0) ? 6 : 0;

        // Exiting icon (becomes hidden) - goes to off-screen
        if (to == -1)   to   = (dir > 0) ? 0 : 6;

        _anim_from[i] = from;
        _anim_to[i]   = to;
    }

    // Show all icons during transition
    for (int i = 0; i < APP_COUNT; i++) {
        lv_obj_remove_flag(_icons[i], LV_OBJ_FLAG_HIDDEN);
    }

    // Start easing animation 0 → 1
    _scroll_anim.start = 0.0f;
    _scroll_anim.end   = 1.0f;
    _scroll_anim.delay = 0.0f;
    _scroll_anim.easingOptions().duration = 0.3f;
    _scroll_anim.easingOptions().easingFunction = ease::ease_out_cubic;
    _scroll_anim.init();
    _scroll_anim.play();

    _is_scrolling = true;
}

// ============================================================
// Position helpers
// ============================================================

void MainMenuApp::applyPositions(float progress) {
    for (int i = 0; i < APP_COUNT; i++) {
        const SlotPos& from = SLOTS[_anim_from[i]];
        const SlotPos& to   = SLOTS[_anim_to[i]];

        float fx = (float)from.x + ((float)to.x - (float)from.x) * progress;
        float fy = (float)from.y + ((float)to.y - (float)from.y) * progress;
        float fs = (float)from.scale + ((float)to.scale - (float)from.scale) * progress;

        lv_obj_set_pos(_icons[i], (int16_t)fx, (int16_t)fy);
        lv_image_set_scale(_icons[i], (uint16_t)fs);
    }
}

void MainMenuApp::setRestPositions() {
    for (int i = 0; i < APP_COUNT; i++) {
        int raw  = ((i - _selected_index) % APP_COUNT + APP_COUNT) % APP_COUNT;
        int slot = RAW_TO_SLOT[raw];

        if (slot == -1) {
            lv_obj_add_flag(_icons[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_remove_flag(_icons[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_pos(_icons[i], SLOTS[slot].x, SLOTS[slot].y);
            lv_image_set_scale(_icons[i], SLOTS[slot].scale);
        }
    }
}

void MainMenuApp::updateLabel() {
    lv_label_set_text(objects.main_label_menu_selected, APP_DEFS[_selected_index].label);
}

void MainMenuApp::updatePanelColor() {
    lv_obj_set_style_bg_color(
        objects.main_panel_menu_selected,
        lv_color_hex(APP_DEFS[_selected_index].panel_color),
        LV_PART_MAIN | LV_STATE_DEFAULT
    );
    lv_obj_set_style_text_color(
        objects.main_label_menu_selected,
        lv_color_hex(APP_DEFS[_selected_index].label_color),
        LV_PART_MAIN | LV_STATE_DEFAULT
    );
}
