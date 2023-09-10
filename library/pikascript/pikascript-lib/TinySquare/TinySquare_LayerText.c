#include "pikaScript.h"
#include "tnsq_gfx_layer_text.h"
#include "number_list.h"

void TinySquare_LayerText___init__(PikaObj *self, int fontType, int color, int opacity, PikaObj* region)
{
    arm_2d_font_t *ptFont = (arm_2d_font_t *)&ARM_2D_FONT_6x8;
    switch (fontType)
    {
    case 0:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_6x8;
        break;
    case 1:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_16x24;
        break;
    case 2:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A2_DIGITS_ONLY;
        break;
    case 3:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A4_DIGITS_ONLY;
        break;
    case 4:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A8_DIGITS_ONLY;
        break;
    }
    tnsq_gfx_layer_text_cfg_t tCFG = {
        .ptFont = ptFont,
        .tColour.tForeground = color,
        .chOpacity = opacity,
        .tRegion = *(arm_2d_region_t *)obj_getStruct(region, "_self"),
    };
    tnsq_gfx_layer_text_t *_self = tnsq_gfx_layer_text_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

void TinySquare_LayerText_print_str(PikaObj *self, char* format, char* string)
{
    tnsq_gfx_layer_text_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_layer_text_printf(_self, format, string);
}

void TinySquare_LayerText_print_num(PikaObj *self, char* format, int number)
{
    tnsq_gfx_layer_text_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_layer_text_printf(_self, format, number);
}