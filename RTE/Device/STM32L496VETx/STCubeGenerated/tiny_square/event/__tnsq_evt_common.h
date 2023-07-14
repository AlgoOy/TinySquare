/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____TNSQ_EVT_COMMON_H__
#define ____TNSQ_EVT_COMMON_H__

#include "rtthread.h"

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

#ifdef ____TNSQ_EVT_COMMON_IMPLEMENT__
#   undef ____TNSQ_EVT_COMMON_IMPLEMENT__
#   define __ARM_2D_IMPL__
#endif
#include "arm_2d_utils.h"

struct tnsq_evt_ctrl_t
{
    ARM_PRIVATE
    (
        rt_mailbox_t ptEvtGetMail;
        rt_mailbox_t ptEvtPutMail;
    )
};
typedef struct tnsq_evt_ctrl_t tnsq_evt_ctrl_t;

tnsq_evt_ctrl_t *tnsq_evt_get_ctrl(void);

rt_err_t tnsq_evt_ctrl_init(tnsq_evt_ctrl_t *ptThis);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
