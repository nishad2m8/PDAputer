#pragma once

#include "../../app_manager/app_base.h"
#include "../../app_manager/app_manager.h"
#include <lvgl.h>
#include <smooth_ui_toolkit.h>

using namespace smooth_ui_toolkit;

class SettingsApp : public AppBase {
public:
    SettingsApp(AppManager& manager) : _manager(manager) {}

    void setBackApp(AppBase* back) { _back_app = back; }

    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
    void onKeyPressed(char key) override;
    const char* getName() override { return "Settings"; }

private:
    AppManager& _manager;
    AppBase* _back_app = nullptr;

    // Menu: 0=device_name, 1=brightness, 2=tone, 3=timezone, 4=time_format, 5=wifi, 6=support
    static constexpr int MENU_COUNT = 7;
    int _sel = 0;
    bool _editing = false;
    bool _on_support_screen = false;

    // Containers for visual feedback
    lv_obj_t* _containers[MENU_COUNT] = {};

    void loadValues();
    void updateSelection();
    void enterEdit();
    void exitEdit(bool save);
    void handleEditKey(char key);
    void saveBrightness();

    // Animations
    Animate _entrance;
    bool _entering = false;
    AnimateValue _sel_bounce;
    int _prev_sel = 0;
};
