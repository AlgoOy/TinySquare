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

#include "tnsq_evt_key.h"

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

typedef struct tnsq_evt_ctrl_t tnsq_evt_ctrl_t;

struct tnsq_evt_ctrl_t
{
    ARM_PRIVATE
    (
        struct
        {
            rt_mq_t ptMsgI2E;
            rt_mq_t ptMsgE2G;
        } tEvtITC;
        struct
        {
            rt_bool_t chGet;
            rt_bool_t chPut;
        } tEvtLock;
    )
};

tnsq_evt_ctrl_t *tnsq_evt_get_ctrl(void);

rt_err_t tnsq_evt_ctrl_init(tnsq_evt_ctrl_t *ptThis);

rt_err_t tnsq_evt_itc_key_handler(void);

void tnsq_evt_get_lock(tnsq_evt_ctrl_t *ptThis);
void tnsq_evt_get_unlock(tnsq_evt_ctrl_t *ptThis);
void tnsq_evt_put_lock(tnsq_evt_ctrl_t *ptThis);
void tnsq_evt_put_unlock(tnsq_evt_ctrl_t *ptThis);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
