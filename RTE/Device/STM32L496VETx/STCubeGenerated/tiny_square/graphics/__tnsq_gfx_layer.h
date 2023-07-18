/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____TNSQ_GFX_LAYER_H__
#define ____TNSQ_GFX_LAYER_H__

#ifdef   __cplusplus
extern "C" {
#endif

#include "rtdef.h"

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

#define TNSQ_GFX_LAYER_BASE_MAGIC   0xA0B9C8D7

struct tnsq_gfx_layer_base_t
{
    struct tnsq_gfx_layer_base_t *ptNext;
    enum
    {
        TNSQ_GFX_LAYER_TYPE_INVALID     = 0x00,
        TNSQ_GFX_LAYER_TYPE_CELL        = 0x01,
        TNSQ_GFX_LAYER_TYPE_USER        = 0x02,
    } tType;
    rt_int32_t wMagic;
};
typedef struct tnsq_gfx_layer_base_t tnsq_gfx_layer_base_t;

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
