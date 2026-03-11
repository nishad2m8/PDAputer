#include "boot_app.h"
#include <ui.h>
#include <lvgl.h>
#include <Arduino.h>
#include <M5Cardputer.h>

char BootApp::randomChar() {
    static const char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*";
    return chars[random(0, sizeof(chars) - 1)];
}

void BootApp::onCreate() {
    // Hide labels initially for animation
    lv_label_set_text(objects.boot_label_name, "");
    lv_label_set_text(objects.boot_label_contributtion, "");

    // Setup typing animation for "PDAputer"
    _name_anim.easingOptions().duration = 1.2f;
    _name_anim.easingOptions().easingFunction = ease::ease_out_cubic;
    _name_anim.start = 0;
    _name_anim.end = (float)NAME_LEN;
    _name_anim.delay = 0.3f;
    _name_anim.init();
    _name_anim.play();

    _phase = PHASE_TYPING_NAME;
}

void BootApp::onUpdate() {
    switch (_phase) {
        case PHASE_TYPING_NAME:
            updateTypingName();
            break;
        case PHASE_FORMING_CONTRIBUTION:
            updateFormingContribution();
            break;
        case PHASE_WAITING:
            updateWaiting();
            break;
        case PHASE_DONE:
            break;
    }
}

void BootApp::onDestroy() {
}

void BootApp::updateTypingName() {
    _name_anim.update();

    int chars_to_show = (int)_name_anim.value();
    if (chars_to_show < 0) chars_to_show = 0;
    if (chars_to_show > NAME_LEN) chars_to_show = NAME_LEN;

    // Play tone when a new character appears
    if (chars_to_show > _last_name_chars) {
        _last_name_chars = chars_to_show;
        M5.Speaker.tone(TONE_BASE + chars_to_show * TONE_STEP, TONE_MS);
    }

    char buf[16];
    strncpy(buf, NAME_TEXT, chars_to_show);
    buf[chars_to_show] = '_';
    buf[chars_to_show + 1] = '\0';
    lv_label_set_text(objects.boot_label_name, buf);

    if (_name_anim.done()) {
        lv_label_set_text(objects.boot_label_name, NAME_TEXT);

        // Setup random forming animation for "nishad2m8"
        _contrib_anim.easingOptions().duration = 1.5f;
        _contrib_anim.easingOptions().easingFunction = ease::ease_in_out_cubic;
        _contrib_anim.start = 0;
        _contrib_anim.end = (float)CONTRIB_LEN;
        _contrib_anim.delay = 0.2f;
        _contrib_anim.init();
        _contrib_anim.play();

        // Fill buffer with random chars
        for (int i = 0; i < CONTRIB_LEN; i++) {
            _contrib_buf[i] = randomChar();
        }
        _contrib_buf[CONTRIB_LEN] = '\0';
        lv_label_set_text(objects.boot_label_contributtion, _contrib_buf);

        _last_random_update = millis();
        _phase = PHASE_FORMING_CONTRIBUTION;
    }
}

void BootApp::updateFormingContribution() {
    _contrib_anim.update();

    float progress = _contrib_anim.value();
    int locked = (int)progress;
    if (locked < 0) locked = 0;
    if (locked > CONTRIB_LEN) locked = CONTRIB_LEN;

    uint32_t now = millis();
    bool should_randomize = (now - _last_random_update) > 50;

    for (int i = 0; i < CONTRIB_LEN; i++) {
        if (i < locked) {
            _contrib_buf[i] = CONTRIB_TEXT[i];
        } else if (should_randomize) {
            _contrib_buf[i] = randomChar();
        }
    }

    if (should_randomize) {
        _last_random_update = now;
    }

    _contrib_buf[CONTRIB_LEN] = '\0';
    lv_label_set_text(objects.boot_label_contributtion, _contrib_buf);

    if (_contrib_anim.done()) {
        lv_label_set_text(objects.boot_label_contributtion, CONTRIB_TEXT);
        _wait_start = millis();
        _phase = PHASE_WAITING;
    }
}

void BootApp::updateWaiting() {
    if (millis() - _wait_start >= WAIT_DURATION_MS) {
        loadScreen(SCREEN_ID_MAIN);
        if (_next_app) {
            _manager.switchApp(_next_app);
        }
        _phase = PHASE_DONE;
    }
}
