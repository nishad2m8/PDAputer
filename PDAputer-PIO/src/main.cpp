#include <Arduino.h>
#include <array>
#include <algorithm>

#include <M5Cardputer.h>
#include <lvgl.h>
#include "lvgl_setup.h"
#include <ui.h>
#include <smooth_ui_toolkit.h>
#include "app_manager/app_manager.h"
#include "apps/boot/boot_app.h"
#include "apps/main_menu/main_menu_app.h"

// https://www.youtube.com/nishad2m8
// https://buymeacoffee.com/nishad2m8

AppManager appManager;
BootApp bootApp(appManager);
MainMenuApp mainMenuApp(appManager);

namespace {
    std::array<bool, 256> s_prev_keymap{};

    inline bool hasKeyPressed(const std::array<bool, 256>& map) {
        return std::any_of(map.begin(), map.end(), [](bool v) { return v; });
    }

    void processKeyboardInput() {
        auto& status = M5Cardputer.Keyboard.keysState();
        auto& klist  = M5Cardputer.Keyboard.keyList();

        std::array<bool, 256> current{};
        auto markKey = [&](char key) {
            if (key == 0) return;
            current[static_cast<uint8_t>(key)] = true;
        };

        for (auto c : status.word) {
            markKey(c);
        }

        if (!hasKeyPressed(current)) {
            for (const auto& pos : klist) {
                markKey((char)M5Cardputer.Keyboard.getKey(pos));
            }
        }

        if (current != s_prev_keymap) {
            size_t pressedCount = std::count(current.begin(), current.end(), true);
            Serial.printf("[KB] pressed=%u word=%u raw=%u mods=0x%02X caps=%d\n",
                          (unsigned)pressedCount,
                          (unsigned)status.word.size(),
                          (unsigned)klist.size(),
                          status.modifiers,
                          M5Cardputer.Keyboard.capslocked() ? 1 : 0);
        }

        for (size_t idx = 0; idx < current.size(); ++idx) {
            if (current[idx] && !s_prev_keymap[idx]) {
                char key = (char)idx;
                Serial.printf("[KB] dispatch '%c' (0x%02X)\n",
                              (key >= 32 && key < 127) ? key : '.',
                              (uint8_t)key);
                appManager.handleKey(key);
            }
        }

        s_prev_keymap = current;
    }
} // namespace

void setup() {
    Serial.begin(115200);
    Serial.println("[BOOT] setup start");

    // M5Cardputer setup (begin() inits M5Unified + keyboard)
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    M5Cardputer.begin(cfg, true);
    Serial.println("[BOOT] M5Cardputer.begin done (keyboard enabled)");

    M5.Display.setRotation(1);
    M5.Display.setBrightness(128);

    // LVGL setup
    lvgl_setup();
    ui_init();
    Serial.println("[BOOT] LVGL + UI initialized");

    // Register millis() as SUT HAL tick source
    smooth_ui_toolkit::ui_hal::on_get_tick([]() -> uint32_t {
        return (uint32_t)millis();
    });

    // Initialize app manager and start boot -> main menu
    appManager.init();
    bootApp.setNextApp(&mainMenuApp);
    appManager.startApp(&bootApp);
    Serial.println("[BOOT] AppManager started (boot -> main menu)");

    // FreeRTOS task for LVGL tick on core 1
    xTaskCreatePinnedToCore(lv_tick_task, "lv_tick", 4096, NULL, 5, NULL, 1);
    Serial.println("[BOOT] LVGL tick task created on core 1");
}

void loop() {
    M5Cardputer.update();
    processKeyboardInput();

    // Update app logic + LVGL rendering (single task, no mutex needed)
    appManager.update();
    lv_timer_handler();

    delay(5);
}
