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

#define __GE_STAGE_IMPLEMENT__
#include "__ge_common.h"

#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

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

static void _on_ge_stage_depose(arm_2d_scene_t *ptScene)
{
    ge_stage_t *ptThis = (ge_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
    
    this.use_as__arm_2d_scene_t.ptPlayer = NULL;

    if (this.blsUserAllocated == RT_FALSE) {
        // todo:judge layer free
        free(ptThis);
    }
}

static void _on_ge_stage_background_start(arm_2d_scene_t *ptScene)
{
    ge_stage_t *ptThis = (ge_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

static void _on_ge_stage_background_complete(arm_2d_scene_t *ptScene)
{
    ge_stage_t *ptThis = (ge_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}


static void _on_ge_stage_frame_start(arm_2d_scene_t *ptScene)
{
    ge_stage_t *ptThis = (ge_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

static void _on_ge_stage_frame_complete(arm_2d_scene_t *ptScene)
{
    ge_stage_t *ptThis = (ge_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

static void _before_ge_stage_switching_out(arm_2d_scene_t *ptScene)
{
    ge_stage_t *ptThis = (ge_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

static IMPL_PFB_ON_DRAW(_pfb_draw_ge_stage_background_handler)
{
    ge_stage_t *ptThis = (ge_stage_t *)pTarget;
    ARM_2D_UNUSED(ptTile);
    ARM_2D_UNUSED(bIsNewFrame);
    /*-----------------------draw back ground begin-----------------------*/



    /*-----------------------draw back ground end  -----------------------*/
    arm_2d_op_wait_async(NULL);

    return arm_fsm_rt_cpl;
}

static IMPL_PFB_ON_DRAW(_pfb_draw_ge_stage_handler)
{
    ge_stage_t *ptThis = (ge_stage_t *)pTarget;
    ARM_2D_UNUSED(ptTile);
    ARM_2D_UNUSED(bIsNewFrame);
    
    arm_2d_canvas(ptTile, __top_canvas) {
    /*-----------------------draw the foreground begin-----------------------*/



    /*-----------------------draw the foreground end  -----------------------*/
    }
    arm_2d_op_wait_async(NULL);

    return arm_fsm_rt_cpl;
}

static void _register_stage_to_player(arm_2d_scene_player_t *ptPlayer, ge_stage_t *ptThis)
{
    arm_2d_scene_player_append_scenes(ptPlayer, &this.use_as__arm_2d_scene_t, 1);
}


ARM_NONNULL(1) ge_stage_t *__ge_stage_init(ge_display_adapter_t *ptDispAdapter, ge_stage_t *ptThis)
{
    rt_bool_t blsUserAllocated = RT_FALSE;
    if (ptThis == NULL)
    {
        ptThis = (ge_stage_t *)malloc(sizeof(ge_stage_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }

    memset(ptThis, 0, sizeof(ge_stage_t));

    *ptThis = (ge_stage_t){
        .use_as__arm_2d_scene_t = {
            .fnBackground   = &_pfb_draw_ge_stage_background_handler,
            .fnScene        = &_pfb_draw_ge_stage_handler,
            //.ptDirtyRegion  = (arm_2d_region_list_item_t *)s_tDirtyRegions,

            .fnOnBGStart    = &_on_ge_stage_background_start,
            .fnOnBGComplete = &_on_ge_stage_background_complete,
            .fnOnFrameStart = &_on_ge_stage_frame_start,
            .fnBeforeSwitchOut = &_before_ge_stage_switching_out,
            .fnOnFrameCPL   = &_on_ge_stage_frame_complete,
            .fnDepose       = &_on_ge_stage_depose,
        },
        .blsUserAllocated = blsUserAllocated,
    };
    
    //_register_player_to_gfx_ctrl(ptDispAdapter->ptPlayer);

    _register_stage_to_player(ptDispAdapter->ptPlayer, ptThis);
    
    return ptThis;
}


#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
