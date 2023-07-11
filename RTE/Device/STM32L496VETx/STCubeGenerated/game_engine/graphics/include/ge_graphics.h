/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __GE_GRAPHICS_H__
#define __GE_GRAPHICS_H__

#ifdef   __cplusplus
extern "C" {
#endif

#include "ge_stage.h"

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

struct ge_display_adapter_t
{
    arm_2d_scene_player_t *ptPlayer;
    arm_fsm_rt_t (*ptPlayerTask)(void);
};
typedef struct ge_display_adapter_t ge_display_adapter_t;

#define ge_stage_init(__GE_PLAYER_PTR, ...) __ge_stage_init((__GE_PLAYER_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) ge_stage_t *__ge_stage_init(ge_display_adapter_t *ptDispAdapter, ge_stage_t *ptStage);

void ge_graphics_controller_entry(void *ptParam);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
 #endif
 