/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-30     AlgoOy     the first version
 */

#define __TNSQ_GFX_LAYER_NUM_IMPLEMENT__
#define __NUMBER_LIST_IMPLEMENT__
#define __ARM_2D_HELPER_LIST_VIEW_IMPLEMENT__
#include "tnsq_gfx_layer_num.h"

#include "arm_2d_helper.h"

#include "tnsq_evt_key.h"

//todo: just for test
#include "stdio.h"
 
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

static rt_bool_t __idx = RT_TRUE;

void tnsq_gfx_refresh_layer_num(tnsq_gfx_layer_num_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_region_list_item_t *ptDirtyRegion, rt_bool_t bIsNewFrame)
{
    arm_2d_canvas(ptTile, __layer_num_canvas)
    {
        while (arm_fsm_rt_cpl != number_list_show(&this.tNumber, ptTile, NULL, bIsNewFrame));
    }
    arm_2d_op_wait_async(NULL);
    
    if (!ptDirtyRegion[0].bUpdated && __idx)
    {
        __idx = RT_FALSE;
        
        ptDirtyRegion[0].tRegion = this.tDirtyRegion;
        ptDirtyRegion[0].bUpdated = true;
    }
}

void tnsq_gfx_clear_layer_num_dirty_region(tnsq_gfx_layer_num_t *ptThis)
{
    __idx = RT_TRUE;
}

void tnsq_gfx_layer_num_get_dirty_region(tnsq_gfx_layer_num_t *ptThis, arm_2d_scene_player_t *ptDispAdapter)
{
    arm_2d_region_t tScreen = arm_2d_helper_pfb_get_display_area(
        &ptDispAdapter->use_as__arm_2d_helper_pfb_t);
    
    this.tDirtyRegion = (arm_2d_region_t) {
        .tLocation = {
            .iX = ((tScreen.tSize.iWidth - this.tNumber.tNumListCFG.tListSize.iWidth) >> 1),
            .iY = ((tScreen.tSize.iHeight - this.tNumber.tNumListCFG.tListSize.iHeight) >> 1),
        },
        .tSize = this.tNumber.tNumListCFG.tListSize,
    };
}

void tnsq_gfx_layer_num_evt_handle(tnsq_gfx_layer_num_t *ptThis)
{
    tnsq_evt_key_t tKey = {0};
    rt_err_t tErr = tnsq_evt_itc_get(&tKey, RT_WAITING_NO);
    while(tErr != -RT_ETIMEOUT && tErr != -RT_ERROR)
    {
        if(tKey.tEvent != TNSQ_EVT_KEY_EVENT_PRESSED && tKey.tEvent != TNSQ_EVT_KEY_EVENT_LONG_PRESSED)
        {
            tErr = tnsq_evt_itc_get(&tKey, RT_WAITING_NO);
            continue;
        }
        else
        {
            switch (tKey.tDirection) 
            {
            case TNSQ_EVT_KEY_DIRECTION_UP:
                numer_list_move_selection(&this.tNumber, -1, this.nFinishInMs);
                return;
            case TNSQ_EVT_KEY_DIRECTION_DOWN:
                numer_list_move_selection(&this.tNumber, 1, this.nFinishInMs);
                return;
            case TNSQ_EVT_KEY_DIRECTION_RIGHT:
                this.chSelectedNum = this.tNumber.use_as____arm_2d_list_core_t.Runtime.hwSelection;
                return;
            default:
                return;
            }
        }
    }
}

rt_int8_t tnsq_gfx_layer_num_get_item_idx(tnsq_gfx_layer_num_t *ptThis)
{
    rt_int8_t chSelectedNum = this.chSelectedNum;
    this.chSelectedNum = -1;
    return chSelectedNum;
}

extern 
const arm_2d_tile_t c_tileListCoverMask;

static 
IMPL_PFB_ON_DRAW(__arm_2d_number_list_draw_cover)
{
    ARM_2D_UNUSED(bIsNewFrame);
    
    number_list_t *ptThis = (number_list_t *)pTarget;

    arm_2d_canvas(ptTile, __canvas) {

        arm_2d_align_centre(__canvas, c_tileListCoverMask.tRegion.tSize) {
            arm_2d_fill_colour_with_mask(   ptTile, 
                                            &__centre_region, 
                                            &c_tileListCoverMask, 
                                            (arm_2d_color_rgb565_t)this.tNumListCFG.tBackgroundColour
            );
        }
    }

    arm_2d_op_wait_async(NULL);
    
    return arm_fsm_rt_cpl;
}

ARM_NONNULL(1) tnsq_gfx_layer_num_t *__tnsq_gfx_layer_num_init(tnsq_gfx_layer_num_cfg_t *ptCFG, tnsq_gfx_layer_num_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_num_t *)malloc(sizeof(tnsq_gfx_layer_num_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
        
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_num_t));
    
    *ptThis = (tnsq_gfx_layer_num_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_NUM,
            .blsUserAllocated = blsUserAllocated,
            .bIsVisible = RT_TRUE,
            .u7LayerID = 0,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .nFinishInMs = ptCFG->nFinishInMs,
        .chSelectedNum = -1,
    };
    
    do {
        number_list_cfg_t tNumCFG = {
            .hwCount = ptCFG->chNum,
            .nStart = 0,
            .iDelta = 1,
            .tFontColour = ptCFG->tColor.font,
            .tBackgroundColour = ptCFG->tColor.background,
            .chNextPadding = ptCFG->tPadding.next,
            .chPrviousePadding = ptCFG->tPadding.pre,
            .fnOnDrawListCover = &__arm_2d_number_list_draw_cover,
        };
        
        if (ptCFG->ptFont == NULL)
        {
            tNumCFG.ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A4_DIGITS_ONLY;
        }
        else
        {
            tNumCFG.ptFont = ptCFG->ptFont;
        }
        
        tNumCFG.tListSize.iWidth = tNumCFG.ptFont->tCharSize.iWidth * 2;
        tNumCFG.tListSize.iHeight = (tNumCFG.ptFont->tCharSize.iHeight + ptCFG->tPadding.pre + ptCFG->tPadding.next) * ptCFG->chShowItemNum;
        
        number_list_init(&this.tNumber, &tNumCFG);
    } while (0);
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif