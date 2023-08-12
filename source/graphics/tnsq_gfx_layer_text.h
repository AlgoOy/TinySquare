/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-11     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_LAYER_TEXT_H__
#define __TNSQ_GFX_LAYER_TEXT_H__
 
#ifdef   __cplusplus
extern "C" {
#endif

#include "rtdef.h"

#include "arm_extra_lcd_printf.h"

#include "__tnsq_gfx_layer.h"

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#   pragma clang diagnostic ignored "-Wpadded"
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wpadded"
#endif

#ifdef __TNSQ_GFX_LAYER_TEXT_IMPLEMENT__
#   undef __TNSQ_GFX_LAYER_TEXT_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

typedef struct tnsq_gfx_layer_text_t tnsq_gfx_layer_text_t;
typedef struct tnsq_gfx_layer_text_cfg_t tnsq_gfx_layer_text_cfg_t;

struct tnsq_gfx_layer_text_cfg_t
{
    const arm_2d_font_t *ptFont;
    struct {
        COLOUR_INT_TYPE     tForeground;
        COLOUR_INT_TYPE     tBackground;
    } tColour;
    uint8_t             chOpacity;
    arm_2d_region_t     tRegion;
    arm_2d_location_t   tDrawOffset;
};

struct tnsq_gfx_layer_text_t
{
    ARM_PRIVATE
    (
        implement (tnsq_gfx_layer_base_t);
        rt_bool_t blsUserAllocated;
        tnsq_gfx_layer_text_cfg_t tCFG;
        char *pchStr;
    )
};

#define tnsq_gfx_layer_text_init(__TNSQ_GFX_LAYER_TEXT_CFG_PTR, ...) \
            __tnsq_gfx_layer_text_init((__TNSQ_GFX_LAYER_TEXT_CFG_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_gfx_layer_text_t *__tnsq_gfx_layer_text_init(tnsq_gfx_layer_text_cfg_t *ptLayerCFG, tnsq_gfx_layer_text_t *ptLayer);

int tnsq_gfx_layer_text_printf(tnsq_gfx_layer_text_t *ptLayer, const char *format, ...);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
