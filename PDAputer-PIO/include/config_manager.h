#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <Arduino.h>

namespace ConfigManager {
    // Load config from SD card. Call after SDManager::begin().
    bool load();
    bool isLoaded();

    // Getters - return empty string if key not found
    const char* getDeviceName();
    const char* getWifiSSID();
    const char* getWifiPassword();
    const char* getTimezone();
    const char* getApiKey();
    const char* getTimeFormat();
    const char* getBrightness();
    const char* getTone();

    // Generic key lookup
    const char* get(const char* key, const char* defaultVal = "");

    // Write a key=value back to config.txt on SD
    bool set(const char* key, const char* value);
}

#endif // CONFIG_MANAGER_H
