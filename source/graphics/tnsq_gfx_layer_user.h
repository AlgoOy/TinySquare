/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_LAYER_USER_H__
#define __TNSQ_GFX_LAYER_USER_H__

#include "rtdef.h"

#include "arm_2d_helper.h"

#include "__tnsq_gfx_layer.h"
 
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

#ifdef __TNSQ_GFX_LAYER_USER_IMPLEMENT__
#   undef __TNSQ_GFX_LAYER_USER_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

typedef struct tnsq_gfx_user_map_t tnsq_gfx_user_map_t;
typedef struct tnsq_gfx_layer_user_cfg_t tnsq_gfx_layer_user_cfg_t;
typedef struct tnsq_gfx_layer_user_t tnsq_gfx_layer_user_t;

typedef void (*ptLayerUserFunc_t)(rt_uint8_t idx, arm_2d_tile_t const *ptTile,const rt_bool_t  bIsNewFrame);

struct tnsq_gfx_user_map_t
{
    rt_uint8_t bIsDirty : 1;
    rt_uint8_t u7Idx    : 7;
};

struct tnsq_gfx_layer_user_cfg_t
{
    rt_uint16_t hwXCount;
    rt_uint16_t hwYCount;
    tnsq_gfx_user_map_t *pchUserMap;
    ptLayerUserFunc_t ptFunc;
};

struct tnsq_gfx_layer_user_t
{
    ARM_PRIVATE
    (
        implement (tnsq_gfx_layer_base_t);
        struct
        {
            rt_uint16_t hwXCount;
            rt_uint16_t hwYCount;
            rt_uint16_t totalCount;
        } tCount;
        struct
        {
            rt_uint8_t hwXPixel;
            rt_uint8_t hwYPixel;
        } tPixel;
        ptLayerUserFunc_t ptFunc;
    )
    tnsq_gfx_user_map_t *pchUserMap;
};

#define tnsq_gfx_layer_user_init(__TNSQ_GFX_LAYER_USER_CFG_PTR, ...) \
            __tnsq_gfx_layer_user_init((__TNSQ_GFX_LAYER_USER_CFG_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_gfx_layer_user_t *__tnsq_gfx_layer_user_init(tnsq_gfx_layer_user_cfg_t *ptLayerCFG, tnsq_gfx_layer_user_t *ptLayer);

void tnsq_gfx_layer_user_draw(tnsq_gfx_layer_user_t *ptLayer, rt_uint16_t iX, rt_uint16_t iY, rt_uint8_t u7Idx);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
