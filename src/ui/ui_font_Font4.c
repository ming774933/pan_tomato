/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --font /Users/huangguanming/SquareLine/assets/TaipeiSansTCBeta-Light.ttf -o /Users/huangguanming/SquareLine/assets/ui_font_Font4.c --format lvgl -r 0x20-0x7f --symbols 退出年月日保存 --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_FONT4
#define UI_FONT_FONT4 1
#endif

#if UI_FONT_FONT4

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x28, 0xa7, 0xd2, 0x4b, 0xf5, 0x14, 0x50,

    /* U+0024 "$" */
    0x23, 0x25, 0x8, 0x30, 0x41, 0xc, 0x4c, 0x40,

    /* U+0025 "%" */
    0x61, 0x24, 0x89, 0x42, 0x56, 0x6a, 0x42, 0x91,
    0x24, 0x89, 0x21, 0x80,

    /* U+0026 "&" */
    0x38, 0x48, 0x48, 0x50, 0x60, 0x92, 0x8c, 0x84,
    0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x4a, 0x49, 0x24, 0x91, 0x20,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x29, 0x20,

    /* U+002A "*" */
    0x5d, 0x10,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x10,

    /* U+002C "," */
    0xd8,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x10, 0x84, 0x22, 0x10, 0x88, 0x42, 0x21, 0x8,
    0x0,

    /* U+0030 "0" */
    0x76, 0xe3, 0x18, 0xc6, 0x3b, 0x70,

    /* U+0031 "1" */
    0x61, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+0032 "2" */
    0x74, 0x42, 0x11, 0x8, 0x88, 0xf8,

    /* U+0033 "3" */
    0x74, 0x42, 0xe1, 0x84, 0x33, 0x70,

    /* U+0034 "4" */
    0x8, 0x62, 0x8a, 0x4a, 0x2f, 0xc2, 0x8,

    /* U+0035 "5" */
    0x79, 0x4, 0x1e, 0xc, 0x10, 0x63, 0x78,

    /* U+0036 "6" */
    0x72, 0x21, 0x6c, 0xc6, 0x29, 0x70,

    /* U+0037 "7" */
    0xfc, 0x21, 0x4, 0x10, 0x82, 0x8, 0x20,

    /* U+0038 "8" */
    0x74, 0x63, 0x15, 0x56, 0x31, 0x70,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x22, 0x70,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x40, 0xd, 0x80,

    /* U+003C "<" */
    0x19, 0x88, 0x1c, 0xc,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0xc0, 0xc0, 0xcc, 0xc0,

    /* U+003F "?" */
    0x70, 0x42, 0x21, 0x10, 0x80, 0x20,

    /* U+0040 "@" */
    0x1f, 0xc, 0x64, 0xd, 0x79, 0x92, 0x69, 0x1a,
    0x46, 0x92, 0x9b, 0x90, 0x6, 0x20, 0xf0,

    /* U+0041 "A" */
    0x10, 0x60, 0xa1, 0x44, 0x8f, 0x91, 0x42, 0x82,

    /* U+0042 "B" */
    0xf2, 0x28, 0xa2, 0xf2, 0x38, 0x63, 0xf8,

    /* U+0043 "C" */
    0x38, 0x8a, 0x4, 0x8, 0x10, 0x20, 0x21, 0x38,

    /* U+0044 "D" */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0x62, 0xf0,

    /* U+0045 "E" */
    0xfc, 0x21, 0xf, 0x42, 0x10, 0xf8,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf, 0x42, 0x10, 0x80,

    /* U+0047 "G" */
    0x3c, 0x86, 0x4, 0x8, 0xf0, 0x60, 0xa1, 0x3c,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x84,

    /* U+0049 "I" */
    0xff, 0x80,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x84, 0x31, 0x70,

    /* U+004B "K" */
    0x86, 0x29, 0x28, 0xd2, 0x48, 0xa1, 0x84,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+004D "M" */
    0x83, 0x8f, 0x2e, 0x5a, 0xb5, 0x6c, 0xc9, 0x82,

    /* U+004E "N" */
    0x87, 0x1c, 0x69, 0xa6, 0x59, 0x63, 0x84,

    /* U+004F "O" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x38,

    /* U+0050 "P" */
    0xfa, 0x18, 0x61, 0xfa, 0x8, 0x20, 0x80,

    /* U+0051 "Q" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70, 0x60, 0x70,

    /* U+0052 "R" */
    0xfa, 0x18, 0x61, 0xfa, 0x48, 0xa2, 0x84,

    /* U+0053 "S" */
    0x74, 0x21, 0x82, 0xc, 0x31, 0x70,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0x78,

    /* U+0056 "V" */
    0x85, 0x9, 0x12, 0x44, 0x89, 0xa, 0x18, 0x10,

    /* U+0057 "W" */
    0x84, 0x63, 0x14, 0xc9, 0x32, 0x52, 0x94, 0xa5,
    0x28, 0xcc, 0x21, 0x0,

    /* U+0058 "X" */
    0x85, 0x22, 0x8c, 0x10, 0xc4, 0x92, 0x84,

    /* U+0059 "Y" */
    0x84, 0x89, 0x21, 0x43, 0x2, 0x4, 0x8, 0x10,

    /* U+005A "Z" */
    0xfc, 0x20, 0x84, 0x20, 0x84, 0x20, 0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20,
    0x80,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x21, 0x19, 0x29, 0x48,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x70, 0x42, 0xf8, 0xcf, 0xa0,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x8f, 0xe0,

    /* U+0063 "c" */
    0x76, 0x61, 0x8, 0x61, 0xc0,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+0065 "e" */
    0x76, 0x63, 0xf8, 0x61, 0xc0,

    /* U+0066 "f" */
    0x34, 0x44, 0xe4, 0x44, 0x44, 0x40,

    /* U+0067 "g" */
    0x7e, 0x28, 0xa2, 0xf2, 0x7, 0xe1, 0x85, 0xe0,

    /* U+0068 "h" */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0xbf, 0x80,

    /* U+006A "j" */
    0x20, 0x92, 0x49, 0x24, 0xf0,

    /* U+006B "k" */
    0x84, 0x21, 0x19, 0x53, 0x92, 0x94, 0x40,

    /* U+006C "l" */
    0xaa, 0xaa, 0xb0,

    /* U+006D "m" */
    0xb3, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x3f, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0x4, 0x10,

    /* U+0072 "r" */
    0xba, 0x49, 0x20,

    /* U+0073 "s" */
    0xe8, 0x86, 0x11, 0xe0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x86, 0x24, 0x92, 0x50, 0xc3, 0x0,

    /* U+0077 "w" */
    0x88, 0xcc, 0x55, 0x4a, 0xa5, 0x53, 0x30, 0x88,

    /* U+0078 "x" */
    0x8a, 0x8c, 0x45, 0x2a, 0x20,

    /* U+0079 "y" */
    0x86, 0x24, 0x92, 0x30, 0xc1, 0x8, 0x23, 0x0,

    /* U+007A "z" */
    0xf8, 0x88, 0x44, 0x43, 0xe0,

    /* U+007B "{" */
    0x69, 0x24, 0xa2, 0x49, 0x26,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xc9, 0x24, 0x8a, 0x49, 0x2c,

    /* U+007E "~" */
    0xc1, 0x80,

    /* U+4FDD "保" */
    0x0, 0x2, 0xfe, 0x28, 0x26, 0xfe, 0xa1, 0x2,
    0x10, 0x3f, 0xf2, 0x38, 0x25, 0x42, 0x92, 0x21,
    0x10,

    /* U+51FA "出" */
    0x8, 0x44, 0x62, 0x31, 0x17, 0xf8, 0x42, 0x23,
    0x11, 0x88, 0xff, 0xe0, 0x20,

    /* U+5B58 "存" */
    0x0, 0x4, 0xf, 0xfc, 0x80, 0x20, 0xb, 0xe4,
    0x13, 0x8, 0x5f, 0xd0, 0x84, 0x21, 0x38,

    /* U+5E74 "年" */
    0x0, 0x4, 0x0, 0xff, 0xa1, 0x4, 0x21, 0x7f,
    0xc8, 0x81, 0x10, 0xff, 0xe0, 0x40, 0x8, 0x1,
    0x0,

    /* U+65E5 "日" */
    0xff, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81, 0x81,
    0xff, 0x81,

    /* U+6708 "月" */
    0x3f, 0x90, 0x4f, 0xe4, 0x12, 0x9, 0xfd, 0x2,
    0x81, 0x40, 0xc1, 0xc0,

    /* U+9000 "退" */
    0x27, 0xc0, 0xf9, 0x91, 0x3, 0xde, 0x4c, 0x49,
    0x9, 0x11, 0x79, 0x50, 0x11, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 43, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 57, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 103, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 103, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 20, .adv_w = 172, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 48, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 42, .adv_w = 60, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 47, .adv_w = 60, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 52, .adv_w = 85, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 54, .adv_w = 103, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 58, .adv_w = 48, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 64, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 60, .adv_w = 48, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 76, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 70, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 103, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 103, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 103, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 103, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 48, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 48, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 137, .adv_w = 103, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 141, .adv_w = 103, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 144, .adv_w = 103, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 148, .adv_w = 86, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 175, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 169, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 129, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 136, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 52, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 100, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 136, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 139, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 288, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 111, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 135, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 106, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 164, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 96, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 60, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 363, .adv_w = 76, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 372, .adv_w = 60, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 377, .adv_w = 103, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 381, .adv_w = 106, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 382, .adv_w = 114, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 383, .adv_w = 105, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 103, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 57, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 428, .adv_w = 113, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 49, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 50, .box_w = 3, .box_h = 12, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 442, .adv_w = 100, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 51, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 173, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 114, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 479, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 487, .adv_w = 69, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 87, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 68, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 113, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 94, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 147, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 94, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 531, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 60, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 541, .adv_w = 49, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 543, .adv_w = 60, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 548, .adv_w = 103, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 550, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 567, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 580, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 595, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 612, .adv_w = 192, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 622, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 634, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x21d, 0xb7b, 0xe97, 0x1608, 0x172b, 0x4023
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 20445, .range_length = 16420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t ui_font_Font4 = {
#else
lv_font_t ui_font_Font4 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT4*/

