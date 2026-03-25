#include "wifi_manager.h"
#include "config_manager.h"
#include "time_manager.h"
#include <WiFi.h>

namespace WifiManager {

enum State { IDLE, CONNECTING, CONNECTED, FAILED };

static State    s_state = IDLE;
static uint32_t s_connect_start = 0;
static uint32_t s_last_retry = 0;

static constexpr uint32_t CONNECT_TIMEOUT_MS = 15000;
static constexpr uint32_t RETRY_INTERVAL_MS  = 30000;

void begin() {
    const char* ssid = ConfigManager::getWifiSSID();
    const char* pass = ConfigManager::getWifiPassword();

    if (ssid[0] == '\0') {
        Serial.println("[WIFI] No SSID configured, skip");
        s_state = FAILED;
        return;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    s_state = CONNECTING;
    s_connect_start = millis();
    Serial.printf("[WIFI] Connecting to %s...\n", ssid);
}

void update() {
    // Let TimeManager check for late NTP sync
    if (s_state == CONNECTED) {
        TimeManager::update();
    }

    if (s_state == CONNECTING) {
        if (WiFi.status() == WL_CONNECTED) {
            s_state = CONNECTED;
            Serial.printf("[WIFI] Connected! IP: %s RSSI: %d\n",
                          WiFi.localIP().toString().c_str(), WiFi.RSSI());
            TimeManager::syncNTP();
        } else if (millis() - s_connect_start > CONNECT_TIMEOUT_MS) {
            s_state = FAILED;
            WiFi.disconnect();
            s_last_retry = millis();
            Serial.println("[WIFI] Connection timeout");
        }
    }

    if (s_state == CONNECTED && WiFi.status() != WL_CONNECTED) {
        s_state = FAILED;
        s_last_retry = millis();
        Serial.println("[WIFI] Disconnected");
    }

    // Auto-retry
    if (s_state == FAILED && millis() - s_last_retry > RETRY_INTERVAL_MS) {
        begin();
    }
}

bool isConnected() {
    return s_state == CONNECTED && WiFi.status() == WL_CONNECTED;
}

int getRSSI() {
    if (!isConnected()) return -100;
    return WiFi.RSSI();
}

int getSignalLevel() {
    if (!isConnected()) return 0;
    int rssi = WiFi.RSSI();
    if (rssi >= -55) return 4;
    if (rssi >= -65) return 3;
    if (rssi >= -75) return 2;
    if (rssi >= -85) return 1;
    return 0;
}

} // namespace WifiManager
