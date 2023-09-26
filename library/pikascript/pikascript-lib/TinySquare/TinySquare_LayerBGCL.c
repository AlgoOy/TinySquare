#include "pikaScript.h"
#include "tnsq_gfx_layer_bg_cl.h"

void TinySquare_LayerBGCL___init__(PikaObj *self, int type, int color, int opacity, PikaObj* region, PikaObj* borderOpacity, PikaObj* cornerOpacity)
{
    tnsq_gfx_layer_bg_cl_cfg_t tCFG = {
        .tType = type,
        .tColor = color,
        .chOpacity = opacity,
        .ptBackGroundColorMask = NULL,
        .tRegion = *(arm_2d_region_t *)obj_getStruct(region, "_self"),
    };
    if (borderOpacity)
    {
        tCFG.tborderOpacity = *(arm_2d_border_opacity_t *)obj_getStruct(borderOpacity, "_self");
    }
    if (cornerOpacity)
    {
        tCFG.tcornerOpacity = *(arm_2d_corner_opacity_t *)obj_getStruct(cornerOpacity, "_self");
    }
    tnsq_gfx_layer_bg_cl_t *_self = tnsq_gfx_layer_bg_cl_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}