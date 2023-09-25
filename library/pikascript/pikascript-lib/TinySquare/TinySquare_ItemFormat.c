#include "pikaScript.h"
#include "tnsq_gfx_layer_menu.h"

void TinySquare_ItemFormat___init__(PikaObj *self, int boxColor, int textColor, int opacity)
{
    struct tItemFormat _self = {
        .tColor.box = boxColor,
        .tColor.font = textColor,
        .chOpacity = opacity,
    };
    obj_setStruct(self, "_self", _self);
}