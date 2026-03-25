#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>

namespace TimeManager {
    // Call after WiFi connects to start NTP sync.
    void syncNTP();

    // Call from main loop to check for late NTP sync.
    void update();

    bool   isSynced();
    String getTimeHHMM();   // respects 12/24h config
    String getTime12h();    // "h:mm AM/PM"
    String getTime24h();    // "H:mm"

    // Raw accessors for other apps
    int    getHour();       // 0-23
    int    getMinute();     // 0-59
    int    getSecond();     // 0-59

    // Calendar accessors
    int    getYear();       // e.g. 2026
    int    getMonth();      // 1-12
    int    getDay();        // 1-31
    int    getDayOfWeek();  // 0=Sun, 6=Sat

    // Calendar helpers
    int    daysInMonth(int year, int month);
    int    firstDayOfMonth(int year, int month); // 0=Sun
}

#endif // TIME_MANAGER_H
