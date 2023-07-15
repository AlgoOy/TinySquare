/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef __TNSQ_EVT_KEY_H__
#define __TNSQ_EVT_KEY_H__

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

struct tnsq_evt_key_t
{
    rt_uint8_t chValue;
    enum{
        tnsq_evt_key_invalid        = 0x00,
        tnsq_evt_key_up             = 0x01,
        tnsq_evt_key_down           = 0x02,
        tnsq_evt_key_pressed        = 0x03,
        tnsq_evt_key_long_pressed   = 0x04,
    } tEvent;
};
typedef struct tnsq_evt_key_t tnsq_evt_key_t;

rt_err_t tnsq_evt_itc_get(tnsq_evt_key_t *ptThis, rt_int32_t timeout);
rt_err_t tnsq_evt_itc_put(tnsq_evt_key_t *ptThis);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
