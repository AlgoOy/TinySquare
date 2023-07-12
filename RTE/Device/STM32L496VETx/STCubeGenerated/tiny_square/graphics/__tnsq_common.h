/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____TNSQ_COMMON_H__
#define ____TNSQ_COMMON_H__

#include "rtthread.h"

#include "arm_2d.h"

#include "arm_2d_helper_scene.h"

#include "tnsq_graphics.h"
#include "tiny_square.h"

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

#ifdef __TNSQ_COMMON_IMPLEMENT__
#   undef __TNSQ_COMMON_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

//enum ge_fsm_rt_t
//{
//    ge_fsm_rt_on_start = 0x00,
//    ge_fsm_rt_on_going = 0x01,
//    ge_fsm_rt_on_cpl = 0x02,
//};
//typedef enum ge_fsm_rt_t ge_fsm_rt_t;

struct tnsq_disp_adapters_list_t
{
    struct tnsq_disp_adapters_list_t *ptNext;
    tnsq_display_adapter_t ptDispAdapter;
};
typedef struct tnsq_disp_adapters_list_t tnsq_disp_adapters_list_t;

struct tnsq_gfx_ctrl_t
{
    ARM_PRIVATE
    (
        struct
        {
            rt_sem_t ptSemWaitReq;
            rt_sem_t ptSemGiveRsp;
        } tRefresh;
        tnsq_disp_adapters_list_t *ptDispList;
        //rt_uint8_t chInitialState;
    )
};
typedef struct tnsq_gfx_ctrl_t tnsq_gfx_ctrl_t;

tnsq_gfx_ctrl_t *tnsq_get_gfx_controller(void);

/* get display adapters list */
tnsq_disp_adapters_list_t const *tnsq_get_disp_adapters_list(tnsq_gfx_ctrl_t const *ptThis);
/* Query whether the display adapter already exists, return RT_ERROR if it exists, and return RT_EOK if it does not exist */
rt_err_t tnsq_query_disp_adapter(tnsq_gfx_ctrl_t const *ptThis, tnsq_display_adapter_t const *ptDispAdapter);
/* To set the display adapter into the linked list, you must use tnsq_query_disp_adapter to ensure that the display adapter does not exist in the linked list */
rt_err_t tnsq_set_disp_adapter(tnsq_gfx_ctrl_t *ptThis, tnsq_display_adapter_t const *ptDispAdapter);
void tnsq_destroy_disp_adapter(tnsq_gfx_ctrl_t *ptThis);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
