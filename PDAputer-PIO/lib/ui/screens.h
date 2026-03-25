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
    SCREEN_ID_FM_RADIO = 3,
    SCREEN_ID_MUSIC = 4,
    SCREEN_ID_SETTINGS = 5,
    SCREEN_ID_SUPPORT = 6,
    SCREEN_ID_WIDGETS = 7,
    SCREEN_ID_CALENDAR = 8,
    SCREEN_ID_NOTES = 9,
    _SCREEN_ID_LAST = 9
};

typedef struct _objects_t {
    lv_obj_t *boot;
    lv_obj_t *main;
    lv_obj_t *fm_radio;
    lv_obj_t *music;
    lv_obj_t *settings;
    lv_obj_t *support;
    lv_obj_t *widgets;
    lv_obj_t *calendar;
    lv_obj_t *notes;
    lv_obj_t *boot_label_name;
    lv_obj_t *boot_label_contributtion;
    lv_obj_t *main_image_bg;
    lv_obj_t *main_panel_menu_selected;
    lv_obj_t *main_container_left;
    lv_obj_t *main_label_time;
    lv_obj_t *main_container_right;
    lv_obj_t *main_image_tone;
    lv_obj_t *main_image_sdcard;
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
    lv_obj_t *main_image_app_calendar;
    lv_obj_t *main_image_app_notes;
    lv_obj_t *main_image_app_remote;
    lv_obj_t *main_container_date;
    lv_obj_t *main_label_date;
    lv_obj_t *fmradio_line_02;
    lv_obj_t *fmradio_line_01;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *fmradio_label_min;
    lv_obj_t *fmradio_label_max;
    lv_obj_t *fmradio_container_stations;
    lv_obj_t *fmradio_label_pre1;
    lv_obj_t *fmradio_label_pre2;
    lv_obj_t *fmradio_label_pre3;
    lv_obj_t *fmradio_scale;
    lv_obj_t *fmradio_label_main;
    lv_obj_t *fmradio_label_sub;
    lv_obj_t *fmradio_container_signal;
    lv_obj_t *fmradio_label_mode;
    lv_obj_t *fmradio_label_most;
    lv_obj_t *fmradio_bar_signal;
    lv_obj_t *fmradio_bar_battery;
    lv_obj_t *fmradio_image_signal;
    lv_obj_t *fmradio_image_headphone;
    lv_obj_t *fmradio_image_battery;
    lv_obj_t *fmradio_image_playpause;
    lv_obj_t *music_label_name;
    lv_obj_t *music_label_album_artist;
    lv_obj_t *music_bar_time;
    lv_obj_t *music_vinyl_disk;
    lv_obj_t *music_label_time;
    lv_obj_t *music_panel_controlls;
    lv_obj_t *music_image_previous;
    lv_obj_t *music_image_play_pause;
    lv_obj_t *music_image_next;
    lv_obj_t *music_image_shuffle;
    lv_obj_t *music_arc_volume;
    lv_obj_t *music_label_track_nos;
    lv_obj_t *settings_container_devicename;
    lv_obj_t *settings_label_device_;
    lv_obj_t *settings_textarea_devicename;
    lv_obj_t *settings_container_brightness;
    lv_obj_t *settings_slider_brightness;
    lv_obj_t *settings_label_brightness;
    lv_obj_t *settings_container_tone;
    lv_obj_t *settings_slider_tone;
    lv_obj_t *settings_label_tone;
    lv_obj_t *settings_container_tformat;
    lv_obj_t *settings_roller_tformat;
    lv_obj_t *settings_container_tzone;
    lv_obj_t *settings_label_tzone;
    lv_obj_t *settings_container_ssid;
    lv_obj_t *settings_label_ssid;
    lv_obj_t *settings_container_support;
    lv_obj_t *obj2;
    lv_obj_t *about_label_details;
    lv_obj_t *about_label_details_1;
    lv_obj_t *main_label_moonphase;
    lv_obj_t *obj3;
    lv_obj_t *main_container_weather;
    lv_obj_t *main_canvas_weather_icon;
    lv_obj_t *main_label_temp;
    lv_obj_t *main_label_time_2;
    lv_obj_t *main_label_time_3;
    lv_obj_t *main_canvas_moon_icon;
    lv_obj_t *calendar_calendar;
} objects_t;

extern objects_t objects;

void create_screen_boot();
void delete_screen_boot();
void tick_screen_boot();

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_fm_radio();
void delete_screen_fm_radio();
void tick_screen_fm_radio();

void create_screen_music();
void delete_screen_music();
void tick_screen_music();

void create_screen_settings();
void delete_screen_settings();
void tick_screen_settings();

void create_screen_support();
void delete_screen_support();
void tick_screen_support();

void create_screen_widgets();
void delete_screen_widgets();
void tick_screen_widgets();

void create_screen_calendar();
void delete_screen_calendar();
void tick_screen_calendar();

void create_screen_notes();
void delete_screen_notes();
void tick_screen_notes();

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/