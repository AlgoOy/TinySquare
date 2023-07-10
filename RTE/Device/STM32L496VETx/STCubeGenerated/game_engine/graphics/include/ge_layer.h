/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __GE_LAYER_H__
#define __GE_LAYER_H__
 
#ifdef   __cplusplus
extern "C" {
#endif

#include "rtdef.h"

#include "ge_color.h"

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

#ifdef __GE_LAYER_IMPLEMENT__
#   undef __GE_LAYER_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

struct ge_cell_t
{
    ge_color_t tColor;
    rt_uint8_t chOpacity;
    rt_bool_t blsDirty;
};
typedef struct ge_cell_t ge_cell_t;
 
struct ge_layer_t
{
    ARM_PRIVATE(
        rt_bool_t blsUserAllocated;
    )
    rt_uint16_t hwXCount;
    rt_uint16_t hwYCount;
    ge_cell_t *ptCells;
};
typedef struct ge_layer_t ge_layer_t;

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif