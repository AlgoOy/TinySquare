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

#include "rtthread.h"

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

#ifdef __GE_COMMON_IMPLEMENT__
#   undef __GE_COMMON_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

enum ge_fsm_rt_t
{
    ge_fsm_rt_on_start = 0x00,
    ge_fsm_rt_on_going = 0x01,
    ge_fsm_rt_on_cpl = 0x02,
};
typedef enum ge_fsm_rt_t ge_fsm_rt_t;

struct _ge_player_t
{
    struct _ge_player_t *ptNext;
    ge_display_adapter_t *ptDispAdapter;
};

struct ge_gfx_ctrl_t
{
    ARM_PRIVATE
    (
        rt_uint8_t chInitialState;
        struct
        {
            rt_sem_t ptSemWaitReq;
            rt_sem_t ptSemGiveRsp;
        } tRefresh;
        struct _ge_player_t ptDispList;
    )
};
typedef struct ge_gfx_ctrl_t ge_gfx_ctrl_t;

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
