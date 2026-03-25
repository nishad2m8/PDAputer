#include "battery_manager.h"
#include <M5Cardputer.h>

namespace BatteryManager {

static int      s_level    = -1;
static bool     s_charging = false;
static float    s_voltage  = 0.0f;
static uint32_t s_last_ms  = 0;

// Minimum interval between hardware reads (ms)
static constexpr uint32_t UPDATE_INTERVAL = 2000;

void begin() {
    update();
}

void update() {
    uint32_t now = millis();
    if (s_level >= 0 && (now - s_last_ms) < UPDATE_INTERVAL) return;
    s_last_ms = now;

    s_level    = M5Cardputer.Power.getBatteryLevel();
    s_charging = M5Cardputer.Power.isCharging();
    s_voltage  = M5Cardputer.Power.getBatteryVoltage() / 1000.0f;
}

int getLevel() {
    return s_level;
}

bool isCharging() {
    return s_charging;
}

float getVoltage() {
    return s_voltage;
}

} // namespace BatteryManager
