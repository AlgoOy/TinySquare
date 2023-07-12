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
    
tnsq_disp_adapters_list_t const *tnsq_get_disp_adapters_list(tnsq_gfx_ctrl_t const *ptThis)
{
    assert(ptThis != NULL);
    return this.ptDispList;
}

rt_err_t tnsq_query_disp_adapter(tnsq_gfx_ctrl_t const *ptThis, tnsq_display_adapter_t const *ptDispAdapter)
{
    assert(ptThis != NULL);
    assert(ptDispAdapter != NULL);
    
    tnsq_disp_adapters_list_t *ptDispListPtr = this.ptDispList;
    while (ptDispListPtr != NULL)
    {
        if (ptDispListPtr->ptDispAdapter.ptPlayer == ptDispAdapter->ptPlayer)
        {
            return RT_ERROR;
        }
        ptDispListPtr = ptDispListPtr->ptNext;
    }
    return RT_EOK;
}

rt_err_t tnsq_set_disp_adapter(tnsq_gfx_ctrl_t *ptThis, tnsq_display_adapter_t const *ptDispAdapter)
{
    assert(ptThis != NULL);
    assert(ptDispAdapter != NULL);
    
    tnsq_disp_adapters_list_t *ptNewDispList = (tnsq_disp_adapters_list_t *)malloc(sizeof(tnsq_disp_adapters_list_t));
    if (ptNewDispList == NULL)
    {
        return RT_ENOMEM;
    }
    
    memset(ptNewDispList, 0, sizeof(tnsq_disp_adapters_list_t));
    
    ptNewDispList->ptDispAdapter = *ptDispAdapter;
    ptNewDispList->ptNext = NULL;
    
    tnsq_disp_adapters_list_t *ptDispListPtr = this.ptDispList;
    if (ptDispListPtr == NULL)
    {
        this.ptDispList = ptNewDispList;
    }
    else
    {
        while (ptDispListPtr->ptNext != NULL)
        {
            ptDispListPtr = ptDispListPtr->ptNext;
        }
        ptDispListPtr->ptNext = ptNewDispList;
    }
    return RT_EOK;
}

void tnsq_destroy_disp_adapter(tnsq_gfx_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    tnsq_disp_adapters_list_t *ptDispListPtr = this.ptDispList;
    while (ptDispListPtr != NULL)
    {
        tnsq_disp_adapters_list_t *ptDispListPtrNext = ptDispListPtr->ptNext;
        free(ptDispListPtr);
        ptDispListPtr = ptDispListPtrNext;
    }
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif