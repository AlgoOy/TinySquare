/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____TNSQ_GFX_CTRL_H__
#define ____TNSQ_GFX_CTRL_H__

#include "rtthread.h"

#include "arm_2d.h"

#include "tnsq_gfx_stage.h"

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

#ifdef ____TNSQ_GFX_CTRL_IMPLEMENT__
#   undef ____TNSQ_GFX_CTRL_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

struct tnsq_gfx_disp_adapters_node_t
{
    ARM_PRIVATE
    (
        struct tnsq_gfx_disp_adapters_node_t *ptNext;
        tnsq_gfx_disp_adapter_t tDispAdapter;
    )
};
typedef struct tnsq_gfx_disp_adapters_node_t tnsq_gfx_disp_adapters_node_t;

struct tnsq_gfx_ctrl_t
{
    ARM_PRIVATE
    (
        struct
        {
            rt_sem_t ptSemWaitReq;
            rt_sem_t ptSemGiveRsp;
        } tRefresh;
        tnsq_gfx_disp_adapters_node_t *ptDispAdapterList;
    )
};
typedef struct tnsq_gfx_ctrl_t tnsq_gfx_ctrl_t;

/* Get a pointer to the globally unique gfx_ctrl, return a pointer to gfx_ctrl */
tnsq_gfx_ctrl_t *tnsq_gfx_get_ctrl(void);
/* Initialize gfx_ctrl, return RT_EOK if sucessful, and return RT_ERROR if failed */
rt_err_t tnsq_gfx_ctrl_init(tnsq_gfx_ctrl_t *ptThis);
/* Get pointers to display adapters list, return display adapters list */
tnsq_gfx_disp_adapters_node_t const *tnsq_gfx_get_disp_adapters_list(tnsq_gfx_ctrl_t const *ptThis);
/* Register the display adapter in the display adapters list, 
 * return RT_EOK if successful or the display adapter already exists, and return RT_ERROR if failed */
rt_err_t tnsq_gfx_register_disp_adapter_to_crtl(tnsq_gfx_ctrl_t *ptThis, tnsq_gfx_disp_adapter_t const *ptDispAdapter);
/* destroy display adapters list */
void tnsq_gfx_destroy_disp_adapters_list(tnsq_gfx_ctrl_t *ptThis);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
