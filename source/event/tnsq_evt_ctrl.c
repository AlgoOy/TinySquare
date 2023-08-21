/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#define ____TNSQ_EVT_COMMON_IMPLEMENT__
#include "__tnsq_evt_common.h"
 
#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wunused-function"
#   pragma clang diagnostic ignored "-Wmissing-declarations"  
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_IAR__
#   pragma diag_suppress=Pa089,Pe188,Pe177,Pe174
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wunused-value"
#endif

#undef this
#define this (*ptThis)
    
static tnsq_evt_ctrl_t s_tEvtController = {0};

tnsq_evt_ctrl_t *tnsq_evt_get_ctrl(void)
{
    return &s_tEvtController;
}

static rt_err_t _tnsq_evt_ctrl_itc_init(tnsq_evt_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    this.tEvtITC.ptMsgI2E = rt_mq_create("tnsqEvtI2E", sizeof(tnsq_evt_key_t), TNSQ_EVT_ITC_NUM, RT_IPC_FLAG_FIFO);
    if (this.tEvtITC.ptMsgI2E == RT_NULL)
    {
        return RT_ERROR;
    }
    
    this.tEvtITC.ptMsgE2G = rt_mq_create("tnsqEvtE2G", sizeof(tnsq_evt_key_t), TNSQ_EVT_ITC_NUM, RT_IPC_FLAG_FIFO);
    if (this.tEvtITC.ptMsgE2G == RT_NULL)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}
    
rt_err_t tnsq_evt_ctrl_init(tnsq_evt_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    memset(ptThis, 0, sizeof(tnsq_evt_ctrl_t));
    
    if (_tnsq_evt_ctrl_itc_init(ptThis) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
