/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-30     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_LAYER_NUM_H__
#define __TNSQ_GFX_LAYER_NUM_H__

#include "__tnsq_gfx_layer.h"

#include "number_list.h"
 
#ifdef   __cplusplus
extern "C" {
#endif

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

#ifdef __TNSQ_GFX_LAYER_NUM_IMPLEMENT__
#   undef __TNSQ_GFX_LAYER_NUM_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

typedef struct tnsq_gfx_layer_num_t tnsq_gfx_layer_num_t;
typedef struct tnsq_gfx_layer_num_cfg_t tnsq_gfx_layer_num_cfg_t;

struct tnsq_gfx_layer_num_cfg_t
{
    rt_uint8_t chNum;
    rt_int32_t nFinishInMs;
    rt_uint8_t chShowItemNum;
    struct
    {
        COLOUR_INT font;
        COLOUR_INT background;
    } tColor;
    struct
    {
        uint8_t pre;
        uint8_t next;
    } tPadding;
    arm_2d_font_t *ptFont;
};

struct tnsq_gfx_layer_num_t
{
    ARM_PRIVATE
    (
        implement (tnsq_gfx_layer_base_t);
        number_list_t tNumber;
        arm_2d_region_t tDirtyRegion;
        rt_int32_t nFinishInMs;
        rt_int8_t chSelectedNum;
    )
};

#define tnsq_gfx_layer_num_init(__TNSQ_GFX_LAYER_NUM_CFG_PTR, ...) \
            __tnsq_gfx_layer_num_init((__TNSQ_GFX_LAYER_NUM_CFG_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_gfx_layer_num_t *__tnsq_gfx_layer_num_init(tnsq_gfx_layer_num_cfg_t *ptLayerCFG, tnsq_gfx_layer_num_t *ptLayer);

rt_int8_t tnsq_gfx_layer_num_get_item_idx(tnsq_gfx_layer_num_t *ptLayer);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
