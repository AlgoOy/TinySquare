/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#define __TNSQ_COMMON_IMPLEMENT__
#include "__tnsq_common.h"
 
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
    
static tnsq_gfx_ctrl_t sGfxController = {0};

tnsq_gfx_ctrl_t *tnsq_get_gfx_controller(void)
{
    return &sGfxController;
}

static rt_err_t _tnsq_gfx_controller_refresh_sem_init(tnsq_gfx_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    if (this.tRefresh.ptSemWaitReq != RT_NULL)
    {
        this.tRefresh.ptSemWaitReq = rt_sem_create("tnsqWaitReq", 0, RT_IPC_FLAG_FIFO);
        if (this.tRefresh.ptSemWaitReq == RT_NULL)
        {
            return RT_ERROR;
        }
    }
    
    if (this.tRefresh.ptSemGiveRsp != RT_NULL)
    {
        this.tRefresh.ptSemGiveRsp = rt_sem_create("tnsqGiveRsp", 0, RT_IPC_FLAG_FIFO);
        if (this.tRefresh.ptSemGiveRsp == RT_NULL)
        {
            return RT_ERROR;
        }
    }
    
    return RT_EOK;
}

static void _tnsq_gfx_controller_disp_list_init(tnsq_gfx_ctrl_t *ptThis)
{
    this.ptDispList = NULL;
}
    
rt_err_t tnsq_init(void)
{
    tnsq_gfx_ctrl_t *ptThis = &sGfxController;
    memset(ptThis, 0, sizeof(tnsq_gfx_ctrl_t));
    
    if (_tnsq_gfx_controller_refresh_sem_init(ptThis) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    _tnsq_gfx_controller_disp_list_init(ptThis);
    
    return RT_EOK;
}
    
//ge_fsm_rt_t get_ge_initial_state()
//{
//    static ge_fsm_rt_t sGeInitialState = ge_fsm_rt_on_start;
//    
//    switch (sGeInitialState)
//    {
//    case ge_fsm_rt_on_start:
//        return ge_fsm_rt_on_start;
//    case ge_fsm_rt_on_going:
//        return ge_fsm_rt_on_going;
//    case ge_fsm_rt_on_cpl:
//        return ge_fsm_rt_on_cpl;
//    }
//}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
