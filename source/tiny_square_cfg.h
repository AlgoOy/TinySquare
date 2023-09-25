/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef __TINY_SQUARE_CFG_H__
#define __TINY_SQUARE_CFG_H__

#include "../port/tiny_square_user_cfg.h"

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

#ifndef TNSQ_EVT_ITC_NUM
    #define TNSQ_EVT_ITC_NUM            64
#endif

#ifndef TNSQ_GFX_THREAD_STACK_SIZE
    #define TNSQ_GFX_THREAD_STACK_SIZE  4096
#endif

#ifndef TNSQ_GFX_THREAD_PRIORITY
    #define TNSQ_GFX_THREAD_PRIORITY    25
#endif

#ifndef TNSQ_GFX_THREAD_TIMESLICE
    #define TNSQ_GFX_THREAD_TIMESLICE   10
#endif

#ifndef TNSQ_EVT_THREAD_STACK_SIZE
    #define TNSQ_EVT_THREAD_STACK_SIZE  1024
#endif

#ifndef TNSQ_EVT_THREAD_PRIORITY
    #define TNSQ_EVT_THREAD_PRIORITY    24
#endif

#ifndef TNSQ_EVT_THREAD_TIMESLICE
    #define TNSQ_EVT_THREAD_TIMESLICE   10
#endif

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif