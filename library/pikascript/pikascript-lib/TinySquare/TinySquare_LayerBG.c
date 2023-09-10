#include "pikaScript.h"
#include "tnsq_gfx_layer_bg.h"

void TinySquare_LayerBG___init__(PikaObj *self, Arg* bg, Arg* bgMask, PikaObj* region)
{
    arm_2d_tile_t *ptBackground = arg_getPtr(bg);
    arm_2d_tile_t *ptBackgroundMask = arg_getPtr(bgMask);
    tnsq_gfx_layer_bg_cfg_t tCFG = {
        .ptBackGround = ptBackground,
        .ptBackGroundMask = ptBackgroundMask,
        .tRegion = *(arm_2d_region_t *)obj_getStruct(region, "_self"),
    };
    tnsq_gfx_layer_bg_t *_self = tnsq_gfx_layer_bg_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}