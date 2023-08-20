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
#include "tnsq_gfx_layer_menu.h"

#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

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

#define TNSQ_GFX_ITEM_BG_OPACITY    (255)

struct tnsq_gfx_list_item_t
{
    implement(arm_2d_list_item_t);
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
        
        ptDirtyRegion[0].tRegion = (arm_2d_region_t){
            .tLocation = {
                .iX = 0,
                .iY = ((__GLCD_CFG_SCEEN_HEIGHT__ - 110) >> 1),
            },
            .tSize = {
                .iWidth = __GLCD_CFG_SCEEN_WIDTH__,
                .iHeight = 110,
            },
        };
        ptDirtyRegion[0].bUpdated = true;

        printf("here: %d\n", bIsNewFrame ? 1 : 0);
    }
    
//    if (this.bIsDirty == RT_TRUE)
//    {
//        arm_2d_size_t tTextSize = this.tCFG.ptFont->tCharSize;
//        tTextSize.iWidth *= strlen(this.pchStr);
//        
//        arm_2d_container(ptTile, __text_tile, &this.tCFG.tRegion)
//        {
//            arm_2d_align_centre(__text_tile_canvas, tTextSize)
//            {
//                arm_lcd_text_set_target_framebuffer((arm_2d_tile_t *)&__text_tile);
//                arm_lcd_text_set_font((arm_2d_font_t *)ptThis->tCFG.ptFont);
//                arm_lcd_text_set_draw_region(&__centre_region);
//                arm_lcd_text_set_colour(this.tCFG.tColour.tForeground, GLCD_COLOR_WHITE);
//                arm_lcd_text_set_opacity(this.tCFG.chOpacity);
//                arm_lcd_puts(this.pchStr);
//            }
//        }
//        arm_2d_op_wait_async(NULL);
//        
//        if (ptDirtyRegion[0].bUpdated == false && __idx)
//        {
//            __idx = RT_FALSE;
//            ptDirtyRegion[0].tRegion = this.tCFG.tRegion;
//            ptDirtyRegion[0].bUpdated = true;
//        }
//    }
}

void tnsq_gfx_clear_layer_menu_dirty_region(tnsq_gfx_layer_menu_t *ptThis)
{
    __idx = RT_TRUE;
//    this.bIsDirty = RT_FALSE;
//    __idx = RT_TRUE;
}

static arm_fsm_rt_t _list_view_item_draw_func(arm_2d_list_item_t *ptItem, const arm_2d_tile_t *ptTile, bool bIsNewFrame, arm_2d_list_item_param_t *ptParam)
{    
    tnsq_gfx_list_item_t *ptThis = (tnsq_gfx_list_item_t *)ptItem;
    
    rt_uint8_t chOpacity = arm_2d_helper_alpha_mix(TNSQ_GFX_ITEM_BG_OPACITY, ptParam->chOpacity);
    
    arm_2d_canvas(ptTile, __canvas)
    {
        draw_round_corner_box(ptTile, &__canvas, GLCD_COLOR_WHITE, chOpacity, bIsNewFrame);
        
        arm_2d_size_t tTextSize = ARM_2D_FONT_16x24.use_as__arm_2d_font_t.tCharSize;
        tTextSize.iWidth *= strlen(this.pchStr);
        
        arm_2d_align_centre(__canvas, tTextSize)
        {
            arm_lcd_text_set_target_framebuffer(ptTile);
            arm_lcd_text_set_font((arm_2d_font_t *)&ARM_2D_FONT_16x24);
            arm_lcd_text_set_colour(__RGB(0x94, 0xd2, 0x52), GLCD_COLOR_BLACK);
            arm_lcd_text_set_opacity(chOpacity);
            //arm_lcd_puts(this.pchStr);
            arm_print_banner(this.pchStr, __canvas);
        }
    }
    
    return arm_fsm_rt_cpl;
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
            .bIsVisible = RT_TRUE,
            .u7LayerID = 0,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .blsUserAllocated = blsUserAllocated,
    };
    
    do {
        tnsq_gfx_list_item_t *ptItems = (tnsq_gfx_list_item_t *)malloc(sizeof(tnsq_gfx_list_item_t) * ptCFG->chItemsNum);
        
        for (int idx = 0; idx < ptCFG->chItemsNum; idx ++)
        {
            ptItems[idx] = (tnsq_gfx_list_item_t){
                .pchStr = ptCFG->pchItems[idx],
                .use_as__arm_2d_list_item_t = {
                    .hwID = idx,
                    .bIsEnabled = true,
                    .bIsVisible = true,
                    .bIsReadOnly = true,
                    .Padding = {
                        5,5,
                    },
                    .tSize = { 90, 110 },
                    .fnOnDrawItem = &_list_view_item_draw_func,
                    .pTarget = (uintptr_t) ptThis,
                },
            };
        }
        
        list_view_cfg_t tListViewCFG = {
            .fnIterator = &ARM_2D_LIST_ITERATOR_ARRAY,
            .fnCalculator = &ARM_2D_LIST_CALCULATOR_MIDDLE_ALIGNED_HORIZONTAL,
            
            .tListSize = {0, 110},
            .ptItems = (arm_2d_list_item_t *)ptItems,
            .hwCount = ptCFG->chItemsNum,
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