#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_BOOT = 1,
    SCREEN_ID_MAIN = 2,
    _SCREEN_ID_LAST = 2
};

typedef struct _objects_t {
    lv_obj_t *boot;
    lv_obj_t *main;
    lv_obj_t *boot_label_name;
    lv_obj_t *boot_label_contributtion;
    lv_obj_t *main_image_bg;
    lv_obj_t *main_panel_menu_selected;
    lv_obj_t *main_container_left;
    lv_obj_t *main_label_time;
    lv_obj_t *main_container_right;
    lv_obj_t *main_image_wifi;
    lv_obj_t *main_image_battery;
    lv_obj_t *main_bar_battery;
    lv_obj_t *main_label_battery;
    lv_obj_t *main_label_menu_selected;
    lv_obj_t *main_image_app_fmradio;
    lv_obj_t *main_image_app_webradio;
    lv_obj_t *main_image_app_music;
    lv_obj_t *main_image_app_ai;
    lv_obj_t *main_image_app_setting;
    lv_obj_t *main_image_app_games;
    lv_obj_t *main_image_app_lorachat;
    lv_obj_t *main_image_app_gps;
} objects_t;

extern objects_t objects;

void create_screen_boot();
void delete_screen_boot();
void tick_screen_boot();

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/