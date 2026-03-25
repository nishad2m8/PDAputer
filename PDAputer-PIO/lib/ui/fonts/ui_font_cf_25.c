/*******************************************************************************
 * Size: 25 px
 * Bpp: 1
 * Opts: --bpp 1 --size 25 --no-compress --font CuteFont-Regular.ttf --symbols ° --range 32-127 --format lvgl
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

#ifndef UI_FONT_CF_25
#define UI_FONT_CF_25 1
#endif

#if UI_FONT_CF_25

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xc,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x32, 0x1b, 0x3f, 0xe6, 0xc3, 0x61, 0xb0, 0xd8,
    0x6c, 0xff, 0x9b, 0xc, 0x80,

    /* U+0024 "$" */
    0x18, 0xc, 0x3f, 0xdb, 0xd, 0x86, 0xc3, 0x61,
    0xfe, 0x19, 0x8c, 0xc6, 0x63, 0x3f, 0xf0, 0xc0,
    0x60,

    /* U+0025 "%" */
    0xf8, 0x48, 0x8c, 0x88, 0x88, 0x98, 0xfb, 0x0,
    0x20, 0x7, 0xf0, 0xd3, 0x9, 0x11, 0x91, 0x11,
    0xf0,

    /* U+0026 "&" */
    0xfc, 0x30, 0xc, 0x3, 0x0, 0x70, 0x1e, 0xf6,
    0x33, 0xc, 0xc3, 0x30, 0xcf, 0xf0,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x7c, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x70,

    /* U+0029 ")" */
    0xc3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,

    /* U+002A "*" */
    0x18, 0x18, 0x18, 0x7e, 0x3c, 0x2c, 0x46,

    /* U+002B "+" */
    0xc, 0x3, 0x0, 0xc0, 0x30, 0xc, 0x3f, 0xf0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+002C "," */
    0xf5,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x0, 0x8, 0x30, 0x61, 0x83, 0x6, 0x18, 0x30,
    0xc1, 0x82, 0xc, 0x10, 0x0,

    /* U+0030 "0" */
    0xff, 0xc1, 0xc3, 0xc7, 0xcb, 0xd3, 0xe3, 0xe3,
    0xc3, 0x83, 0xff,

    /* U+0031 "1" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0xfe, 0x3, 0x3, 0x3, 0x3, 0xff, 0xc0, 0xc0,
    0xc0, 0xc0, 0xff,

    /* U+0033 "3" */
    0xff, 0x0, 0xc0, 0x60, 0x30, 0x1b, 0xfc, 0x6,
    0x3, 0x1, 0x80, 0xdf, 0xc0,

    /* U+0034 "4" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0x3, 0x3,
    0x3, 0x3, 0x3,

    /* U+0035 "5" */
    0x7f, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x3, 0x3,
    0x3, 0x3, 0xff,

    /* U+0036 "6" */
    0x7f, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xff,

    /* U+0037 "7" */
    0xff, 0x3, 0x3, 0x7, 0x6, 0xc, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0038 "8" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xff,

    /* U+0039 "9" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0x3, 0x3,
    0x3, 0x3, 0xfe,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0x50,

    /* U+003C "<" */
    0x0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0x30, 0x6,
    0x0, 0xe0, 0xe, 0x0, 0xe0, 0xc,

    /* U+003D "=" */
    0xff, 0x80, 0x0, 0x0, 0xf, 0xf8,

    /* U+003E ">" */
    0xc0, 0x1c, 0x1, 0xc0, 0x1c, 0x1, 0x80, 0x30,
    0x1c, 0x1c, 0x1c, 0x1c, 0xc, 0x0,

    /* U+003F "?" */
    0xfe, 0xc, 0x18, 0x30, 0x6f, 0xd8, 0x30, 0x0,
    0x1, 0x80,

    /* U+0040 "@" */
    0xff, 0xf6, 0x1, 0xb0, 0xd, 0x80, 0x6c, 0xf3,
    0x6c, 0xdb, 0x66, 0xdb, 0x36, 0xd9, 0xb6, 0xff,
    0xb0, 0x1, 0x80, 0x7, 0xff, 0x80,

    /* U+0041 "A" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0042 "B" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc6, 0xfe, 0xc6, 0xc3,
    0xc3, 0xc3, 0xff,

    /* U+0043 "C" */
    0xff, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc3, 0xc3, 0xff,

    /* U+0044 "D" */
    0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc7, 0xfe,

    /* U+0045 "E" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
    0xc0, 0xc0, 0xff,

    /* U+0046 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x7f, 0xc0, 0xc0, 0xc0, 0xc0, 0xdf, 0xc3, 0xc3,
    0xc3, 0xc3, 0xff,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xfc,

    /* U+004B "K" */
    0xc3, 0xc2, 0xc6, 0xc4, 0xcc, 0xf8, 0xd8, 0xcc,
    0xc6, 0xc6, 0xc3,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0x7f,

    /* U+004D "M" */
    0xe1, 0xfc, 0xbd, 0xef, 0x73, 0xcc, 0xf3, 0x3c,
    0xcf, 0x3, 0xc0, 0xf0, 0x3c, 0xc,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xd3, 0xd3, 0xd3, 0xcb, 0xcb,
    0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xff,

    /* U+0050 "P" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0xff, 0x61, 0xb0, 0xd8, 0x6c, 0x36, 0x1b, 0xd,
    0x86, 0xcb, 0x63, 0xbf, 0xc0, 0x0,

    /* U+0052 "R" */
    0xff, 0xc3, 0xc3, 0xc3, 0xc6, 0xfe, 0xc6, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0053 "S" */
    0x7f, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x3, 0x3,
    0x3, 0x3, 0xff,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xff,

    /* U+0056 "V" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x82, 0x63, 0x1b, 0x7, 0x0,

    /* U+0057 "W" */
    0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0x7f, 0x9c, 0xe3, 0x30,

    /* U+0058 "X" */
    0xc3, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x34,
    0x66, 0xc3, 0xc3,

    /* U+0059 "Y" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0x3, 0x3,
    0x3, 0x3, 0xff,

    /* U+005A "Z" */
    0xff, 0x1, 0x81, 0x80, 0xc0, 0xc0, 0xc0, 0x60,
    0x60, 0x30, 0x30, 0x1f, 0xe0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+005C "\\" */
    0x1, 0x83, 0x3, 0x6, 0x6, 0xc, 0x18, 0x18,
    0x30, 0x30, 0x60, 0xc0, 0x80,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+005E "^" */
    0x18, 0x59, 0x18, 0x0,

    /* U+005F "_" */
    0xff, 0xf8,

    /* U+0061 "a" */
    0xfc, 0x30, 0xff, 0xcf, 0x3c, 0xf3, 0xfc,

    /* U+0062 "b" */
    0xc3, 0xc, 0x3f, 0xcf, 0x3c, 0xf3, 0xcf, 0x3f,
    0xc0,

    /* U+0063 "c" */
    0xff, 0x3c, 0x30, 0xc3, 0xc, 0xff,

    /* U+0064 "d" */
    0xc, 0x30, 0xc3, 0xff, 0x3c, 0xf3, 0xcf, 0x3c,
    0xff,

    /* U+0065 "e" */
    0xff, 0x3c, 0xf3, 0xcf, 0xfc, 0x30, 0xfc,

    /* U+0066 "f" */
    0xfe, 0x31, 0x8c, 0x7f, 0x18, 0xc6, 0x31, 0x80,

    /* U+0067 "g" */
    0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xff, 0xc, 0x3f,
    0xc0,

    /* U+0068 "h" */
    0xc3, 0xc, 0x30, 0xff, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3,

    /* U+0069 "i" */
    0xc0, 0xff, 0xff,

    /* U+006A "j" */
    0x30, 0x0, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+006B "k" */
    0xc6, 0x31, 0x8c, 0xe7, 0x7a, 0xf6, 0xb7, 0x90,

    /* U+006C "l" */
    0xff, 0xff, 0xff,

    /* U+006D "m" */
    0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,

    /* U+006E "n" */
    0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+006F "o" */
    0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xff,

    /* U+0070 "p" */
    0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xff, 0xc3, 0xc,
    0x0,

    /* U+0071 "q" */
    0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xff, 0xc, 0x30,
    0xc0,

    /* U+0072 "r" */
    0xfe, 0x31, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0xff, 0xc, 0x3e, 0xc, 0x30, 0xfe,

    /* U+0074 "t" */
    0xc6, 0x31, 0x8f, 0xe3, 0x18, 0xc6, 0x31, 0xf0,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xff,

    /* U+0076 "v" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x27, 0x8c,

    /* U+0077 "w" */
    0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x37,
    0x78, 0xcc,

    /* U+0078 "x" */
    0x49, 0x27, 0x8c, 0x31, 0xe4, 0x93,

    /* U+0079 "y" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xff, 0xc, 0x3f,
    0xc0,

    /* U+007A "z" */
    0xfc, 0x63, 0xc, 0x61, 0x8c, 0x3f,

    /* U+007B "{" */
    0x3b, 0x18, 0xc6, 0x33, 0x18, 0x63, 0x18, 0xc6,
    0x30, 0xe0,

    /* U+007C "|" */
    0x3f, 0xff, 0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xe1, 0x8c, 0x63, 0x18, 0x63, 0x31, 0x8c, 0x63,
    0x1b, 0x80,

    /* U+007E "~" */
    0x7c, 0x36, 0x66, 0xc3, 0xc0,

    /* U+00B0 "°" */
    0x69, 0x96
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 88, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 79, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 136, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 7, .adv_w = 171, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 171, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 37, .adv_w = 236, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 194, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 70, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 69, .adv_w = 116, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 77, .adv_w = 116, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 85, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 92, .adv_w = 206, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 78, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 107, .adv_w = 173, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 108, .adv_w = 78, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 109, .adv_w = 129, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 122, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 171, .box_w = 4, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 171, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 78, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 78, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 234, .adv_w = 206, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 206, .box_w = 9, .box_h = 5, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 254, .adv_w = 206, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 231, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 300, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 75, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 101, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 198, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 163, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 171, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 481, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 171, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 198, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 171, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 163, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 116, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 595, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 608, .adv_w = 116, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 616, .adv_w = 151, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 620, .adv_w = 206, .box_w = 13, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 622, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 134, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 104, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 677, .adv_w = 134, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 73, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 73, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 696, .adv_w = 122, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 73, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 190, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 736, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 745, .adv_w = 100, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 750, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 100, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 776, .adv_w = 194, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 801, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 116, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 817, .adv_w = 77, .box_w = 2, .box_h = 19, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 822, .adv_w = 116, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 832, .adv_w = 220, .box_w = 12, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 837, .adv_w = 103, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8}
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
    },
    {
        .range_start = 176, .range_length = 1, .glyph_id_start = 95,
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
    .cmap_num = 3,
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
const lv_font_t ui_font_cf_25 = {
#else
lv_font_t ui_font_cf_25 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if UI_FONT_CF_25*/