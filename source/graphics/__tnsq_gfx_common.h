/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____TNSQ_GFX_COMMON_H__
#define ____TNSQ_GFX_COMMON_H__

#include "tnsq_gfx.h"
#include "__tnsq_gfx_ctrl.h"
#include "__tnsq_gfx_layer.h"
#include "__tnsq_gfx_layer_cell.h"
#include "__tnsq_gfx_layer_user.h"
#include "__tnsq_gfx_layer_bg.h"
#include "__tnsq_gfx_layer_bg_cl.h"
#include "__tnsq_gfx_layer_text.h"
#include "__tnsq_gfx_layer_menu.h"
#include "__tnsq_gfx_layer_num.h"

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

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
