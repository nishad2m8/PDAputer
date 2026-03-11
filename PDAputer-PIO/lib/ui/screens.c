#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_boot() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.boot = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff140e02), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 35, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_element_01);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 195, 23);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_element_02);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, -9, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_element_03);
        }
        {
            // boot label name
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.boot_label_name = obj;
            lv_obj_set_pos(obj, 49, 41);
            lv_obj_set_size(obj, 142, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_45, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff8e0b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "PDAputer");
        }
        {
            // boot label contributtion
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.boot_label_contributtion = obj;
            lv_obj_set_pos(obj, 49, 109);
            lv_obj_set_size(obj, 142, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "nishad2m8");
        }
    }
    
    tick_screen_boot();
}

void delete_screen_boot() {
    lv_obj_delete(objects.boot);
    objects.boot = 0;
    objects.boot_label_name = 0;
    objects.boot_label_contributtion = 0;
}

void tick_screen_boot() {
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff141002), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main image bg
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_bg = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_bg);
        }
        {
            // main panel menu selected
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_panel_menu_selected = obj;
            lv_obj_set_pos(obj, 45, 106);
            lv_obj_set_size(obj, 150, 150);
            lv_obj_set_style_radius(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff001758), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main container left
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_container_left = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(50), 25);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // main label time
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.main_label_time = obj;
                    lv_obj_set_pos(obj, 4, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "09:42");
                }
            }
        }
        {
            // main container right
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_container_right = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(50), 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // main image wifi
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.main_image_wifi = obj;
                    lv_obj_set_pos(obj, 145, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_wifi);
                }
                {
                    // main image battery
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.main_image_battery = obj;
                    lv_obj_set_pos(obj, 167, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_battery);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // main bar battery
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.main_bar_battery = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 6, 9);
                            lv_bar_set_value(obj, 100, LV_ANIM_OFF);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 1, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // main label battery
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.main_label_battery = obj;
                    lv_obj_set_pos(obj, 181, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "100%");
                }
            }
        }
        {
            // main label menu selected
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_label_menu_selected = obj;
            lv_obj_set_pos(obj, 48, 108);
            lv_obj_set_size(obj, 145, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff98b0ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "FM Radio");
        }
        {
            // main image app fmradio
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_fmradio = obj;
            lv_obj_set_pos(obj, 95, 53);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_fmradio);
        }
        {
            // main image app webradio
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_webradio = obj;
            lv_obj_set_pos(obj, 149, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_webradio);
            lv_image_set_scale(obj, 200);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app music
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_music = obj;
            lv_obj_set_pos(obj, 190, 90);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_music);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app ai
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_ai = obj;
            lv_obj_set_pos(obj, 35, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_ai);
            lv_image_set_scale(obj, 200);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app setting
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_setting = obj;
            lv_obj_set_pos(obj, -2, 90);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_setting);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app games
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_games = obj;
            lv_obj_set_pos(obj, 0, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_games);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app lorachat
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_lorachat = obj;
            lv_obj_set_pos(obj, 0, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_lorachat);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app gps
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_gps = obj;
            lv_obj_set_pos(obj, 0, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_gps);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
    }
    
    tick_screen_main();
}

void delete_screen_main() {
    lv_obj_delete(objects.main);
    objects.main = 0;
    objects.main_image_bg = 0;
    objects.main_panel_menu_selected = 0;
    objects.main_container_left = 0;
    objects.main_label_time = 0;
    objects.main_container_right = 0;
    objects.main_image_wifi = 0;
    objects.main_image_battery = 0;
    objects.main_bar_battery = 0;
    objects.main_label_battery = 0;
    objects.main_label_menu_selected = 0;
    objects.main_image_app_fmradio = 0;
    objects.main_image_app_webradio = 0;
    objects.main_image_app_music = 0;
    objects.main_image_app_ai = 0;
    objects.main_image_app_setting = 0;
    objects.main_image_app_games = 0;
    objects.main_image_app_lorachat = 0;
    objects.main_image_app_gps = 0;
}

void tick_screen_main() {
}

typedef void (*create_screen_func_t)();
create_screen_func_t create_screen_funcs[] = {
    create_screen_boot,
    create_screen_main,
};
void create_screen(int screen_index) {
    create_screen_funcs[screen_index]();
}
void create_screen_by_id(enum ScreensEnum screenId) {
    create_screen_funcs[screenId - 1]();
}

typedef void (*delete_screen_func_t)();
delete_screen_func_t delete_screen_funcs[] = {
    delete_screen_boot,
    delete_screen_main,
};
void delete_screen(int screen_index) {
    delete_screen_funcs[screen_index]();
}
void delete_screen_by_id(enum ScreensEnum screenId) {
    delete_screen_funcs[screenId - 1]();
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_boot,
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "CF-45", &ui_font_cf_45 },
    { "CF-20", &ui_font_cf_20 },
    { "CF-25", &ui_font_cf_25 },
    { "CF-30", &ui_font_cf_30 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_boot();
    create_screen_main();
}