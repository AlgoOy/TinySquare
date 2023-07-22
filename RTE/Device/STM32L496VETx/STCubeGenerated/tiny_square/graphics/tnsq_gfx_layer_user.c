/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#define __TNSQ_GFX_LAYER_USER_IMPLEMENT__
#include "tnsq_gfx_layer_user.h"

#include <stdlib.h>

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wunused-function"
#   pragma clang diagnostic ignored "-Wmissing-declarations"  
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_IAR__
#   pragma diag_suppress=Pa089,Pe188,Pe177,Pe174
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wunused-value"
#endif

#undef this
#define this (*ptThis)
    
void tnsq_gfx_refresh_layer_user(tnsq_gfx_layer_user_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_scene_player_t *ptDispAdapter)
{
    arm_2d_region_t tScreen = arm_2d_helper_pfb_get_display_area(
        &ptDispAdapter->use_as__arm_2d_helper_pfb_t);
    
    for (int i = 0; i < this.tSize.hwXCount * this.tSize.hwYCount; i ++)
    {
        arm_2d_region_t tRegion = (arm_2d_region_t) {
            .tLocation = {
                .iX = (i % this.tSize.hwXCount) * (tScreen.tSize.iWidth / this.tSize.hwXCount),
                .iY = (i / this.tSize.hwXCount) * (tScreen.tSize.iHeight / this.tSize.hwYCount),
            },
            .tSize = {
                .iWidth = tScreen.tSize.iWidth / this.tSize.hwXCount,
                .iHeight = tScreen.tSize.iHeight / this.tSize.hwYCount,
            },
        };
        this.ptFunc(this.pchUserMap[i], ptTile, &tRegion);
    }
}
    
ARM_NONNULL(1) tnsq_gfx_layer_user_t *__tnsq_gfx_layer_user_init(tnsq_gfx_layer_user_cfg_t *ptCFG, tnsq_gfx_layer_user_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_user_t *)malloc(sizeof(tnsq_gfx_layer_user_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
    
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_user_t));
    
    *ptThis = (tnsq_gfx_layer_user_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_USER,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .blsUserAllocated = blsUserAllocated,
        .tSize = {
            .hwXCount = ptCFG->hwXCount,
            .hwYCount = ptCFG->hwYCount,
        },
        .ptFunc = ptCFG->ptFunc,
        .pchUserMap = ptCFG->pchUserMap,
    };
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
