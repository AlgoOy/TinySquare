/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-11     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_LAYER_MENU_H__
#define __TNSQ_GFX_LAYER_MENU_H__
 
#ifdef   __cplusplus
extern "C" {
#endif

#include "__tnsq_gfx_layer.h"

#include "list_view.h"

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

#ifdef __TNSQ_GFX_LAYER_MENU_IMPLEMENT__
#   undef __TNSQ_GFX_LAYER_MENU_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

typedef struct tnsq_gfx_layer_menu_t tnsq_gfx_layer_menu_t;
typedef struct tnsq_gfx_layer_menu_cfg_t tnsq_gfx_layer_menu_cfg_t;

struct tItemFormat
{
    struct
    {
        COLOUR_INT box;
        COLOUR_INT font;
    } tColor;
    rt_uint8_t chOpacity;
};

struct tnsq_gfx_layer_menu_cfg_t
{
    struct
    {
        rt_uint8_t chItemsNum;
        char **pchItems;
        arm_2d_size_t tItemSize;
        struct
        {
            uint8_t pre;
            uint8_t next;
        } tItemPadding;
        rt_uint8_t chShowItemNum;
        rt_int32_t nFinishInMs;
    } tItemGeneral;
    
    struct tItemFormat tItemNormal;
    
    struct tItemFormat tItemSelected;
};

struct tnsq_gfx_layer_menu_t
{
    ARM_PRIVATE
    (
        implement (tnsq_gfx_layer_base_t);
        rt_bool_t blsUserAllocated;
        list_view_t tListView;
        arm_2d_size_t tItemSize;
        arm_2d_region_t tDirtyRegion;
        rt_int32_t nFinishInMs;
        rt_int8_t chSelectedIdx;
        char *pchSelectedStr;
    )
};

#define tnsq_gfx_layer_menu_init(__TNSQ_GFX_LAYER_MENU_CFG_PTR, ...) \
            __tnsq_gfx_layer_menu_init((__TNSQ_GFX_LAYER_MENU_CFG_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_gfx_layer_menu_t *__tnsq_gfx_layer_menu_init(tnsq_gfx_layer_menu_cfg_t *ptLayerCFG, tnsq_gfx_layer_menu_t *ptLayer);

char *tnsq_gfx_layer_menu_get_item_name(tnsq_gfx_layer_menu_t *ptLayer);

rt_int8_t tnsq_gfx_layer_menu_get_item_idx(tnsq_gfx_layer_menu_t *ptLayer);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
