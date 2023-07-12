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
    
static rt_err_t _gfx_init(ge_gfx_ctrl_t *ptThis)
{
    if (_gfx_refresh_sem_init(ptThis) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    this.chInitialState = RT_TRUE;
    return RT_EOK;
}
    
void ge_graphics_controller_entry(void *ptParam)
{
    ARM_2D_UNUSED(ptParam);
    ge_gfx_ctrl_t sGfxController = {0};
    ge_gfx_ctrl_t *ptThis = &sGfxController;
    
    this.chInitialState = RT_FALSE;
    
    while (_gfx_init(ptThis) != RT_EOK)
    {
        // todo:err handle
    }
    
    while(1)
    {
        
    }
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
