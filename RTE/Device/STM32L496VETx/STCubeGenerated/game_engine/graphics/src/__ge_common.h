/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____GE_COMMON_H__
#define ____GE_COMMON_H__

#include "arm_2d.h"

#include "arm_2d_helper_scene.h"

#include "ge_graphics.h"

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

/* OOC header, please DO NOT modify */
#ifdef __GE_STAGE_IMPLEMENT__
#   undef __GE_SCENE_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

//struct ge_stage_t
//{
//    ARM_PRIVATE(
//        implement(arm_2d_scene_t);
//        rt_bool_t blsUserAllocated;
//    )
//    ge_layer_t *ptLayer;
//};
//typedef struct ge_stage_t ge_stage_t;

#define ge_stage_init(...)  __ge_stage_init((NULL, ##__VA_ARGS__))

ge_stage_t *__ge_stage_init(ge_stage_t *ptStage);


#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif