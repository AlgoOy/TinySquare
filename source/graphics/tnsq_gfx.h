/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_H__
#define __TNSQ_GFX_H__

#ifdef   __cplusplus
extern "C" {
#endif

#include "tnsq_gfx_stage.h"
#include "tnsq_gfx_utils.h"
#include "tnsq_gfx_layer_cell.h"
#include "tnsq_gfx_layer_user.h"
#include "tnsq_gfx_layer_bg.h"
#include "tnsq_gfx_layer_bg_cl.h"
#include "tnsq_gfx_layer_text.h"
#include "tnsq_gfx_layer_menu.h"
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

void tnsq_gfx_task_entry(void *ptParam);
void tnsq_gfx_apply_for_refresh(void);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif
 