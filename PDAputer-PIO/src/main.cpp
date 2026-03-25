#include <Arduino.h>

#include <M5Cardputer.h>
#include <lvgl.h>
#include "lvgl_setup.h"
#include <ui.h>
#include <smooth_ui_toolkit.h>
#include "app_manager/app_manager.h"
#include "apps/boot/boot_app.h"
#include "apps/main_menu/main_menu_app.h"
#include "apps/fm_radio/fm_radio_app.h"
#include "apps/music/music_app.h"
#include "apps/settings/settings_app.h"
#include "apps/calendar/calendar_app.h"
#include <battery_manager.h>
#include <keyboard_manager.h>

// https://www.youtube.com/nishad2m8
// https://buymeacoffee.com/nishad2m8

AppManager appManager;
BootApp bootApp(appManager);
MainMenuApp mainMenuApp(appManager);
FMRadioApp fmRadioApp(appManager);
MusicApp musicApp(appManager);
SettingsApp settingsApp(appManager);
CalendarApp calendarApp(appManager);


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

    // Initialize app manager and wire up navigation
    appManager.init();
    bootApp.setNextApp(&mainMenuApp);

    // Music: index 1
    musicApp.setBackApp(&mainMenuApp);
    mainMenuApp.setAppTarget(1, &musicApp);

    // FM Radio: index 3
    fmRadioApp.setBackApp(&mainMenuApp);
    mainMenuApp.setAppTarget(3, &fmRadioApp);

    // Calendar: index 8
    calendarApp.setBackApp(&mainMenuApp);
    mainMenuApp.setAppTarget(8, &calendarApp);

    // Settings: index 10
    settingsApp.setBackApp(&mainMenuApp);
    mainMenuApp.setAppTarget(10, &settingsApp);

    BatteryManager::begin();

    // Keyboard manager — translates raw M5 keys to standard codes
    KeyboardManager::begin([](char key) {
        appManager.handleKey(key);
    });

    appManager.startApp(&bootApp);
    Serial.println("[BOOT] AppManager started (boot -> main menu)");

    // FreeRTOS task for LVGL tick on core 1
    xTaskCreatePinnedToCore(lv_tick_task, "lv_tick", 4096, NULL, 5, NULL, 1);
    Serial.println("[BOOT] LVGL tick task created on core 1");
}

void loop() {
    M5Cardputer.update();
    KeyboardManager::update();

    // Update app logic + LVGL rendering (single task, no mutex needed)
    appManager.update();
    lv_timer_handler();

    delay(5);
}
