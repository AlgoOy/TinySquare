#include "pikaScript.h"
#include "tnsq_gfx_utils.h"

void TinySquare_Screen___init__(PikaObj *self)
{
    arm_2d_size_t _self = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
    obj_setStruct(self, "_self", _self);
}

int TinySquare_Screen_height(PikaObj *self)
{
    arm_2d_size_t *_self = obj_getStruct(self, "_self");
    return _self->iHeight;
}

int TinySquare_Screen_width(PikaObj *self)
{
    arm_2d_size_t *_self = obj_getStruct(self, "_self");
    return _self->iWidth;
}