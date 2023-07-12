/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __TNSQ_STAGE_H__
#define __TNSQ_STAGE_H__

#ifdef   __cplusplus
extern "C" {
#endif

#include "rtdef.h"

#include "arm_2d_helper_scene.h"

#include "tnsq_layer.h"

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

#ifdef __TNSQ_STAGE_IMPLEMENT__
#   undef __TNSQ_STAGE_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

struct tnsq_display_adapter_t
{
    arm_2d_scene_player_t *ptPlayer;
    arm_fsm_rt_t (*ptPlayerTask)(void);
};
typedef struct tnsq_display_adapter_t tnsq_display_adapter_t;

struct tnsq_stage_cfg_t
{
    tnsq_display_adapter_t ptDispAdapter;
};
typedef struct tnsq_stage_cfg_t tnsq_stage_cfg_t;

struct tnsq_stage_t
{
    ARM_PRIVATE
	(
        implement(arm_2d_scene_t);
        tnsq_stage_cfg_t tStageCFG;
        rt_bool_t blsUserAllocated;
    )
    tnsq_layer_t *ptLayer;
};
typedef struct tnsq_stage_t tnsq_stage_t;

#define tnsq_stage_init(__TNSQ_DISP_ADAPTER_PTR, ...) __tnsq_stage_init((__TNSQ_DISP_ADAPTER_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_stage_t *__tnsq_stage_init(tnsq_stage_cfg_t *ptStageCFG, tnsq_stage_t *ptStage);

#define tnsq_layer_register(__TNSQ_STAGE_PTR, ...) __tnsq_layer_register((__TNSQ_STAGE_PTR), (NULL, ##__VA_ARGS__))

ARM_NONNULL(1) tnsq_layer_t *__tnsq_layer_register(tnsq_stage_t *ptStage, tnsq_layer_t *ptLayer);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
