/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-30     AlgoOy     the first version
 */
 
#ifndef ____TNSQ_GFX_LAYER_NUM_H__
#define ____TNSQ_GFX_LAYER_NUM_H__
 
#ifdef   __cplusplus
extern "C" {
#endif

#include "tnsq_gfx_layer_num.h"

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

void tnsq_gfx_refresh_layer_num(tnsq_gfx_layer_num_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_region_list_item_t *ptDirtyRegion, rt_bool_t bIsNewFrame);

void tnsq_gfx_clear_layer_num_dirty_region(tnsq_gfx_layer_num_t *ptThis);

void tnsq_gfx_layer_num_evt_handle(tnsq_gfx_layer_num_t *ptThis);

void tnsq_gfx_layer_num_get_dirty_region(tnsq_gfx_layer_num_t *ptThis, arm_2d_scene_player_t *ptDispAdapter);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
