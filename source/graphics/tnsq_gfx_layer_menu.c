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
                                   
#define STRUCT_ENTRY(STRUCT_ELEM, STRUCT, MEMBER) \
    ((STRUCT *)((uint8_t *)(STRUCT_ELEM) - (size_t)(&((STRUCT *)0)->MEMBER)))

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
            case TNSQ_EVT_KEY_DIRECTION_UP:
                list_view_move_selection(&this.tListView, -1, this.tCFG.tItemGeneral.nFinishInMs);
                return;
            case TNSQ_EVT_KEY_DIRECTION_DOWN:
                list_view_move_selection(&this.tListView, 1, this.tCFG.tItemGeneral.nFinishInMs);
                return;
            case TNSQ_EVT_KEY_DIRECTION_RIGHT:
                this.chSelectedIdx = this.tListView.use_as____arm_2d_list_core_t.Runtime.hwSelection;
                this.pchSelectedStr = this.tCFG.tItemGeneral.pchStringTable[this.chSelectedIdx];
                return;
            default:
                return;
            }
        }
    }
}

const char *tnsq_gfx_layer_menu_get_item_name(tnsq_gfx_layer_menu_t *ptThis)
{
    const char *pchSelectedStr = this.pchSelectedStr;
    this.pchSelectedStr = NULL;
    return pchSelectedStr;
}

rt_int8_t tnsq_gfx_layer_menu_get_item_idx(tnsq_gfx_layer_menu_t *ptThis)
{
    rt_int8_t chSelectedIdx = this.chSelectedIdx;
    this.chSelectedIdx = -1;
    return chSelectedIdx;
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

#if defined(__IS_COMPILER_IAR__) && __IS_COMPILER_IAR__
#define __va_list    va_list
#endif

static int __printf(tnsq_gfx_layer_menu_t *ptThis, const arm_2d_region_t *ptRegion, const char *format, ...)
{
    int real_size;
    static char s_chBuffer[__LCD_PRINTF_CFG_TEXT_BUFFER_SIZE__ + 1];
    __va_list ap;
    va_start(ap, format);
        real_size = vsnprintf(s_chBuffer, sizeof(s_chBuffer)-1, format, ap);
    va_end(ap);
    real_size = MIN(sizeof(s_chBuffer)-1, real_size);
    s_chBuffer[real_size] = '\0';
    
    int16_t iWidth = this.tCFG.tItemGeneral.ptFont->tCharSize.iWidth;
    int16_t iHeight = this.tCFG.tItemGeneral.ptFont->tCharSize.iHeight;

    arm_2d_align_centre( *ptRegion, (int16_t)real_size * iWidth, iHeight) {
        arm_lcd_text_set_draw_region(&__centre_region);
        arm_lcd_puts(s_chBuffer);
        arm_lcd_text_set_draw_region(NULL);
    }
    return real_size;
}

static arm_fsm_rt_t _list_view_item_draw_func(arm_2d_list_item_t *ptItem, const arm_2d_tile_t *ptTile, bool bIsNewFrame, arm_2d_list_item_param_t *ptParam)
{    
    tnsq_gfx_layer_menu_t *ptThis = (tnsq_gfx_layer_menu_t *)ptItem->pTarget;
    
    rt_uint8_t chOpacity = 0;
    
    arm_2d_canvas(ptTile, __canvas)
    {
        if (ptParam->bIsSelected)
        {
            chOpacity = arm_2d_helper_alpha_mix(this.tCFG.tItemSelected.chOpacity, ptParam->chOpacity);
            draw_round_corner_box(ptTile, &__canvas, this.tCFG.tItemSelected.tColor.box, chOpacity, bIsNewFrame);
            arm_lcd_text_set_colour(this.tCFG.tItemSelected.tColor.font, GLCD_COLOR_BLACK);
        }
        else
        {
            chOpacity = arm_2d_helper_alpha_mix(this.tCFG.tItemNormal.chOpacity, ptParam->chOpacity);
            draw_round_corner_box(ptTile, &__canvas, this.tCFG.tItemNormal.tColor.box, chOpacity, bIsNewFrame);
            arm_lcd_text_set_colour(this.tCFG.tItemNormal.tColor.font, GLCD_COLOR_BLACK);
        }
        
        arm_lcd_text_set_font(this.tCFG.tItemGeneral.ptFont);
        arm_lcd_text_set_display_mode(ARM_2D_DRW_PATN_MODE_COPY);
        arm_lcd_text_set_target_framebuffer(ptTile);
        arm_lcd_text_set_opacity(chOpacity);
        
        __printf(ptThis, &__canvas, this.tCFG.tItemGeneral.pchFormatString, this.tCFG.tItemGeneral.pchStringTable[this.tTempItem.hwID]);
        
        arm_lcd_text_set_target_framebuffer(NULL);
    }
    
    return arm_fsm_rt_cpl;
}

static arm_2d_list_item_t *_tnsq_gfx_menu_list_iterator(__arm_2d_list_core_t *ptListView,
														arm_2d_list_iterator_dir_t tDirection,
														uint_fast16_t hwID)
{
    tnsq_gfx_layer_menu_t *ptThis = STRUCT_ENTRY(ptListView, tnsq_gfx_layer_menu_t, tListView);
    int32_t nIterationIndex;
    switch (tDirection) {
        default:
        case __ARM_2D_LIST_GET_ITEM_WITH_ID_WITHOUT_MOVE_POINTER:
            nIterationIndex = hwID;
            nIterationIndex %= this.tCFG.tItemGeneral.chStringCount;
            break;

        case __ARM_2D_LIST_GET_ITEM_AND_MOVE_POINTER:
            this.tListView.nIterationIndex = hwID;
            this.tListView.nIterationIndex %= this.tCFG.tItemGeneral.chStringCount;
            nIterationIndex = this.tListView.nIterationIndex;
            break;

        case __ARM_2D_LIST_GET_PREVIOUS:
            if (this.tListView.nIterationIndex) {
                this.tListView.nIterationIndex--;
            } else {
                this.tListView.nIterationIndex = this.tCFG.tItemGeneral.chStringCount - 1;
            }
            nIterationIndex = this.tListView.nIterationIndex;
            break;

        case __ARM_2D_LIST_GET_NEXT:
            this.tListView.nIterationIndex++;
            this.tListView.nIterationIndex %= this.tCFG.tItemGeneral.chStringCount;
            
            nIterationIndex = this.tListView.nIterationIndex;
            break;

        case __ARM_2D_LIST_GET_FIRST_ITEM_WITHOUT_MOVE_POINTER:
            nIterationIndex = 0;
            break;

        case __ARM_2D_LIST_GET_FIRST_ITEM:
            this.tListView.nIterationIndex = 0;
            nIterationIndex = this.tListView.nIterationIndex;
            break;

        case __ARM_2D_LIST_GET_CURRENT:
            nIterationIndex = this.tListView.nIterationIndex;
            break;

        case __ARM_2D_LIST_GET_LAST_ITEM_WITHOUT_MOVE_POINTER:
            nIterationIndex = this.tCFG.tItemGeneral.chStringCount - 1;
            break;

        case __ARM_2D_LIST_GET_LAST_ITEM:
            this.tListView.nIterationIndex = this.tCFG.tItemGeneral.chStringCount - 1;
            nIterationIndex = this.tListView.nIterationIndex;
            break;
    }

    /* validate item size */
    if (this.tTempItem.tSize.iHeight <= 0) {
        this.tTempItem.tSize.iHeight = this.tCFG.tItemGeneral.ptFont->tCharSize.iHeight;
    }
    if (this.tTempItem.tSize.iWidth <= 0) {
        this.tTempItem.tSize.iWidth 
            = this.tListView.use_as____arm_2d_list_core_t
                .Runtime.tileList.tRegion.tSize.iWidth;
    }

    nIterationIndex %= this.tCFG.tItemGeneral.chStringCount;

    /* update item id : pretend that this is a different list core item */
    this.tTempItem.hwID = (uint16_t)nIterationIndex;

    return &this.tTempItem;
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
        .tTempItem = {
            .hwID = 0,
            .bIsEnabled = true,
            .bIsVisible = true,
            .Padding = {
                ptCFG->tItemGeneral.tItemPadding.pre,
                ptCFG->tItemGeneral.tItemPadding.next,
            },
            .pTarget = (uintptr_t)ptThis,
            .tSize = ptCFG->tItemGeneral.tItemSize,
            .fnOnDrawItem = &_list_view_item_draw_func,
        },
        .tCFG = *ptCFG,
        .chSelectedIdx = -1,
        .pchSelectedStr = NULL,
    };
    
    static const char c_chDefaultFormatString[] = {"%s"};
    static const char c_chDefaultString[] = {"TinySquare"};
    
    do {        
        list_view_cfg_t tListViewCFG = {
            .fnIterator = &_tnsq_gfx_menu_list_iterator,
            .fnCalculator = &ARM_2D_LIST_CALCULATOR_MIDDLE_ALIGNED_FIXED_SIZED_ITEM_NO_STATUS_CHECK_VERTICAL,
            .tListSize = 
            {
                .iWidth = ptCFG->tItemGeneral.tItemSize.iWidth,
                .iHeight = (ptCFG->tItemGeneral.tItemSize.iHeight + ptCFG->tItemGeneral.tItemPadding.pre + ptCFG->tItemGeneral.tItemPadding.pre) * ptCFG->tItemGeneral.chShowItemNum,
            },
            .ptItems = (arm_2d_list_item_t *)&this.tTempItem,
            .hwCount = ptCFG->tItemGeneral.chStringCount,
            .hwItemSizeInByte = sizeof(arm_2d_list_item_t),
            
            .bIgnoreBackground = true,
        };
        
        if (NULL == this.tCFG.tItemGeneral.ptFont) {
            this.tCFG.tItemGeneral.ptFont = (arm_2d_font_t *)&ARM_2D_FONT_6x8;
        }
        
        if (!this.tCFG.tItemGeneral.chStringCount) {
            this.tCFG.tItemGeneral.chStringCount = 1;
        }

        if (NULL == this.tCFG.tItemGeneral.pchStringTable) {
            this.tCFG.tItemGeneral.pchStringTable = (const char **)c_chDefaultString;
        }

        if (NULL == this.tCFG.tItemGeneral.pchFormatString) {
            this.tCFG.tItemGeneral.pchFormatString = c_chDefaultFormatString;
        }
        
        list_view_init(&this.tListView, &tListViewCFG);
    } while (0);
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif