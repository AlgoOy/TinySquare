/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-11     AlgoOy     the first version
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

void tnsq_gfx_refresh_layer_text(tnsq_gfx_layer_text_t *ptThis, const arm_2d_tile_t *ptTile)
{
    arm_2d_canvas(ptTile, __layer_text_canvas)
    {
        arm_lcd_text_set_target_framebuffer(ptTile);
        arm_lcd_text_set_font(ptThis->tCFG.ptFont);
        arm_lcd_text_set_draw_region(&ptThis->tCFG.tRegion);
        arm_lcd_text_set_colour(ptThis->tCFG.tColour.tForeground, ptThis->tCFG.tColour.tBackground);
        arm_lcd_text_set_opacity(ptThis->tCFG.chOpacity);
        arm_lcd_text_location(ptThis->tCFG.tDrawOffset.iX, ptThis->tCFG.tDrawOffset.iY);
        arm_lcd_puts(ptThis->pchStr);
    }
    arm_2d_op_wait_async(NULL);
}
    
int tnsq_gfx_layer_text_printf(tnsq_gfx_layer_text_t *ptThis, const char *format, ...)
{   
    int real_size;
    __va_list ap;
    va_start(ap, format);
        real_size = vsnprintf(ptThis->pchStr, __LCD_PRINTF_CFG_TEXT_BUFFER_SIZE__, format, ap);
    va_end(ap);
    real_size = MIN(sizeof(__LCD_PRINTF_CFG_TEXT_BUFFER_SIZE__), real_size);
    ptThis->pchStr[real_size] = '\0';
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
    
    char *pchStr = (char *)malloc(sizeof(__LCD_PRINTF_CFG_TEXT_BUFFER_SIZE__ + 1));
    if (pchStr == NULL)
    {
        return NULL;
    }
    else
    {
        pchStr[0] = '\0';
    }
    
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_text_t));
    
    *ptThis = (tnsq_gfx_layer_text_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_TEXT,
            .bIsVisible = RT_TRUE,
            .u7LayerID = 0,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .blsUserAllocated = blsUserAllocated,
        .tCFG = *ptCFG,
        .pchStr = pchStr,
    };
    
    return ptThis;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif