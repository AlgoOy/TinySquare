/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-11     AlgoOy     the first version
 */

#define __TNSQ_GFX_LAYER_MENU_IMPLEMENT__
#define __NUMBER_LIST_IMPLEMENT__
#define __ARM_2D_HELPER_LIST_VIEW_IMPLEMENT__
#include "tnsq_gfx_layer_menu.h"

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
    
typedef struct tnsq_gfx_list_item_t tnsq_gfx_list_item_t;

#define __REF_ITEM_ARRAY(__PTR, __INDEX) (arm_2d_list_item_t *)                 \
                                    (   ((uintptr_t)(__PTR))                    \
                                    +   this.tListView.tListViewCFG.hwItemSizeInByte * (__INDEX))

struct tnsq_gfx_list_item_t
{
    implement(arm_2d_list_item_t);
    struct tItemFormat tItemNormalAttr;
    struct tItemFormat tItemSelectedAttr;
    char *pchStr;
};

static rt_bool_t __idx = RT_TRUE;

void tnsq_gfx_refresh_layer_menu(tnsq_gfx_layer_menu_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_region_list_item_t *ptDirtyRegion, rt_bool_t bIsNewFrame)
{
    while (arm_fsm_rt_cpl != list_view_show(&this.tListView, ptTile, NULL, bIsNewFrame));
    arm_2d_op_wait_async(NULL);
    
    if (!ptDirtyRegion[0].bUpdated && __idx)
    {
        __idx = RT_FALSE;
        
        ptDirtyRegion[0].tRegion = this.tDirtyRegion;
        ptDirtyRegion[0].bUpdated = true;
    }
}

void tnsq_gfx_clear_layer_menu_dirty_region(tnsq_gfx_layer_menu_t *ptThis)
{
    __idx = RT_TRUE;
}

void tnsq_gfx_layer_menu_evt_handle(tnsq_gfx_layer_menu_t *ptThis)
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
            case TNSQ_EVT_KEY_DERECTION_UP:
                list_view_move_selection(&this.tListView, -1, this.nFinishInMs);
                return;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                list_view_move_selection(&this.tListView, 1, this.nFinishInMs);
                return;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                this.pchSelectedStr = ((tnsq_gfx_list_item_t *)__REF_ITEM_ARRAY(this.tListView.tListViewCFG.ptItems, 
                    this.tListView.use_as____arm_2d_list_core_t.Runtime.hwSelection))->pchStr;
                this.chSelectedIdx = this.tListView.use_as____arm_2d_list_core_t.Runtime.hwSelection;
                return;
            default:
                return;
            }
        }
    }
}

char *tnsq_gfx_layer_menu_get_item_name(tnsq_gfx_layer_menu_t *ptThis)
{
    char *pchSelectedStr = this.pchSelectedStr;
    this.pchSelectedStr = NULL;
    return pchSelectedStr;
}

rt_int8_t tnsq_gfx_layer_menu_get_item_idx(tnsq_gfx_layer_menu_t *ptThis)
{
    rt_int8_t chSelectedIdx = this.chSelectedIdx;
    this.chSelectedIdx = -1;
    return chSelectedIdx;
}

static arm_fsm_rt_t _list_view_item_draw_func(arm_2d_list_item_t *ptItem, const arm_2d_tile_t *ptTile, bool bIsNewFrame, arm_2d_list_item_param_t *ptParam)
{    
    tnsq_gfx_list_item_t *ptThis = (tnsq_gfx_list_item_t *)ptItem;
    
    rt_uint8_t chOpacity = 0;
    
    arm_2d_canvas(ptTile, __canvas)
    {
        if (ptParam->bIsSelected)
        {
            chOpacity = arm_2d_helper_alpha_mix(this.tItemSelectedAttr.chOpacity, ptParam->chOpacity);
            draw_round_corner_box(ptTile, &__canvas, this.tItemSelectedAttr.tColor.box, chOpacity, bIsNewFrame);
            arm_lcd_text_set_colour(this.tItemSelectedAttr.tColor.font, GLCD_COLOR_BLACK);
        }
        else
        {
            chOpacity = arm_2d_helper_alpha_mix(this.tItemNormalAttr.chOpacity, ptParam->chOpacity);
            draw_round_corner_box(ptTile, &__canvas, this.tItemNormalAttr.tColor.box, chOpacity, bIsNewFrame);
            arm_lcd_text_set_colour(this.tItemNormalAttr.tColor.font, GLCD_COLOR_BLACK);
        }
        
        arm_2d_size_t tTextSize = ARM_2D_FONT_16x24.use_as__arm_2d_font_t.tCharSize;
        tTextSize.iWidth *= strlen(this.pchStr);
        
        arm_lcd_text_set_target_framebuffer(ptTile);
        arm_lcd_text_set_font((arm_2d_font_t *)&ARM_2D_FONT_16x24);
        arm_lcd_text_set_opacity(chOpacity);
        arm_print_banner(this.pchStr, __canvas);
    }
    
    return arm_fsm_rt_cpl;
}

void tnsq_gfx_layer_menu_get_dirty_region(tnsq_gfx_layer_menu_t *ptThis, arm_2d_scene_player_t *ptDispAdapter)
{
    arm_2d_region_t tScreen = arm_2d_helper_pfb_get_display_area(
        &ptDispAdapter->use_as__arm_2d_helper_pfb_t);
    
    this.tDirtyRegion = (arm_2d_region_t) {
        .tLocation = {
            .iX = ((tScreen.tSize.iWidth - this.tListView.tListViewCFG.tListSize.iWidth) >> 1),
            .iY = ((tScreen.tSize.iHeight - this.tListView.tListViewCFG.tListSize.iHeight) >> 1),
        },
        .tSize = this.tListView.tListViewCFG.tListSize,
    };
}

void tnsq_gfx_layer_menu_depose(tnsq_gfx_layer_menu_t *ptThis)
{
    if (this.tListView.tListViewCFG.ptItems != NULL)
    {
        free(this.tListView.tListViewCFG.ptItems);
    }
}

ARM_NONNULL(1) tnsq_gfx_layer_menu_t *__tnsq_gfx_layer_menu_init(tnsq_gfx_layer_menu_cfg_t *ptCFG, tnsq_gfx_layer_menu_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_menu_t *)malloc(sizeof(tnsq_gfx_layer_menu_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
        
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_menu_t));
    
    *ptThis = (tnsq_gfx_layer_menu_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_MENU,
            .blsUserAllocated = blsUserAllocated,
            .bIsVisible = RT_TRUE,
            .u7LayerID = 0,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .tItemSize = ptCFG->tItemGeneral.tItemSize,
        .nFinishInMs = ptCFG->tItemGeneral.nFinishInMs,
        .chSelectedIdx = -1,
        .pchSelectedStr = NULL,
    };
    
    do {
        tnsq_gfx_list_item_t *ptItems = (tnsq_gfx_list_item_t *)malloc(sizeof(tnsq_gfx_list_item_t) * ptCFG->tItemGeneral.chItemsNum);
        
        for (int idx = 0; idx < ptCFG->tItemGeneral.chItemsNum; idx ++)
        {
            ptItems[idx] = (tnsq_gfx_list_item_t){
                .use_as__arm_2d_list_item_t = {
                    .hwID = idx,
                    .bIsEnabled = true,
                    .bIsVisible = true,
                    .bIsReadOnly = true,
                    .Padding = {
                        ptCFG->tItemGeneral.tItemPadding.pre,
                        ptCFG->tItemGeneral.tItemPadding.next,
                    },
                    .tSize = ptCFG->tItemGeneral.tItemSize,
                    .fnOnDrawItem = &_list_view_item_draw_func,
                    .pTarget = (uintptr_t) ptThis,
                },
                .tItemNormalAttr = ptCFG->tItemNormal,
                .tItemSelectedAttr = ptCFG->tItemSelected,
                .pchStr = ptCFG->tItemGeneral.pchItems[idx],
            };
        }
        
        list_view_cfg_t tListViewCFG = {
            .fnIterator = &ARM_2D_LIST_ITERATOR_ARRAY,
            .fnCalculator = &ARM_2D_LIST_CALCULATOR_MIDDLE_ALIGNED_VERTICAL,
            
            .tListSize = 
            {
                .iWidth = ptCFG->tItemGeneral.tItemSize.iWidth,
                .iHeight = (ptCFG->tItemGeneral.tItemSize.iHeight + ptCFG->tItemGeneral.tItemPadding.pre + ptCFG->tItemGeneral.tItemPadding.pre) * ptCFG->tItemGeneral.chShowItemNum,
            },
            .ptItems = (arm_2d_list_item_t *)ptItems,
            .hwCount = ptCFG->tItemGeneral.chItemsNum,
            .hwItemSizeInByte = sizeof(tnsq_gfx_list_item_t),
            
            .bIgnoreBackground = true,
        };
        
        list_view_init(&this.tListView, &tListViewCFG);
    } while (0);
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif