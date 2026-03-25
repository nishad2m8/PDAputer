/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --no-compress --font ../../../Downloads/Cute_Font/CuteFont-Regular.ttf --range 32-127 --format lvgl
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl.h"
#endif

#ifndef UI_FONT_CF_20
#define UI_FONT_CF_20 1
#endif

#if UI_FONT_CF_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd,

    /* U+0022 "\"" */
    0x99, 0x90,

    /* U+0023 "#" */
    0x49, 0xfc, 0x92, 0x49, 0x2f, 0xd2,

    /* U+0024 "$" */
    0x10, 0x63, 0xfc, 0x89, 0x1f, 0xc4, 0x89, 0x13,
    0xfc, 0x40, 0x0,

    /* U+0025 "%" */
    0xf1, 0x24, 0xcf, 0x60, 0x10, 0xb, 0xc7, 0x93,
    0x64, 0x8f,

    /* U+0026 "&" */
    0xf0, 0x80, 0x80, 0x60, 0x46, 0x84, 0x84, 0xfc,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x72, 0x49, 0x24, 0x91, 0x80,

    /* U+0029 ")" */
    0xc4, 0x92, 0x49, 0x27, 0x0,

    /* U+002A "*" */
    0x25, 0x1e, 0xa5, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x8,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x18, 0x84, 0x62, 0x31, 0x18, 0x84, 0x0,

    /* U+0030 "0" */
    0xfe, 0x18, 0xe5, 0xa7, 0x18, 0x7f,

    /* U+0031 "1" */
    0xe4, 0x92, 0x49,

    /* U+0032 "2" */
    0xfc, 0x10, 0x7f, 0x82, 0x8, 0x3f,

    /* U+0033 "3" */
    0xfc, 0x10, 0x7f, 0x4, 0x10, 0x7f,

    /* U+0034 "4" */
    0x86, 0x18, 0x7f, 0x4, 0x10, 0x41,

    /* U+0035 "5" */
    0xfe, 0x8, 0x3f, 0x4, 0x10, 0x7f,

    /* U+0036 "6" */
    0xfe, 0x8, 0x3f, 0x86, 0x18, 0x7f,

    /* U+0037 "7" */
    0xfc, 0x10, 0x42, 0x10, 0x82, 0x8,

    /* U+0038 "8" */
    0xfe, 0x18, 0x7f, 0x86, 0x18, 0x7f,

    /* U+0039 "9" */
    0xfe, 0x18, 0x7f, 0x4, 0x10, 0x7f,

    /* U+003A ":" */
    0x84,

    /* U+003B ";" */
    0x86,

    /* U+003C "<" */
    0x3, 0xc, 0x30, 0xc0, 0xc0, 0x30, 0xc, 0x3,

    /* U+003D "=" */
    0xff, 0x0, 0x0, 0xff,

    /* U+003E ">" */
    0xc0, 0x30, 0xc, 0x3, 0x3, 0xc, 0x30, 0xc0,

    /* U+003F "?" */
    0xf8, 0x42, 0xf4, 0x0, 0x8,

    /* U+0040 "@" */
    0xff, 0xe0, 0x18, 0x6, 0x79, 0x92, 0x64, 0x99,
    0x26, 0x7f, 0x80, 0x3f, 0xf0,

    /* U+0041 "A" */
    0xfe, 0x18, 0x7f, 0x86, 0x18, 0x61,

    /* U+0042 "B" */
    0xfe, 0x18, 0xfe, 0x8e, 0x18, 0x7f,

    /* U+0043 "C" */
    0xfe, 0x18, 0x20, 0x82, 0x8, 0x7f,

    /* U+0044 "D" */
    0xfa, 0x38, 0x61, 0x86, 0x18, 0xfe,

    /* U+0045 "E" */
    0xfe, 0x8, 0x3f, 0x82, 0x8, 0x3f,

    /* U+0046 "F" */
    0xfe, 0x8, 0x3f, 0x82, 0x8, 0x20,

    /* U+0047 "G" */
    0xfe, 0x8, 0x2f, 0x86, 0x18, 0x7f,

    /* U+0048 "H" */
    0x86, 0x18, 0x7f, 0x86, 0x18, 0x61,

    /* U+0049 "I" */
    0xff,

    /* U+004A "J" */
    0x24, 0x92, 0x4f,

    /* U+004B "K" */
    0x8a, 0x69, 0x3c, 0xb2, 0x48, 0xa2,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x3f,

    /* U+004D "M" */
    0xc7, 0x56, 0xec, 0x99, 0x30, 0x60, 0xc1,

    /* U+004E "N" */
    0xc7, 0x9a, 0x6d, 0xb6, 0x79, 0xe3,

    /* U+004F "O" */
    0xfe, 0x18, 0x61, 0x86, 0x18, 0x7f,

    /* U+0050 "P" */
    0xfe, 0x18, 0x7f, 0x82, 0x8, 0x20,

    /* U+0051 "Q" */
    0xfe, 0x18, 0x61, 0x86, 0x58, 0xff, 0x0,

    /* U+0052 "R" */
    0xfe, 0x18, 0x7e, 0x8a, 0x18, 0x61,

    /* U+0053 "S" */
    0xfe, 0x8, 0x3f, 0x4, 0x10, 0x7f,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x7f,

    /* U+0056 "V" */
    0x83, 0x6, 0xc, 0x18, 0x38, 0xdb, 0x1c,

    /* U+0057 "W" */
    0x88, 0xc4, 0x62, 0x31, 0x18, 0x8c, 0x45, 0x74,
    0x6c,

    /* U+0058 "X" */
    0x8e, 0xdc, 0x42, 0x2a, 0x31,

    /* U+0059 "Y" */
    0x86, 0x18, 0x7f, 0x4, 0x10, 0x7f,

    /* U+005A "Z" */
    0xfe, 0x8, 0x30, 0xc1, 0x4, 0x18, 0x7f,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x93, 0x80,

    /* U+005C "\\" */
    0x84, 0x30, 0x86, 0x10, 0xc2, 0x10, 0xc0,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x27, 0x80,

    /* U+005E "^" */
    0x32, 0xe2,

    /* U+005F "_" */
    0xff, 0xc0,

    /* U+0061 "a" */
    0x78, 0x7f, 0x18, 0xc7, 0xe0,

    /* U+0062 "b" */
    0x84, 0x3f, 0x18, 0xc6, 0x3f,

    /* U+0063 "c" */
    0xf9, 0x88, 0x9f,

    /* U+0064 "d" */
    0x8, 0x43, 0xf8, 0xc6, 0x31, 0xf8,

    /* U+0065 "e" */
    0xfc, 0x63, 0x1f, 0xc3, 0xc0,

    /* U+0066 "f" */
    0xf2, 0x4f, 0x24, 0x80,

    /* U+0067 "g" */
    0xfc, 0x63, 0x18, 0xfc, 0x2f,

    /* U+0068 "h" */
    0x84, 0x21, 0xf8, 0xc6, 0x31, 0x88,

    /* U+0069 "i" */
    0x9f, 0x80,

    /* U+006A "j" */
    0x41, 0x55, 0x5c,

    /* U+006B "k" */
    0x88, 0x89, 0xba, 0xea, 0xb0,

    /* U+006C "l" */
    0xff, 0x80,

    /* U+006D "m" */
    0xff, 0x26, 0x4c, 0x99, 0x32, 0x40,

    /* U+006E "n" */
    0xfc, 0x63, 0x18, 0xc4,

    /* U+006F "o" */
    0xfc, 0x63, 0x18, 0xfc,

    /* U+0070 "p" */
    0xfc, 0x63, 0x18, 0xfe, 0x10,

    /* U+0071 "q" */
    0xfc, 0x63, 0x18, 0xfc, 0x21,

    /* U+0072 "r" */
    0xe8, 0x88, 0x88,

    /* U+0073 "s" */
    0xf4, 0x3e, 0x10, 0xfc,

    /* U+0074 "t" */
    0x92, 0x79, 0x24, 0xe0,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xfc,

    /* U+0076 "v" */
    0x8c, 0x63, 0x15, 0x10,

    /* U+0077 "w" */
    0x93, 0x26, 0x4c, 0x99, 0x2d, 0x80,

    /* U+0078 "x" */
    0x9a, 0x66, 0xa9,

    /* U+0079 "y" */
    0x8c, 0x63, 0x18, 0xfc, 0x2f,

    /* U+007A "z" */
    0xf9, 0x88, 0xc4, 0x7c,

    /* U+007B "{" */
    0x34, 0x44, 0x48, 0x44, 0x44, 0x30,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xc2, 0x22, 0x21, 0x22, 0x22, 0xc0,

    /* U+007E "~" */
    0x78, 0xe4, 0xe3, 0xc0
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 70, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 63, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 109, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 4, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 21, .adv_w = 189, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 56, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 40, .adv_w = 92, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 45, .adv_w = 92, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 123, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 54, .adv_w = 165, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 62, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 139, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 63, .adv_w = 62, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 103, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 71, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 137, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 62, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 62, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 130, .adv_w = 165, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 165, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 142, .adv_w = 165, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 119, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 185, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 168, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 60, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 81, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 159, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 131, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 137, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 264, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 137, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 159, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 137, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 92, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 328, .adv_w = 103, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 335, .adv_w = 92, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 340, .adv_w = 121, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 342, .adv_w = 165, .box_w = 10, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 344, .adv_w = 107, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 107, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 107, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 83, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 377, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 59, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 59, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 388, .adv_w = 98, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 59, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 152, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 414, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 419, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 156, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 452, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 92, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 462, .adv_w = 62, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 464, .adv_w = 92, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 470, .adv_w = 176, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 64, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 30, .glyph_id_start = 65,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_cf_20 = {
#else
lv_font_t ui_font_cf_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if UI_FONT_CF_20*/