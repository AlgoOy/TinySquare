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

typedef struct tnsq_evt_key_t tnsq_evt_key_t;
typedef enum tnsq_evt_key_value_t tnsq_evt_key_value_t;

enum tnsq_evt_key_value_t
{
	TNSQ_EVT_KEY_INVALID  = 0x00,
	TNSQ_EVT_KEY_UP       = 0x01,
	TNSQ_EVT_KEY_DOWN     = 0x02,
	TNSQ_EVT_KEY_LEFT     = 0x03,
	TNSQ_EVT_KEY_RIGHT    = 0x04,
	TNSQ_EVT_KEY_X		  = 0x05,
	TNSQ_EVT_KEY_Y		  = 0x06,
	TNSQ_EVT_KEY_A		  = 0x07,
	TNSQ_EVT_KEY_B		  = 0x08,
};

struct tnsq_evt_key_t
{
    tnsq_evt_key_value_t tKeyValue;
    enum 
    {
        TNSQ_EVT_KEY_EVENT_INVALID        = 0x00,
        TNSQ_EVT_KEY_EVENT_UP             = 0x01,
        TNSQ_EVT_KEY_EVENT_DOWN           = 0x02,
        TNSQ_EVT_KEY_EVENT_PRESSED        = 0x03,
        TNSQ_EVT_KEY_EVENT_LONG_PRESSED   = 0x04,
    } tEvent;
};

rt_err_t tnsq_evt_itc_get(tnsq_evt_key_t *ptKey, rt_int32_t timeout);
rt_err_t tnsq_evt_itc_put(tnsq_evt_key_t *ptKey);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
