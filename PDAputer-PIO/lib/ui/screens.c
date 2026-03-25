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
            lv_obj_set_size(obj, 76, 25);
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
                    lv_label_set_text(obj, "-:-");
                }
            }
        }
        {
            // main container right
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_container_right = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 164, 25);
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
                    // main image tone
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.main_image_tone = obj;
                    lv_obj_set_pos(obj, 145, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_tone_00);
                }
                {
                    // main image sdcard
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.main_image_sdcard = obj;
                    lv_obj_set_pos(obj, 145, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_sd_card_00);
                }
                {
                    // main image wifi
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.main_image_wifi = obj;
                    lv_obj_set_pos(obj, 145, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_wifi_04);
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
                    lv_label_set_text(obj, "-%");
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
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main image app calendar
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_calendar = obj;
            lv_obj_set_pos(obj, 0, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_calendar);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            // main image app notes
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_notes = obj;
            lv_obj_set_pos(obj, 0, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_note);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main image app remote
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.main_image_app_remote = obj;
            lv_obj_set_pos(obj, 0, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_remote);
            lv_image_set_scale(obj, 170);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main container date
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_container_date = obj;
            lv_obj_set_pos(obj, 5, 26);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2b6953), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // main label date
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.main_label_date = obj;
                    lv_obj_set_pos(obj, 42, -3382);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-");
                }
            }
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
    objects.main_image_tone = 0;
    objects.main_image_sdcard = 0;
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
    objects.main_image_app_calendar = 0;
    objects.main_image_app_notes = 0;
    objects.main_image_app_remote = 0;
    objects.main_container_date = 0;
    objects.main_label_date = 0;
}

void tick_screen_main() {
}

void create_screen_fm_radio() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.fm_radio = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff15171a), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // fmradio line 02
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.fmradio_line_02 = obj;
            lv_obj_set_pos(obj, 31, 73);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 180, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_line_dash_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_line_dash_gap(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fmradio line 01
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.fmradio_line_01 = obj;
            lv_obj_set_pos(obj, 100, 18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 40, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 172, 18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 8, 0 },
                { 15, 19 }
            };
            lv_line_set_points(obj, line_points, 3);
            lv_obj_set_style_line_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 48, 18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 15, 0 },
                { 7, 0 },
                { 0, 18 }
            };
            lv_line_set_points(obj, line_points, 3);
            lv_obj_set_style_line_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fmradio label min
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fmradio_label_min = obj;
            lv_obj_set_pos(obj, 4, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffd5ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff14171a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
        {
            // fmradio label max
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fmradio_label_max = obj;
            lv_obj_set_pos(obj, -4, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffd5ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff14171a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
        {
            // fmradio container stations
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fmradio_container_stations = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(22));
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_ON);
            lv_obj_set_scroll_dir(obj, LV_DIR_HOR);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_START);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_START);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // fmradio label pre1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fmradio_label_pre1 = obj;
                    lv_obj_set_pos(obj, 144, 70);
                    lv_obj_set_size(obj, 75, 22);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_label_set_text(obj, "-");
                }
                {
                    // fmradio label pre2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fmradio_label_pre2 = obj;
                    lv_obj_set_pos(obj, 144, 70);
                    lv_obj_set_size(obj, 75, 22);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_label_set_text(obj, "-");
                }
                {
                    // fmradio label pre3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fmradio_label_pre3 = obj;
                    lv_obj_set_pos(obj, 144, 70);
                    lv_obj_set_size(obj, 75, 22);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_label_set_text(obj, "-");
                }
            }
        }
        {
            // fmradio scale
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fmradio_scale = obj;
            lv_obj_set_pos(obj, 0, -30);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(20));
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fmradio label main
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fmradio_label_main = obj;
            lv_obj_set_pos(obj, 0, -18);
            lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_45, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffd5ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, -1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "108.2");
        }
        {
            // fmradio label sub
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fmradio_label_sub = obj;
            lv_obj_set_pos(obj, 0, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff7e9700), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff14171a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "MHz");
        }
        {
            // fmradio container signal
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fmradio_container_signal = obj;
            lv_obj_set_pos(obj, 7, 4);
            lv_obj_set_size(obj, 20, 57);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fmradio label mode
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fmradio_label_mode = obj;
            lv_obj_set_pos(obj, 42, -16);
            lv_obj_set_size(obj, 20, 20);
            lv_obj_set_style_text_font(obj, &ui_font_cf_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "FM");
        }
        {
            // fmradio label most
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fmradio_label_most = obj;
            lv_obj_set_pos(obj, -44, -16);
            lv_obj_set_size(obj, 20, 19);
            lv_obj_set_style_text_font(obj, &ui_font_cf_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "MO");
        }
        {
            // fmradio bar signal
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.fmradio_bar_signal = obj;
            lv_obj_set_pos(obj, 5, 5);
            lv_obj_set_size(obj, 20, 58);
            lv_bar_set_range(obj, 0, 15);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, &img_signal_main, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, &img_signal_indicator, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // fmradio bar battery
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.fmradio_bar_battery = obj;
            lv_obj_set_pos(obj, -5, 5);
            lv_obj_set_size(obj, 20, 57);
            lv_bar_set_value(obj, 50, LV_ANIM_OFF);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, &img_volume_main, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, &img_volume_indicator, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // fmradio image signal
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.fmradio_image_signal = obj;
            lv_obj_set_pos(obj, 16, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_signal);
            lv_obj_set_style_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff22ff39), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            // fmradio image headphone
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.fmradio_image_headphone = obj;
            lv_obj_set_pos(obj, 142, 4);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_headphone);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff10e9e9), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fmradio image battery
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.fmradio_image_battery = obj;
            lv_obj_set_pos(obj, 212, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_battery);
            lv_obj_set_style_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xffff41d9), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff808080), LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            // fmradio image playpause
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.fmradio_image_playpause = obj;
            lv_obj_set_pos(obj, 67, 4);
            lv_obj_set_size(obj, 30, 30);
            lv_obj_set_style_bg_image_src(obj, &img_icon_play, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, &img_icon_pause, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_bg_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        }
    }
    
    tick_screen_fm_radio();
}

void delete_screen_fm_radio() {
    lv_obj_delete(objects.fm_radio);
    objects.fm_radio = 0;
    objects.fmradio_line_02 = 0;
    objects.fmradio_line_01 = 0;
    objects.obj0 = 0;
    objects.obj1 = 0;
    objects.fmradio_label_min = 0;
    objects.fmradio_label_max = 0;
    objects.fmradio_container_stations = 0;
    objects.fmradio_label_pre1 = 0;
    objects.fmradio_label_pre2 = 0;
    objects.fmradio_label_pre3 = 0;
    objects.fmradio_scale = 0;
    objects.fmradio_label_main = 0;
    objects.fmradio_label_sub = 0;
    objects.fmradio_container_signal = 0;
    objects.fmradio_label_mode = 0;
    objects.fmradio_label_most = 0;
    objects.fmradio_bar_signal = 0;
    objects.fmradio_bar_battery = 0;
    objects.fmradio_image_signal = 0;
    objects.fmradio_image_headphone = 0;
    objects.fmradio_image_battery = 0;
    objects.fmradio_image_playpause = 0;
}

void tick_screen_fm_radio() {
}

void create_screen_music() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.music = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff191919), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // music label name
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.music_label_name = obj;
            lv_obj_set_pos(obj, 11, 5);
            lv_obj_set_size(obj, 192, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "music name");
        }
        {
            // music label album artist
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.music_label_album_artist = obj;
            lv_obj_set_pos(obj, 11, 29);
            lv_obj_set_size(obj, 169, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff3f3f), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Album");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 166, -7);
            lv_obj_set_size(obj, 150, 150);
            lv_obj_set_style_radius(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // music bar time
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.music_bar_time = obj;
            lv_obj_set_pos(obj, 11, 56);
            lv_obj_set_size(obj, 138, 7);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff292b30), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5197f9), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // music vinyl disk
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.music_vinyl_disk = obj;
            lv_obj_set_pos(obj, 180, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_vinyl_disk);
        }
        {
            // music label time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.music_label_time = obj;
            lv_obj_set_pos(obj, 11, 63);
            lv_obj_set_size(obj, 71, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff5197f9), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "5:05");
        }
        {
            // music panel controlls
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.music_panel_controlls = obj;
            lv_obj_set_pos(obj, 5, 86);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_radius(obj, 256, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff3f4147), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // music image previous
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.music_image_previous = obj;
                    lv_obj_set_pos(obj, 19, 89);
                    lv_obj_set_size(obj, 30, 30);
                    lv_image_set_src(obj, &img_music_previous);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff13ff00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                    lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                }
                {
                    // music image play pause
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.music_image_play_pause = obj;
                    lv_obj_set_pos(obj, 66, 89);
                    lv_obj_set_size(obj, 30, 30);
                    lv_image_set_src(obj, &img_music_play);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xffff5b00), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff13ff00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                    lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                }
                {
                    // music image next
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.music_image_next = obj;
                    lv_obj_set_pos(obj, 113, 89);
                    lv_obj_set_size(obj, 30, 30);
                    lv_image_set_src(obj, &img_music_next);
                    lv_obj_set_style_bg_image_src(obj, &img_music_play, LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff13ff00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                    lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                }
                {
                    // music image shuffle
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.music_image_shuffle = obj;
                    lv_obj_set_pos(obj, 113, 89);
                    lv_obj_set_size(obj, 30, 30);
                    lv_image_set_src(obj, &img_music_shuffle);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff13ff00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                    lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
                    lv_obj_set_style_image_recolor(obj, lv_color_hex(0xffff5b00), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                }
            }
        }
        {
            // music arc volume
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.music_arc_volume = obj;
            lv_obj_set_pos(obj, 164, -7);
            lv_obj_set_size(obj, 150, 150);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 125);
            lv_arc_set_bg_end_angle(obj, 235);
            lv_obj_set_style_arc_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffcfcd31), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // music label track nos
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.music_label_track_nos = obj;
            lv_obj_set_pos(obj, 82, 63);
            lv_obj_set_size(obj, 67, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff13ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "1/2");
        }
    }
    
    tick_screen_music();
}

void delete_screen_music() {
    lv_obj_delete(objects.music);
    objects.music = 0;
    objects.music_label_name = 0;
    objects.music_label_album_artist = 0;
    objects.music_bar_time = 0;
    objects.music_vinyl_disk = 0;
    objects.music_label_time = 0;
    objects.music_panel_controlls = 0;
    objects.music_image_previous = 0;
    objects.music_image_play_pause = 0;
    objects.music_image_next = 0;
    objects.music_image_shuffle = 0;
    objects.music_arc_volume = 0;
    objects.music_label_track_nos = 0;
}

void tick_screen_music() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_ON);
    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // settings container devicename
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_devicename = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_add_state(obj, LV_STATE_FOCUS_KEY);
            add_style_container_settings(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // settings label device 
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.settings_label_device_ = obj;
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Device Name:");
                }
                {
                    // settings textarea devicename
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.settings_textarea_devicename = obj;
                    lv_obj_set_pos(obj, 0, 148);
                    lv_obj_set_size(obj, 107, LV_SIZE_CONTENT);
                    lv_textarea_set_max_length(obj, 8);
                    lv_textarea_set_placeholder_text(obj, "aA022228");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff411d00), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                }
            }
        }
        {
            // settings container brightness
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_brightness = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_container_settings(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Brightness:");
                }
                {
                    // settings slider brightness
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.settings_slider_brightness = obj;
                    lv_obj_set_pos(obj, 66, 69);
                    lv_obj_set_size(obj, 70, 5);
                    lv_slider_set_value(obj, 25, LV_ANIM_OFF);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3f020), LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff14171a), LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3f021), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3f021), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
                {
                    // settings label brightness
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.settings_label_brightness = obj;
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "100%");
                }
            }
        }
        {
            // settings container tone
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_tone = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_container_settings(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Tone:");
                }
                {
                    // settings slider tone
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.settings_slider_tone = obj;
                    lv_obj_set_pos(obj, 66, 69);
                    lv_obj_set_size(obj, 75, 5);
                    lv_slider_set_value(obj, 25, LV_ANIM_OFF);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3f020), LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff14171a), LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_border_width(obj, 3, LV_PART_KNOB | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3f021), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3f021), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
                {
                    // settings label tone
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.settings_label_tone = obj;
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "25%");
                }
            }
        }
        {
            // settings container tformat
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_tformat = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_container_settings(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Time Format:");
                }
                {
                    // settings roller tformat
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    objects.settings_roller_tformat = obj;
                    lv_obj_set_pos(obj, 2644, -4125);
                    lv_obj_set_size(obj, 33, 20);
                    lv_roller_set_options(obj, "12\n24", LV_ROLLER_MODE_INFINITE);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff411d00), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // settings container tzone
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_tzone = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_add_state(obj, LV_STATE_FOCUS_KEY);
            add_style_container_settings(obj);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff5a5a5a), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Time Zone:");
                }
                {
                    // settings label tzone
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.settings_label_tzone = obj;
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "XX");
                }
            }
        }
        {
            // settings container ssid
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_ssid = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_container_settings(obj);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff5a5a5a), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "WifI:");
                }
                {
                    // settings label ssid
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.settings_label_ssid = obj;
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "SSID");
                }
            }
        }
        {
            // settings container support
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.settings_container_support = obj;
            lv_obj_set_pos(obj, 12, 16);
            lv_obj_set_size(obj, 218, 25);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_container_settings(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff440505), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xffee1b24), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_heart);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 80, 37);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Support");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void delete_screen_settings() {
    lv_obj_delete(objects.settings);
    objects.settings = 0;
    objects.settings_container_devicename = 0;
    objects.settings_label_device_ = 0;
    objects.settings_textarea_devicename = 0;
    objects.settings_container_brightness = 0;
    objects.settings_slider_brightness = 0;
    objects.settings_label_brightness = 0;
    objects.settings_container_tone = 0;
    objects.settings_slider_tone = 0;
    objects.settings_label_tone = 0;
    objects.settings_container_tformat = 0;
    objects.settings_roller_tformat = 0;
    objects.settings_container_tzone = 0;
    objects.settings_label_tzone = 0;
    objects.settings_container_ssid = 0;
    objects.settings_label_ssid = 0;
    objects.settings_container_support = 0;
}

void tick_screen_settings() {
}

void create_screen_support() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.support = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_qrcode_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 111, 8);
            lv_obj_set_size(obj, 120, 120);
            lv_qrcode_set_size(obj, 120);
            lv_qrcode_set_dark_color(obj, lv_color_hex(0xff000000));
            lv_qrcode_set_light_color(obj, lv_color_hex(0xffffffff));
            lv_qrcode_update(obj, "https://buymeacoffee.com/nishad2m8", 34);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // about label details
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.about_label_details = obj;
            lv_obj_set_pos(obj, 8, 47);
            lv_obj_set_size(obj, 93, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Buy me a coffee to support this project");
        }
        {
            // about label details_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.about_label_details_1 = obj;
            lv_obj_set_pos(obj, 8, 108);
            lv_obj_set_size(obj, 93, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff8e0b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "nishad2m8");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 35, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_bc);
        }
    }
    
    tick_screen_support();
}

void delete_screen_support() {
    lv_obj_delete(objects.support);
    objects.support = 0;
    objects.obj2 = 0;
    objects.about_label_details = 0;
    objects.about_label_details_1 = 0;
}

void tick_screen_support() {
}

void create_screen_widgets() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.widgets = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff141002), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main label moonphase
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_label_moonphase = obj;
            lv_obj_set_pos(obj, 120, 29);
            lv_obj_set_size(obj, 83, 23);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "waxing-gibbous");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 88, 36);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_mask);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff141002), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main container weather
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_container_weather = obj;
            lv_obj_set_pos(obj, 5, 25);
            lv_obj_set_size(obj, 90, 30);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2b6953), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 1, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff17afbe), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_outline_pad(obj, -1, LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // main canvas weather icon
                    lv_obj_t *obj = lv_canvas_create(parent_obj);
                    objects.main_canvas_weather_icon = obj;
                    lv_obj_set_pos(obj, 6, 27);
                    lv_obj_set_size(obj, 30, 30);
                    lv_obj_set_style_bg_image_src(obj, &img_sunny, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 36);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_column(obj, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // main label temp
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.main_label_temp = obj;
                            lv_obj_set_pos(obj, 42, 22);
                            lv_obj_set_size(obj, 43, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_cf_45, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "25");
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 50, 0);
                            lv_obj_set_size(obj, 14, 28);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // main label time_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.main_label_time_2 = obj;
                                    lv_obj_set_pos(obj, 85, 27);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 12);
                                    lv_obj_set_style_text_font(obj, &ui_font_cf_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "°");
                                }
                                {
                                    // main label time_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.main_label_time_3 = obj;
                                    lv_obj_set_pos(obj, 84, 34);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &ui_font_cf_25, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "C");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // main canvas moon icon
            lv_obj_t *obj = lv_canvas_create(parent_obj);
            objects.main_canvas_moon_icon = obj;
            lv_obj_set_pos(obj, 205, 25);
            lv_obj_set_size(obj, 30, 30);
            lv_obj_set_style_bg_image_src(obj, &img_waxing_gibbous, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_widgets();
}

void delete_screen_widgets() {
    lv_obj_delete(objects.widgets);
    objects.widgets = 0;
    objects.main_label_moonphase = 0;
    objects.obj3 = 0;
    objects.main_container_weather = 0;
    objects.main_canvas_weather_icon = 0;
    objects.main_label_temp = 0;
    objects.main_label_time_2 = 0;
    objects.main_label_time_3 = 0;
    objects.main_canvas_moon_icon = 0;
}

void tick_screen_widgets() {
}

void create_screen_calendar() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.calendar = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // calendar calendar
            lv_obj_t *obj = lv_calendar_create(parent_obj);
            objects.calendar_calendar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
            lv_calendar_add_header_arrow(obj);
            lv_calendar_set_today_date(obj, 2022, 11, 1);
            lv_calendar_set_month_shown(obj, 2022, 11);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_cf_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, -20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, -5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, -3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_calendar();
}

void delete_screen_calendar() {
    lv_obj_delete(objects.calendar);
    objects.calendar = 0;
    objects.calendar_calendar = 0;
}

void tick_screen_calendar() {
}

void create_screen_notes() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.notes = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 135);
    
    tick_screen_notes();
}

void delete_screen_notes() {
    lv_obj_delete(objects.notes);
    objects.notes = 0;
}

void tick_screen_notes() {
}

typedef void (*create_screen_func_t)();
create_screen_func_t create_screen_funcs[] = {
    create_screen_boot,
    create_screen_main,
    create_screen_fm_radio,
    create_screen_music,
    create_screen_settings,
    create_screen_support,
    create_screen_widgets,
    create_screen_calendar,
    create_screen_notes,
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
    delete_screen_fm_radio,
    delete_screen_music,
    delete_screen_settings,
    delete_screen_support,
    delete_screen_widgets,
    delete_screen_calendar,
    delete_screen_notes,
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
    tick_screen_fm_radio,
    tick_screen_music,
    tick_screen_settings,
    tick_screen_support,
    tick_screen_widgets,
    tick_screen_calendar,
    tick_screen_notes,
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