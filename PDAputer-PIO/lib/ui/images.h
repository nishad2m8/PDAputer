#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_element_01;
extern const lv_img_dsc_t img_element_02;
extern const lv_img_dsc_t img_element_03;
extern const lv_img_dsc_t img_bg;
extern const lv_img_dsc_t img_battery;
extern const lv_img_dsc_t img_icon_ai;
extern const lv_img_dsc_t img_icon_fmradio;
extern const lv_img_dsc_t img_icon_music;
extern const lv_img_dsc_t img_icon_setting;
extern const lv_img_dsc_t img_icon_webradio;
extern const lv_img_dsc_t img_icon_wifi;
extern const lv_img_dsc_t img_icon_games;
extern const lv_img_dsc_t img_icon_gps;
extern const lv_img_dsc_t img_icon_lorachat;
extern const lv_img_dsc_t img_sunny;
extern const lv_img_dsc_t img_waxing_gibbous;
extern const lv_img_dsc_t img_mask;
extern const lv_img_dsc_t img_icon_battery;
extern const lv_img_dsc_t img_icon_headphone;
extern const lv_img_dsc_t img_icon_pause;
extern const lv_img_dsc_t img_icon_play;
extern const lv_img_dsc_t img_icon_signal;
extern const lv_img_dsc_t img_signal_indicator;
extern const lv_img_dsc_t img_signal_main;
extern const lv_img_dsc_t img_volume_indicator;
extern const lv_img_dsc_t img_volume_main;
extern const lv_img_dsc_t img_vinyl_disk;
extern const lv_img_dsc_t img_music_next;
extern const lv_img_dsc_t img_music_pause;
extern const lv_img_dsc_t img_music_play;
extern const lv_img_dsc_t img_music_previous;
extern const lv_img_dsc_t img_music_repeat;
extern const lv_img_dsc_t img_music_shuffle;
extern const lv_img_dsc_t img_sd_card_01;
extern const lv_img_dsc_t img_sd_card_00;
extern const lv_img_dsc_t img_tone_00;
extern const lv_img_dsc_t img_tone_01;
extern const lv_img_dsc_t img_wifi_00;
extern const lv_img_dsc_t img_wifi_01;
extern const lv_img_dsc_t img_wifi_02;
extern const lv_img_dsc_t img_wifi_03;
extern const lv_img_dsc_t img_wifi_04;
extern const lv_img_dsc_t img_bc;
extern const lv_img_dsc_t img_heart;
extern const lv_img_dsc_t img_icon_calendar;
extern const lv_img_dsc_t img_icon_note;
extern const lv_img_dsc_t img_icon_remote;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[47];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/