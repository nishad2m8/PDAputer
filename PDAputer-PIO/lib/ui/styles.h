#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: container_settings
lv_style_t *get_style_container_settings_MAIN_CHECKED();
lv_style_t *get_style_container_settings_MAIN_DEFAULT();
lv_style_t *get_style_container_settings_MAIN_FOCUS_KEY();
void add_style_container_settings(lv_obj_t *obj);
void remove_style_container_settings(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/