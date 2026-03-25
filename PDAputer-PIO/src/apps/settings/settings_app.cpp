#include "settings_app.h"
#include <ui.h>
#include <lvgl.h>
#include <Arduino.h>
#include <M5Cardputer.h>
#include <config_manager.h>

// Tone feedback
static constexpr int TONE_NAV   = 4000;
static constexpr int TONE_OK    = 4500;
static constexpr int TONE_BACK  = 3000;
static constexpr int TONE_MS    = 20;

// Helper: play tone only if volume > 0
static void playTone(int freq) {
    if (atoi(ConfigManager::getTone()) > 0) {
        M5.Speaker.tone(freq, TONE_MS);
    }
}

// Menu: 0=device_name, 1=brightness, 2=tone, 3=time_format, 4=timezone, 5=wifi, 6=support
// Editable: 0, 1, 2, 3
static bool isEditable(int sel) {
    return sel == 0 || sel == 1 || sel == 2 || sel == 3;
}

// Entrance animation constants
static constexpr int16_t ENTRANCE_OFFSET = 50;   // slide in from right (px)
static constexpr float   STAGGER_GAP     = 0.10f; // stagger between items
static constexpr float   ENTRANCE_DUR    = 0.6f;  // total duration (sec)

// Selection bounce
static constexpr float SEL_BOUNCE_PX = 6.0f;

// ============================================================
// Lifecycle
// ============================================================

static void mapContainers(lv_obj_t* c[], int n) {
    (void)n;
    c[0] = objects.settings_container_devicename;
    c[1] = objects.settings_container_brightness;
    c[2] = objects.settings_container_tone;
    c[3] = objects.settings_container_tformat;
    c[4] = objects.settings_container_tzone;
    c[5] = objects.settings_container_ssid;
    c[6] = objects.settings_container_support;
}

void SettingsApp::onCreate() {
    _sel = 0;
    _prev_sel = 0;
    _editing = false;
    _on_support_screen = false;

    // Create screen on demand (not created at boot)
    if (!objects.settings) {
        create_screen_settings();
    }

    loadScreen(SCREEN_ID_SETTINGS);
    mapContainers(_containers, MENU_COUNT);

    // Set containers invisible before first render
    for (int i = 0; i < MENU_COUNT; i++) {
        if (_containers[i]) {
            lv_obj_set_style_translate_x(_containers[i], ENTRANCE_OFFSET, 0);
            lv_obj_set_style_opa(_containers[i], 0, 0);
        }
    }

    loadValues();
    updateSelection();
    _entrance.start = 0.0f;
    _entrance.end   = 1.0f;
    _entrance.delay = 0.0f;
    _entrance.easingOptions().duration = ENTRANCE_DUR;
    _entrance.easingOptions().easingFunction = ease::ease_out_back;
    _entrance.init();
    _entrance.play();
    _entering = true;

    // Selection bounce spring (bouncy feel)
    _sel_bounce.springOptions().stiffness = 300;
    _sel_bounce.springOptions().damping   = 12;
    _sel_bounce.springOptions().mass      = 0.8f;
    _sel_bounce.springOptions().bounce    = 0.6f;
    _sel_bounce.begin();
    _sel_bounce.teleport(0.0f);
}

void SettingsApp::onUpdate() {
    // Staggered entrance animation
    if (_entering) {
        _entrance.update();
        float p = _entrance.value();
        float range = 1.0f - (MENU_COUNT - 1) * STAGGER_GAP;

        for (int i = 0; i < MENU_COUNT; i++) {
            if (!_containers[i]) continue;
            float cp = (p - i * STAGGER_GAP) / range;
            if (cp < 0.0f) cp = 0.0f;
            if (cp > 1.0f) cp = 1.0f;

            // Fade to styled opa: 255 for selected, 150 for others
            lv_opa_t target_opa = (i == _sel) ? 255 : 150;
            lv_obj_set_style_translate_x(_containers[i],
                (int16_t)((1.0f - cp) * ENTRANCE_OFFSET), 0);
            lv_obj_set_style_opa(_containers[i], (lv_opa_t)(cp * target_opa), 0);
        }

        if (_entrance.done()) {
            _entering = false;
            for (int i = 0; i < MENU_COUNT; i++) {
                if (!_containers[i]) continue;
                lv_obj_remove_local_style_prop(_containers[i], LV_STYLE_TRANSLATE_X, 0);
                lv_obj_remove_local_style_prop(_containers[i], LV_STYLE_OPA, 0);
            }
        }
    }

    // Selection bounce — apply spring offset to selected container
    if (!_entering) {
        float bx = _sel_bounce.value();
        for (int i = 0; i < MENU_COUNT; i++) {
            if (!_containers[i]) continue;
            if (i == _sel) {
                lv_obj_set_style_translate_x(_containers[i], (int16_t)bx, 0);
            } else {
                lv_obj_remove_local_style_prop(_containers[i], LV_STYLE_TRANSLATE_X, 0);
            }
        }
    }
}

void SettingsApp::onDestroy() {
    _sel_bounce.stop();
    for (int i = 0; i < MENU_COUNT; i++) {
        if (!_containers[i]) continue;
        lv_obj_remove_local_style_prop(_containers[i], LV_STYLE_TRANSLATE_X, 0);
        lv_obj_remove_local_style_prop(_containers[i], LV_STYLE_OPA, 0);
    }
}

// ============================================================
// Load config values into UI
// ============================================================

void SettingsApp::loadValues() {
    if (objects.settings_textarea_devicename) {
        lv_textarea_set_text(objects.settings_textarea_devicename,
                             ConfigManager::getDeviceName());
    }

    // Brightness slider
    {
        int bright = atoi(ConfigManager::getBrightness());
        if (bright < 25) bright = 25;
        if (bright > 255) bright = 255;
        int pct = bright * 100 / 255;
        if (objects.settings_slider_brightness) {
            lv_bar_set_value(objects.settings_slider_brightness, pct, LV_ANIM_OFF);
        }
        if (objects.settings_label_brightness) {
            char buf[8];
            snprintf(buf, sizeof(buf), "%d%%", pct);
            lv_label_set_text(objects.settings_label_brightness, buf);
        }
    }

    // Tone volume slider
    {
        int vol = atoi(ConfigManager::getTone());
        if (vol < 0) vol = 0;
        if (vol > 255) vol = 255;
        int pct = vol * 100 / 255;
        if (objects.settings_slider_tone) {
            lv_bar_set_value(objects.settings_slider_tone, pct, LV_ANIM_OFF);
        }
        if (objects.settings_label_tone) {
            char buf[8];
            snprintf(buf, sizeof(buf), "%d%%", pct);
            lv_label_set_text(objects.settings_label_tone, buf);
        }
    }

    if (objects.settings_label_ssid) {
        const char* ssid = ConfigManager::getWifiSSID();
        lv_label_set_text(objects.settings_label_ssid, ssid[0] ? ssid : "Not set");
    }

    if (objects.settings_label_tzone) {
        const char* tz = ConfigManager::getTimezone();
        lv_label_set_text(objects.settings_label_tzone, tz[0] ? tz : "UTC0");
    }

    if (objects.settings_roller_tformat) {
        const char* fmt = ConfigManager::getTimeFormat();
        lv_roller_set_selected(objects.settings_roller_tformat,
                               (strcmp(fmt, "24") == 0) ? 1 : 0, LV_ANIM_OFF);
    }
}

// ============================================================
// Selection highlight
// ============================================================

void SettingsApp::updateSelection() {
    for (int i = 0; i < MENU_COUNT; i++) {
        if (!_containers[i]) continue;

        if (_editing && i == _sel) {
            lv_obj_add_state(_containers[i], LV_STATE_CHECKED);
            lv_obj_remove_state(_containers[i], LV_STATE_FOCUS_KEY);
        } else {
            lv_obj_remove_state(_containers[i], LV_STATE_CHECKED);
            if (i == _sel)
                lv_obj_add_state(_containers[i], LV_STATE_FOCUS_KEY);
            else
                lv_obj_remove_state(_containers[i], LV_STATE_FOCUS_KEY);
        }
    }

    if (_containers[_sel] && objects.settings) {
        lv_obj_scroll_to_view(_containers[_sel], LV_ANIM_ON);
    }
}

// ============================================================
// Edit mode
// ============================================================

void SettingsApp::enterEdit() {
    if (_sel == 6) {
        _on_support_screen = true;
        if (!objects.support) {
            create_screen_support();
        }
        loadScreen(SCREEN_ID_SUPPORT);
        return;
    }
    if (!isEditable(_sel)) return;

    _editing = true;
    updateSelection();

    if (_sel == 0 && objects.settings_textarea_devicename) {
        lv_obj_add_state(objects.settings_textarea_devicename, LV_STATE_FOCUSED);
        lv_obj_add_state(objects.settings_textarea_devicename, LV_STATE_CHECKED);
    }
    if (_sel == 1 && objects.settings_slider_brightness) {
        lv_obj_add_state(objects.settings_slider_brightness, LV_STATE_CHECKED);
    }
    if (_sel == 2 && objects.settings_slider_tone) {
        lv_obj_add_state(objects.settings_slider_tone, LV_STATE_CHECKED);
    }
    if (_sel == 3 && objects.settings_roller_tformat) {
        lv_obj_add_state(objects.settings_roller_tformat, LV_STATE_CHECKED);
    }
}

void SettingsApp::exitEdit(bool save) {
    if (!_editing) return;

    if (save) {
        switch (_sel) {
            case 0:
                if (objects.settings_textarea_devicename) {
                    ConfigManager::set("device_name",
                        lv_textarea_get_text(objects.settings_textarea_devicename));
                }
                break;
            case 1:
                saveBrightness();
                break;
            case 2: // Tone volume
                if (objects.settings_slider_tone) {
                    int pct = lv_bar_get_value(objects.settings_slider_tone);
                    int vol = pct * 255 / 100;
                    M5.Speaker.setVolume(vol);
                    char vbuf[8];
                    snprintf(vbuf, sizeof(vbuf), "%d", vol);
                    ConfigManager::set("tone", vbuf);
                }
                break;
            case 3:
                if (objects.settings_roller_tformat) {
                    uint32_t sel = lv_roller_get_selected(objects.settings_roller_tformat);
                    ConfigManager::set("time_format", sel == 1 ? "24" : "12");
                }
                break;
        }
    } else {
        // Cancel - revert to saved values
        loadValues();
        if (_sel == 1) {
            int bright = atoi(ConfigManager::getBrightness());
            if (bright < 25) bright = 25;
            if (bright > 255) bright = 255;
            M5.Display.setBrightness(bright);
        }
        if (_sel == 2) {
            int vol = atoi(ConfigManager::getTone());
            if (vol < 0) vol = 0;
            if (vol > 255) vol = 255;
            M5.Speaker.setVolume(vol);
        }
    }

    _editing = false;

    if (objects.settings_textarea_devicename) {
        lv_obj_remove_state(objects.settings_textarea_devicename, LV_STATE_FOCUSED);
        lv_obj_remove_state(objects.settings_textarea_devicename, LV_STATE_CHECKED);
    }
    if (objects.settings_slider_brightness) {
        lv_obj_remove_state(objects.settings_slider_brightness, LV_STATE_CHECKED);
    }
    if (objects.settings_slider_tone) {
        lv_obj_remove_state(objects.settings_slider_tone, LV_STATE_CHECKED);
    }
    if (objects.settings_roller_tformat) {
        lv_obj_remove_state(objects.settings_roller_tformat, LV_STATE_CHECKED);
    }

    updateSelection();
}

void SettingsApp::saveBrightness() {
    if (!objects.settings_slider_brightness) return;
    int pct = lv_bar_get_value(objects.settings_slider_brightness);
    int bright = pct * 255 / 100;
    M5.Display.setBrightness(bright);

    char buf[8];
    snprintf(buf, sizeof(buf), "%d", bright);
    ConfigManager::set("brightness", buf);

    if (objects.settings_label_brightness) {
        snprintf(buf, sizeof(buf), "%d%%", pct);
        lv_label_set_text(objects.settings_label_brightness, buf);
    }
}

void SettingsApp::handleEditKey(char key) {
    switch (_sel) {
        case 0: // Device name
            if (objects.settings_textarea_devicename) {
                if (key == 0x08) {
                    lv_textarea_delete_char(objects.settings_textarea_devicename);
                } else if (key >= 32 && key < 127) {
                    char s[2] = {key, 0};
                    lv_textarea_add_text(objects.settings_textarea_devicename, s);
                }
            }
            break;

        case 1: // Brightness
            if (objects.settings_slider_brightness) {
                int val = lv_bar_get_value(objects.settings_slider_brightness);
                if (key == ';') val += 10;
                else if (key == '.') val -= 10;
                if (val < 10) val = 10;
                if (val > 100) val = 100;
                lv_bar_set_value(objects.settings_slider_brightness, val, LV_ANIM_OFF);
                M5.Display.setBrightness(val * 255 / 100);

                if (objects.settings_label_brightness) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "%d%%", val);
                    lv_label_set_text(objects.settings_label_brightness, buf);
                }
            }
            break;

        case 2: // Tone volume (;/. to adjust)
            if (objects.settings_slider_tone) {
                int val = lv_bar_get_value(objects.settings_slider_tone);
                if (key == ';') val += 10;
                else if (key == '.') val -= 10;
                if (val < 0) val = 0;
                if (val > 100) val = 100;
                lv_bar_set_value(objects.settings_slider_tone, val, LV_ANIM_OFF);
                M5.Speaker.setVolume(val * 255 / 100);

                if (objects.settings_label_tone) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "%d%%", val);
                    lv_label_set_text(objects.settings_label_tone, buf);
                }
            }
            break;

        case 3: // Time format roller (infinite)
            if (objects.settings_roller_tformat) {
                uint32_t cnt = lv_roller_get_option_count(objects.settings_roller_tformat);
                uint32_t sel = lv_roller_get_selected(objects.settings_roller_tformat);
                if (key == ';') sel = (sel + cnt - 1) % cnt;
                else if (key == '.') sel = (sel + 1) % cnt;
                lv_roller_set_selected(objects.settings_roller_tformat, sel, LV_ANIM_ON);
            }
            break;
    }
}

// ============================================================
// Keyboard input
// ============================================================

void SettingsApp::onKeyPressed(char key) {
    // Back from support screen
    if (_on_support_screen) {
        if (key == '`' || key == '\n') {
            playTone(TONE_BACK);
            _on_support_screen = false;
            loadScreen(SCREEN_ID_SETTINGS);
            mapContainers(_containers, MENU_COUNT);
            loadValues();
            updateSelection();

            // Re-trigger entrance animation
            for (int i = 0; i < MENU_COUNT; i++) {
                if (_containers[i]) {
                    lv_obj_set_style_translate_x(_containers[i], ENTRANCE_OFFSET, 0);
                    lv_obj_set_style_opa(_containers[i], 0, 0);
                }
            }
            _entrance.init();
            _entrance.play();
            _entering = true;
        }
        return;
    }

    // Back / cancel
    if (key == '`') {
        playTone(TONE_BACK);
        if (_editing) {
            exitEdit(false);
        } else {
            if (_back_app) _manager.switchApp(_back_app);
        }
        return;
    }

    if (_editing) {
        if (key == '\n') {
            playTone(TONE_OK);
            exitEdit(true);
        } else {
            playTone(TONE_NAV);
            handleEditKey(key);
        }
        return;
    }

    // Navigation
    switch (key) {
        case ';':
            playTone(TONE_NAV);
            if (_containers[_sel])
                lv_obj_remove_local_style_prop(_containers[_sel], LV_STYLE_TRANSLATE_X, 0);
            _prev_sel = _sel;
            _sel = (_sel - 1 + MENU_COUNT) % MENU_COUNT;
            updateSelection();
            _sel_bounce.teleport(SEL_BOUNCE_PX);
            _sel_bounce.move(0.0f);
            break;
        case '.':
            playTone(TONE_NAV);
            if (_containers[_sel])
                lv_obj_remove_local_style_prop(_containers[_sel], LV_STYLE_TRANSLATE_X, 0);
            _prev_sel = _sel;
            _sel = (_sel + 1) % MENU_COUNT;
            updateSelection();
            _sel_bounce.teleport(SEL_BOUNCE_PX);
            _sel_bounce.move(0.0f);
            break;
        case '\n':
            playTone(TONE_OK);
            enterEdit();
            break;
    }
}
