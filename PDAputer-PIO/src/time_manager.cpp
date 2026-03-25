#include "time_manager.h"
#include "config_manager.h"
#include <time.h>
#include <string.h>

namespace TimeManager {

static bool s_synced = false;

void syncNTP() {
    const char* tz = ConfigManager::getTimezone();
    if (tz[0] == '\0') tz = "UTC0";

    configTzTime(tz, "pool.ntp.org", "time.nist.gov");
    Serial.printf("[TIME] NTP sync with tz=%s\n", tz);

    uint32_t start = millis();
    while (millis() - start < 3000) {
        time_t now = time(nullptr);
        if (now > 1700000000) {
            s_synced = true;
            struct tm ti;
            localtime_r(&now, &ti);
            Serial.printf("[TIME] Synced: %02d:%02d:%02d\n",
                          ti.tm_hour, ti.tm_min, ti.tm_sec);
            return;
        }
        delay(100);
    }
    Serial.println("[TIME] NTP sync pending...");
}

void update() {
    if (s_synced) return;
    time_t now = time(nullptr);
    if (now > 1700000000) {
        s_synced = true;
        Serial.println("[TIME] NTP synced (late)");
    }
}

bool isSynced() {
    return s_synced;
}

static void getLocalTime(struct tm& ti) {
    time_t now = time(nullptr);
    localtime_r(&now, &ti);
}

int getHour() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_hour;
}

int getMinute() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_min;
}

int getSecond() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_sec;
}

String getTime24h() {
    if (!s_synced) return "--:--";
    struct tm ti;
    getLocalTime(ti);
    char buf[6];
    snprintf(buf, sizeof(buf), "%d:%02d", ti.tm_hour, ti.tm_min);
    return String(buf);
}

String getTime12h() {
    if (!s_synced) return "-- : --";
    struct tm ti;
    getLocalTime(ti);
    int hr = ti.tm_hour % 12;
    if (hr == 0) hr = 12;
    char buf[12];
    snprintf(buf, sizeof(buf), "%d:%02d %s",
             hr, ti.tm_min, ti.tm_hour >= 12 ? "PM" : "AM");
    return String(buf);
}

String getTimeHHMM() {
    if (!s_synced) return "--:--";
    struct tm ti;
    getLocalTime(ti);

    bool use24 = (strcmp(ConfigManager::getTimeFormat(), "24") == 0);
    char buf[6];
    if (use24) {
        snprintf(buf, sizeof(buf), "%d:%02d", ti.tm_hour, ti.tm_min);
    } else {
        int hr = ti.tm_hour % 12;
        if (hr == 0) hr = 12;
        snprintf(buf, sizeof(buf), "%d:%02d", hr, ti.tm_min);
    }
    return String(buf);
}

int getYear() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_year + 1900;
}

int getMonth() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_mon + 1;
}

int getDay() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_mday;
}

int getDayOfWeek() {
    struct tm ti;
    getLocalTime(ti);
    return ti.tm_wday; // 0=Sun
}

int daysInMonth(int year, int month) {
    static const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month < 1 || month > 12) return 30;
    int d = days[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
        d = 29;
    return d;
}

int firstDayOfMonth(int year, int month) {
    struct tm ti = {};
    ti.tm_year = year - 1900;
    ti.tm_mon  = month - 1;
    ti.tm_mday = 1;
    mktime(&ti);
    return ti.tm_wday; // 0=Sun
}

} // namespace TimeManager
