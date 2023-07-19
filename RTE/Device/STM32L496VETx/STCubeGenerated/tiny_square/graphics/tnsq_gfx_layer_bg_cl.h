/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_LAYER_BG_CL_H__
#define __TNSQ_GFX_LAYER_BG_CL_H__
 
#ifdef   __cplusplus
extern "C" {
#endif

#include "rtdef.h"

#include "arm_2d.h"

#include "arm_2d_helper.h"

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

#ifdef __TNSQ_GFX_LAYER_BG_CL_IMPLEMENT__
#   undef __TNSQ_GFX_LAYER_BG_CL_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

struct tnsq_gfx_layer_bg_cl_cfg_t
{
    __arm_2d_color_t tColor;
    rt_uint8_t chOpacity;
    arm_2d_tile_t *ptBackGroundColorMask;
    arm_2d_region_t *ptRegion;
};
typedef struct tnsq_gfx_layer_bg_cl_cfg_t tnsq_gfx_layer_bg_cl_cfg_t;

struct tnsq_gfx_layer_bg_cl_t
{
    ARM_PRIVATE
    (
        implement (tnsq_gfx_layer_base_t);
        rt_bool_t blsUserAllocated;
        tnsq_gfx_layer_bg_cl_cfg_t tCFG;
    )
};
typedef struct tnsq_gfx_layer_bg_cl_t tnsq_gfx_layer_bg_cl_t;

#define tnsq_gfx_layer_bg_cl_init(__TNSQ_GFX_LAYER_BG_CL_CFG_PTR, ...) \
            __tnsq_gfx_layer_bg_cl_init((__TNSQ_GFX_LAYER_BG_CL_CFG_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_gfx_layer_bg_cl_t *__tnsq_gfx_layer_bg_cl_init(tnsq_gfx_layer_bg_cl_cfg_t *ptLayerCFG, tnsq_gfx_layer_bg_cl_t *ptLayer);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
