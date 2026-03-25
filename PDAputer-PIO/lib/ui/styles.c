#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: container_settings
//

void init_style_container_settings_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_pad(style, 1);
    lv_style_set_outline_color(style, lv_color_hex(0xffff9a24));
    lv_style_set_outline_opa(style, 255);
    lv_style_set_margin_left(style, -10);
    lv_style_set_pad_left(style, 5);
    lv_style_set_opa(style, 255);
};

lv_style_t *get_style_container_settings_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_container_settings_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_container_settings_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_layout(style, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(style, LV_FLEX_FLOW_ROW);
    lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_START);
    lv_style_set_flex_cross_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_flex_track_place(style, LV_FLEX_ALIGN_CENTER);
    lv_style_set_margin_left(style, 10);
    lv_style_set_opa(style, 150);
    lv_style_set_pad_left(style, 5);
};

lv_style_t *get_style_container_settings_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_container_settings_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_container_settings_MAIN_FOCUS_KEY(lv_style_t *style) {
    lv_style_set_margin_left(style, -10);
    lv_style_set_outline_width(style, 1);
    lv_style_set_outline_color(style, lv_color_hex(0xffffffff));
    lv_style_set_outline_opa(style, 255);
    lv_style_set_outline_pad(style, 1);
    lv_style_set_pad_left(style, 5);
    lv_style_set_opa(style, 255);
};

lv_style_t *get_style_container_settings_MAIN_FOCUS_KEY() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_container_settings_MAIN_FOCUS_KEY(style);
    }
    return style;
};

void add_style_container_settings(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_container_settings_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_container_settings_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_container_settings_MAIN_FOCUS_KEY(), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
};

void remove_style_container_settings(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_container_settings_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_container_settings_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_container_settings_MAIN_FOCUS_KEY(), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_container_settings,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_container_settings,
    };
    remove_style_funcs[styleIndex](obj);
}