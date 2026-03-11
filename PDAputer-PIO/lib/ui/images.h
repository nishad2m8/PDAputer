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
extern const lv_img_dsc_t img_wifi;
extern const lv_img_dsc_t img_icon_ai;
extern const lv_img_dsc_t img_icon_fmradio;
extern const lv_img_dsc_t img_icon_music;
extern const lv_img_dsc_t img_icon_setting;
extern const lv_img_dsc_t img_icon_webradio;
extern const lv_img_dsc_t img_icon_wifi;
extern const lv_img_dsc_t img_icon_games;
extern const lv_img_dsc_t img_icon_gps;
extern const lv_img_dsc_t img_icon_lorachat;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[15];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/