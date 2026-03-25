#pragma once

#include "../../app_manager/app_base.h"
#include "../../app_manager/app_manager.h"
#include <lvgl.h>

class CalendarApp : public AppBase {
public:
    CalendarApp(AppManager& manager) : _manager(manager) {}

    void setBackApp(AppBase* back) { _back_app = back; }

    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
    void onKeyPressed(char key) override;
    const char* getName() override { return "Calendar"; }

private:
    AppManager& _manager;
    AppBase* _back_app = nullptr;

    void updateCalendar();
};
