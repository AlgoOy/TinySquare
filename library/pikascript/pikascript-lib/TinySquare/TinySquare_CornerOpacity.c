#include "pikaScript.h"
#include "arm_extra_controls.h"

void TinySquare_CornerOpacity___init__(PikaObj *self, int leftTop, int rightTop, int rightBottom, int leftBottom)
{
    arm_2d_corner_opacity_t _self = {
        .chTopLeft = leftTop,
        .chTopRight = rightTop,
        .chBottomLeft = rightBottom,
        .chBottomRight = leftBottom,
    };
    obj_setStruct(self, "_self", _self);
}