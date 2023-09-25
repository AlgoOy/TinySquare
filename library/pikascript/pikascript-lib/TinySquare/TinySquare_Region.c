#include "pikaScript.h"
#include "tnsq_gfx_utils.h"

void TinySquare_Region___init__(PikaObj *self, int hwX, int hwY, int hwWidth, int hwHeight)
{
    arm_2d_region_t _self = {
        .tLocation = {
            .iX = hwX,
            .iY = hwY,
        },
        .tSize = {
            .iWidth = hwWidth,
            .iHeight = hwHeight,
        },
    };
    obj_setStruct(self, "_self", _self);
}