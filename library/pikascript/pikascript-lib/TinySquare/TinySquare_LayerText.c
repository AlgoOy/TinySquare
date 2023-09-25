#include "pikaScript.h"
#include "tnsq_gfx_layer_text.h"
#include "TinySquare_Common.h"

void TinySquare_LayerText___init__(PikaObj *self, int fontType, int color, int opacity, PikaObj* region)
{
    tnsq_gfx_layer_text_cfg_t tCFG = {
        .ptFont = get_font_ptr(fontType),
        .tColour.tForeground = color,
        .chOpacity = opacity,
        .tRegion = *(arm_2d_region_t *)obj_getStruct(region, "_self"),
    };
    tnsq_gfx_layer_text_t *_self = tnsq_gfx_layer_text_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

void TinySquare_LayerText_print_str(PikaObj *self, char* format, char* string)
{
    if (!strcmp(format, ""))
    {
        format = "%s";
    }
    tnsq_gfx_layer_text_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_layer_text_printf(_self, format, string);
}

void TinySquare_LayerText_print_num(PikaObj *self, char* format, int number)
{
    if (!strcmp(format, ""))
    {
        format = "%d";
    }
    tnsq_gfx_layer_text_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_layer_text_printf(_self, format, number);
}