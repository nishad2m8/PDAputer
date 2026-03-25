#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include <Arduino.h>

namespace BatteryManager {
    void begin();
    void update();           // Call periodically to refresh cached values
    int  getLevel();         // 0-100%
    bool isCharging();
    float getVoltage();
}

#endif // BATTERY_MANAGER_H
