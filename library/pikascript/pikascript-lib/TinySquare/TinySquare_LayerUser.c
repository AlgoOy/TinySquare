#include "pikaScript.h"
#include "tnsq_gfx_layer_user.h"
#include "arm_extra_controls.h"

static void userFunc(uint8_t idx, arm_2d_tile_t const *ptTile, const rt_bool_t bIsNewFrame)
{
    arm_2d_canvas(ptTile, __userFunc)
    {
        switch (idx)
        {
        case 0:
            draw_round_corner_box(ptTile, &__userFunc, GLCD_COLOR_WHITE, 0, bIsNewFrame);
            break;
        case 1:
            draw_round_corner_box(ptTile, &__userFunc, GLCD_COLOR_BLACK, 255, bIsNewFrame);
            break;
        case 2:
            draw_round_corner_box(ptTile, &__userFunc, GLCD_COLOR_RED, 255, bIsNewFrame);
            break;
        default:
            break;
        }
    }
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