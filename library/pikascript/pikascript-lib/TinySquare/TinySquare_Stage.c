#include "pikaScript.h"
#include "tnsq_gfx_stage.h"
#include "arm_2d_disp_adapters.h"

void TinySquare_Stage___init__(PikaObj *self)
{
    tnsq_gfx_stage_cfg_t tCFG = {
        .ptDispAdapter.ptPlayer = &DISP0_ADAPTER,
        .ptDispAdapter.ptPlayerTask = disp_adapter0_task,
    };
    tnsq_gfx_stage_t *_self = tnsq_gfx_stage_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

int TinySquare_Stage_register_layer(PikaObj *self, PikaObj* layer)
{
    tnsq_gfx_stage_t *_self = obj_getPtr(self, "_self");
    return tnsq_gfx_register_layer_to_stage(_self, obj_getPtr(layer, "_self"));
}

void TinySquare_Stage_remove_layer(PikaObj *self, int layerID)
{
    tnsq_gfx_stage_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_remove_layer(_self, layerID);
}

void TinySquare_Stage_visible_layer(PikaObj *self, int layerID)
{
    tnsq_gfx_stage_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_make_layer_visible(_self, layerID);
}

void TinySquare_Stage_invisible_layer(PikaObj *self, int layerID)
{
    tnsq_gfx_stage_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_make_layer_invisible(_self, layerID);
}