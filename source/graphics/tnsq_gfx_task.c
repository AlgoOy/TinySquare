/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#define ____TNSQ_GFX_CTRL_IMPLEMENT__
#include "__tnsq_gfx_common.h"

// todo: just for test
#include <stdio.h>
 
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
    
/**
 * @brief The function will apply to refresh the display.
 * @param none
 * @return none
*/
void tnsq_gfx_apply_for_refresh(void)
{
    tnsq_gfx_ctrl_t *ptThis = tnsq_gfx_get_ctrl();
    
    while (rt_sem_release(this.tRefresh.ptSemWaitReq) != RT_EOK)
    {
        /* error handle */
    }
    while (rt_sem_take(this.tRefresh.ptSemGiveRsp, RT_WAITING_FOREVER) != RT_EOK)
    {
        /* error handle */
    }
}
    
/**
 * @brief The function is the entry of the gfx task.
 * @param ptParam is a pointer to the parameter.
 * @return none
*/
void tnsq_gfx_task_entry(void *ptParam)
{
    (void)ptParam;
    
    tnsq_gfx_ctrl_t *ptThis = tnsq_gfx_get_ctrl();
    
    while (1)
    {
        while (rt_sem_take(this.tRefresh.ptSemWaitReq, RT_WAITING_FOREVER) != RT_EOK)
        {
            /* error handle */
        }
        /* todo: if there many disp adapters waiting for run
         * arm_2d_op_wait_async(disp_adapters_task());  ???
         */
        tnsq_gfx_disp_adapters_node_t *ptDispAdapterListPtr = this.ptDispAdapterList;
        while (ptDispAdapterListPtr != NULL)
        {
            while (ptDispAdapterListPtr->tDispAdapter.ptPlayerTask() != arm_fsm_rt_cpl)
            {
                /* waiting for task cpl */
            }
            ptDispAdapterListPtr = ptDispAdapterListPtr->ptNext;
        }
        
        while (rt_sem_release(this.tRefresh.ptSemGiveRsp) != RT_EOK)
        {
            /* error handle */
        }
    }
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
