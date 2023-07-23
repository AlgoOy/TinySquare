/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#define __TNSQ_GFX_LAYER_BG_CL_IMPLEMENT__
#include "tnsq_gfx_layer_bg_cl.h"

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
    
void tnsq_gfx_refresh_layer_bg_cl(tnsq_gfx_layer_bg_cl_t *ptThis, const arm_2d_tile_t *ptTile)
{
    if (this.tCFG.ptBackGroundColorMask != NULL)
    {
        arm_2d_fill_colour_with_mask_and_opacity(
            ptTile, 
            &this.tCFG.tRegion,
            this.tCFG.ptBackGroundColorMask,
            this.tCFG.tColor,
            this.tCFG.chOpacity
        );
    }
    else
    {
        arm_2d_fill_colour_with_opacity(
            ptTile, 
            &this.tCFG.tRegion,
            this.tCFG.tColor,
            this.tCFG.chOpacity
        );
    }
    arm_2d_op_wait_async(NULL);
}
    
ARM_NONNULL(1) tnsq_gfx_layer_bg_cl_t *__tnsq_gfx_layer_bg_cl_init(tnsq_gfx_layer_bg_cl_cfg_t *ptCFG, tnsq_gfx_layer_bg_cl_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_bg_cl_t *)malloc(sizeof(tnsq_gfx_layer_bg_cl_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
    
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_bg_cl_t));
    
    *ptThis = (tnsq_gfx_layer_bg_cl_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_BG_CL,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .blsUserAllocated = blsUserAllocated,
        .tCFG = *ptCFG,
    };
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
