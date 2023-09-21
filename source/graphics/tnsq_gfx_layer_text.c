/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-18     AlgoOy     the first version
 */

#define __TNSQ_GFX_LAYER_TEXT_IMPLEMENT__
#include "tnsq_gfx_layer_text.h"

#include <stdio.h>
 
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
    
#if defined(__IS_COMPILER_IAR__) && __IS_COMPILER_IAR__
#define __va_list    va_list

#endif

static rt_bool_t __idx = RT_TRUE;

void tnsq_gfx_refresh_layer_text(tnsq_gfx_layer_text_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_region_list_item_t *ptDirtyRegion)
{
    if (this.bIsDirty == RT_TRUE)
    {
        arm_2d_size_t tTextSize = this.tCFG.ptFont->tCharSize;
        tTextSize.iWidth *= strlen(this.pchStr);
        
        arm_2d_container(ptTile, __text_tile, &this.tCFG.tRegion)
        {
            arm_2d_align_centre(__text_tile_canvas, tTextSize)
            {
                arm_lcd_text_set_target_framebuffer((arm_2d_tile_t *)&__text_tile);
                arm_lcd_text_set_font((arm_2d_font_t *)ptThis->tCFG.ptFont);
                arm_lcd_text_set_draw_region(&__centre_region);
                arm_lcd_text_set_colour(this.tCFG.tColour.tForeground, GLCD_COLOR_WHITE);
                arm_lcd_text_set_opacity(this.tCFG.chOpacity);
                arm_lcd_puts(this.pchStr);
            }
        }
        arm_2d_op_wait_async(NULL);
        
        if (ptDirtyRegion[0].bUpdated == false && __idx)
        {
            __idx = RT_FALSE;
            ptDirtyRegion[0].tRegion = this.tCFG.tRegion;
            ptDirtyRegion[0].bUpdated = true;
        }
    }
}

void tnsq_gfx_clear_layer_text_dirty_region(tnsq_gfx_layer_text_t *ptThis)
{
    this.bIsDirty = RT_FALSE;
    __idx = RT_TRUE;
}
    
rt_int32_t tnsq_gfx_layer_text_printf(tnsq_gfx_layer_text_t *ptThis, const char *format, ...)
{
    if (ptThis == NULL)
    {
        return -1;
    }
    int real_size;
    __va_list ap;
    va_start(ap, format);
        real_size = vsnprintf(this.pchStr, __LCD_PRINTF_CFG_TEXT_BUFFER_SIZE__, format, ap);
    va_end(ap);
    real_size = MIN(__LCD_PRINTF_CFG_TEXT_BUFFER_SIZE__, real_size);
    this.pchStr[real_size] = '\0';
    this.bIsDirty = RT_TRUE;
    return real_size;
}

ARM_NONNULL(1) tnsq_gfx_layer_text_t *__tnsq_gfx_layer_text_init(tnsq_gfx_layer_text_cfg_t *ptCFG, tnsq_gfx_layer_text_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_text_t *)malloc(sizeof(tnsq_gfx_layer_text_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
    
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_text_t));
    
    *ptThis = (tnsq_gfx_layer_text_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_TEXT,
            .blsUserAllocated = blsUserAllocated,
            .bIsVisible = RT_TRUE,
            .u7LayerID = 0,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .bIsDirty = RT_FALSE,
        .tCFG = *ptCFG,
        .pchStr[0] = '\0',
    };
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif