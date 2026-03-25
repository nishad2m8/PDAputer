#pragma once

#include "../../app_manager/app_base.h"
#include "../../app_manager/app_manager.h"
#include <smooth_ui_toolkit.h>
#include <lvgl.h>

using namespace smooth_ui_toolkit;

// Icon slot position definition
struct SlotPos {
    int16_t x, y;
    uint16_t scale;
};

// App entry definition
struct AppDef {
    const char* label;
    uint32_t panel_color;
    uint32_t label_color;
};

class MainMenuApp : public AppBase {
public:
    MainMenuApp(AppManager& manager) : _manager(manager) {}

    void setAppTarget(int index, AppBase* app);

    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
    void onKeyPressed(char key) override;
    const char* getName() override { return "MainMenu"; }

private:
    AppManager& _manager;

    static const int APP_COUNT = 11;
    AppBase* _app_targets[APP_COUNT] = {};

    lv_obj_t* _icons[APP_COUNT];
    int _selected_index = 2;

    // Scroll animation
    Animate _scroll_anim;
    bool _is_scrolling = false;
    int _anim_from[APP_COUNT];
    int _anim_to[APP_COUNT];

    // Label bounce animation
    AnimateValue _label_x;

    // Panel Y bounce animation
    AnimateValue _panel_y;

    void scrollLeft();
    void scrollRight();
    void setupScrollAnimation(int old_sel, int new_sel, int dir);
    void applyPositions(float progress);
    void setRestPositions();
    void updateLabel();
    void updatePanelColor();
    void updateStatusIcons();

    bool _muted = false;
    int  _saved_volume = 128;
};
