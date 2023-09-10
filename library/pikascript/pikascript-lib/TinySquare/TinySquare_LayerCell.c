#include "pikaScript.h"
#include "tnsq_gfx_layer_cell.h"

void TinySquare_LayerCell___init__(PikaObj *self, int hwXCount, int hwYCount)
{
    tnsq_gfx_cell_t tCells[hwXCount * hwYCount];
    memset(tCells, 0, sizeof(tnsq_gfx_cell_t) * hwXCount * hwYCount);
    obj_setStruct(self, "tCells", tCells);
    tnsq_gfx_layer_cell_cfg_t tCFG = {
        .hwXCount = hwXCount,
        .hwYCount = hwYCount,
        .ptCells = (tnsq_gfx_cell_t *)obj_getStruct(self, "tCells"),
    };
    tnsq_gfx_layer_cell_t *_self = tnsq_gfx_layer_cell_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

void TinySquare_LayerCell_draw_cell(PikaObj *self, int hwX, int hwY, int color, int opacity)
{
    tnsq_gfx_layer_cell_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_layer_cell_draw(_self, hwX, hwY, opacity, color);
}
