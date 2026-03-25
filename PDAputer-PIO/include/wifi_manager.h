#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

namespace WifiManager {
    // Start non-blocking connection using ConfigManager credentials.
    // Call after ConfigManager::load().
    void begin();

    // Call from main loop - handles connection state machine + NTP sync.
    void update();

    bool isConnected();
    int  getRSSI();         // signal strength in dBm
    int  getSignalLevel();  // 0-4 (0=none, 1=weak..4=strong)
}

#endif // WIFI_MANAGER_H
