#include "pikaScript.h"
#include "arm_extra_controls.h"

void TinySquare_BorderOpacity___init__(PikaObj *self, int left, int right, int top, int bottom)
{
    arm_2d_border_opacity_t _self = {
        .chLeft = left,
        .chRight = right,
        .chTop = top,
        .chBottom = bottom,
    };
    obj_setStruct(self, "_self", _self);
}