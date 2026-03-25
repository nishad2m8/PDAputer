#include "calendar_app.h"
#include <ui.h>
#include <lvgl.h>
#include <Arduino.h>
#include <M5Cardputer.h>
#include <time_manager.h>
#include <config_manager.h>

void CalendarApp::onCreate() {
    // Screen is not created at boot — create it on demand
    if (!objects.calendar) {
        create_screen_calendar();
    }
    loadScreen(SCREEN_ID_CALENDAR);
    updateCalendar();
}

void CalendarApp::onUpdate() {}

void CalendarApp::onDestroy() {}

void CalendarApp::onKeyPressed(char key) {
    if (key == '`') {
        if (atoi(ConfigManager::getTone()) > 0) M5.Speaker.tone(3000, 20);
        if (_back_app) _manager.switchApp(_back_app);
    }
}

void CalendarApp::updateCalendar() {
    if (!objects.calendar_calendar) return;

    int year  = TimeManager::getYear();
    int month = TimeManager::getMonth();
    int day   = TimeManager::getDay();

    lv_calendar_set_today_date(objects.calendar_calendar, year, month, day);
    lv_calendar_set_month_shown(objects.calendar_calendar, year, month);

    // Override today's border color via custom draw event
    // The calendar hardcodes border color from theme primary, so we override it
    lv_obj_t* btnm = lv_calendar_get_btnmatrix(objects.calendar_calendar);
    if (btnm) {
        lv_obj_add_event_cb(btnm, [](lv_event_t* e) {
            lv_draw_task_t* draw_task = lv_event_get_draw_task(e);
            lv_draw_dsc_base_t* base_dsc = (lv_draw_dsc_base_t*)lv_draw_task_get_draw_dsc(draw_task);
            if (base_dsc->part != LV_PART_ITEMS) return;

            uint32_t id = base_dsc->id1;
            lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
            if (lv_buttonmatrix_has_button_ctrl(obj, id, LV_BUTTONMATRIX_CTRL_CUSTOM_1)) {
                lv_draw_border_dsc_t* border_dsc = lv_draw_task_get_border_dsc(draw_task);
                if (border_dsc) {
                    border_dsc->color = lv_color_hex(0xff8e0b);
                }
            }
        }, LV_EVENT_DRAW_TASK_ADDED, NULL);
        lv_obj_add_flag(btnm, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
        lv_obj_set_style_pad_row(btnm, 0, 0);
        lv_obj_set_style_pad_column(btnm, 0, 0);
    }

    // Style the arrow header: hide buttons, reduce spacing
    lv_obj_t* arrow_header = lv_obj_get_child(objects.calendar_calendar, 0);
    if (arrow_header) {
        lv_obj_t* btn_left = lv_obj_get_child(arrow_header, 0);
        lv_obj_t* btn_right = lv_obj_get_child(arrow_header, 2);
        if (btn_left)  lv_obj_add_flag(btn_left, LV_OBJ_FLAG_HIDDEN);
        if (btn_right) lv_obj_add_flag(btn_right, LV_OBJ_FLAG_HIDDEN);
        // Tighten gap between title and grid
        lv_obj_set_height(arrow_header, 25);
        lv_obj_set_style_pad_bottom(arrow_header, 5, 0);
        lv_obj_set_style_pad_top(arrow_header, 5, 0);
        lv_obj_set_style_margin_bottom(arrow_header, 10, 0);
        lv_obj_set_style_margin_top(arrow_header, 5, 0);
    }
}
