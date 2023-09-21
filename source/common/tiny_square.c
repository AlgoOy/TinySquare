/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#include "tiny_square.h"
#include "tiny_square_cfg.h"
 
#include "__tnsq_gfx_common.h"
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
    
rt_err_t tnsq_init(void)
{
    if (tnsq_gfx_ctrl_init(tnsq_gfx_get_ctrl()) == RT_ERROR)
    {
        return RT_ERROR;
    }
    
    if (tnsq_evt_ctrl_init(tnsq_evt_get_ctrl()) == RT_ERROR)
    {
        return RT_ERROR;
    }
	
	
	rt_thread_t engineTid = RT_NULL, eventTid = RT_NULL;
	
    /* todo: put task create into tnsq init */
	engineTid = rt_thread_create("tnsq_gfx", tnsq_gfx_task_entry, RT_NULL, TNSQ_GFX_THREAD_STACK_SIZE, TNSQ_GFX_THREAD_PRIORITY, TNSQ_GFX_THREAD_TIMESLICE);
	if (engineTid != RT_NULL)
    {
		rt_thread_startup(engineTid);
	}
    else
    {
        return RT_ERROR;
    }    

	
	eventTid = rt_thread_create("tnsq_evt", tnsq_evt_task_entry, RT_NULL, TNSQ_EVT_THREAD_STACK_SIZE, TNSQ_EVT_THREAD_PRIORITY, TNSQ_EVT_THREAD_TIMESLICE);
	if (eventTid != RT_NULL)
    {
		rt_thread_startup(eventTid);
	}
    else
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
