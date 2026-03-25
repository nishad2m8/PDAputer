#pragma once

#include "../../app_manager/app_base.h"
#include "../../app_manager/app_manager.h"
#include "radio_manager.h"
#include <lvgl.h>

class FMRadioApp : public AppBase {
public:
    FMRadioApp(AppManager& manager) : _manager(manager) {}

    void setBackApp(AppBase* back) { _back_app = back; }

    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
    void onKeyPressed(char key) override;
    const char* getName() override { return "FMRadio"; }

private:
    AppManager& _manager;
    AppBase* _back_app = nullptr;
    RadioManager _radio;
    bool _radio_initialized = false;
    lv_timer_t* _tmr_radio = nullptr;

    // Frequency scale constants
    static constexpr int      SCALE_LINES            = 30;
    static constexpr int      SCALE_LINE_WIDTH       = 2;
    static constexpr int      SCALE_PAD_LR           = 5;
    static constexpr int      SCALE_MIN_HEIGHT       = 2;
    static constexpr int      SCALE_MAX_HEIGHT       = 22;
    static constexpr float    SCALE_CURVE_SIGMA_MHZ  = 1.5f;
    static constexpr uint32_t SCALE_COLOR_ACTIVE_HEX = 0xFFFF00;
    static constexpr uint32_t SCALE_COLOR_CURVE_HEX  = 0xFFFF00;
    static constexpr uint32_t SCALE_COLOR_BACK_HEX   = 0x353535;

    // Scale line storage (persisted for lv_line pointer lifetime)
    lv_point_precise_t _scale_pts[SCALE_LINES][2];
    lv_point_precise_t _scale_bg_pts[SCALE_LINES][2];
    lv_obj_t* _scale_lines[SCALE_LINES] = {};
    int _active_scale_line = -1;

    // Preset label shortcuts
    lv_obj_t* _preset_objs[3] = {};

    // Scale management
    void createScaleLines();
    void updateScale(float freq, float minFreq, float maxFreq);

    // UI helpers
    void updatePlaybackStatusUI();
    void updateBatteryBar();
    void onRadioTimerUpdate();

    // LVGL timer callback (static, forwards to instance)
    static void radioTimerCb(lv_timer_t* t);
};
