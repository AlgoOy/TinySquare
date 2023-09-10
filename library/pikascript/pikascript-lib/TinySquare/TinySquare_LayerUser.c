#include "pikaScript.h"
#include "tnsq_gfx_layer_user.h"

static void userFunc(uint8_t idx, arm_2d_tile_t const *ptTile, const rt_bool_t bIsNewFrame)
{

}

void TinySquare_LayerUser___init__(PikaObj *self, int hwXCount, int hwYCount)
{
    tnsq_gfx_user_map_t tUserMap[hwXCount * hwYCount];
    memset(tUserMap, 0, sizeof(tnsq_gfx_user_map_t) * hwXCount * hwYCount);
    obj_setStruct(self, "tUserMap", tUserMap);
    tnsq_gfx_layer_user_cfg_t tCFG = {
        .hwXCount = hwXCount,
        .hwYCount = hwYCount,
        .pchUserMap = (tnsq_gfx_user_map_t *)obj_getStruct(self, "tUserMap"),
        .ptFunc = userFunc,
    };
    tnsq_gfx_layer_user_t *_self = tnsq_gfx_layer_user_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

void TinySquare_LayerUser_draw_userMap(PikaObj *self, int hwX, int hwY, int idx)
{
    tnsq_gfx_layer_user_t *_self = obj_getPtr(self, "_self");
    tnsq_gfx_layer_user_draw(_self, hwX, hwY, idx);
}