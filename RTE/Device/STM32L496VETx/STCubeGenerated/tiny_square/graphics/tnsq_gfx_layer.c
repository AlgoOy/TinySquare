/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#include "arm_2d.h"

#define ____TNSQ_GFX_COMMON_IMPLEMENT__
#define __TNSQ_GFX_LAYER_IMPLEMENT__
#include "__tnsq_gfx_common.h"

#include <stdlib.h>
#include <string.h>

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
    
void tnsq_gfx_refresh_layer(tnsq_gfx_layer_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_scene_player_t *ptDispAdapter)
{
    arm_2d_region_t tScreen = arm_2d_helper_pfb_get_display_area(
        &ptDispAdapter->use_as__arm_2d_helper_pfb_t);
    
    for (int i = 0; i < this.tSize.hwXCount * this.tSize.hwYCount; i ++)
    {
        if (this.ptCells[i].blsDirty == RT_TRUE)
        {
            arm_2dp_fill_colour_with_opacity
            (
                NULL,
                ptTile,
                (arm_2d_region_t []) {
                    {
                        .tLocation = {
                            .iX = (i % this.tSize.hwXCount) * (tScreen.tSize.iWidth / this.tSize.hwXCount),
                            .iY = (i / this.tSize.hwXCount) * (tScreen.tSize.iHeight / this.tSize.hwYCount),
                        },
                        .tSize = {
                            .iWidth = tScreen.tSize.iWidth / this.tSize.hwXCount,
                            .iHeight = tScreen.tSize.iHeight / this.tSize.hwYCount,
                        },
                    },
                },
                this.ptCells[i].tColor,
                this.ptCells[i].chOpacity
            );
            arm_2d_op_wait_async(NULL);
        }
    }
}
    
ARM_NONNULL(1) tnsq_gfx_layer_t *__tnsq_gfx_layer_init(tnsq_gfx_layer_cfg_t *ptCFG, tnsq_gfx_layer_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_t *)malloc(sizeof(tnsq_gfx_layer_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
    
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_t));
    
    *ptThis = (tnsq_gfx_layer_t) {
        .blsUserAllocated = blsUserAllocated,
        .tSize = {
            .hwXCount = ptCFG->hwXCount,
            .hwYCount = ptCFG->hwYCount,
        },
        .ptNext = NULL,
        .ptCells = ptCFG->ptCells,
    };
    
    return ptThis;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
