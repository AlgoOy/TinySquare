#include "pikaScript.h"
#include "tnsq_gfx_layer_num.h"

void TinySquare_LayerNum___init__(PikaObj *self, int number, int bgColor, int textColor)
{
    tnsq_gfx_layer_num_cfg_t tCFG = {
        .chNum = number,
        .nFinishInMs = 150,
        .chShowItemNum = 3,
        .tColor = {
            .font = textColor,
            .background = bgColor,
        },
        .tPadding = {0},
        .ptFont = NULL,
    };
    tnsq_gfx_layer_num_t *_self = tnsq_gfx_layer_num_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

int TinySquare_LayerNum_get_idx(PikaObj *self)
{
    tnsq_gfx_layer_num_t *_self = obj_getPtr(self, "_self");
    return tnsq_gfx_layer_num_get_item_idx(_self);
}