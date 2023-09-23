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
#include "__tnsq_gfx_ctrl.h"
 
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
    
static tnsq_gfx_ctrl_t s_tGfxController = {0};

/**
 * @brief The function will get the graphics controller.
 * @param none
 * @return Return the graphics controller.
*/
tnsq_gfx_ctrl_t *tnsq_gfx_get_ctrl(void)
{
    return &s_tGfxController;
}

/**
 * @brief The function will query the display adapter.
 * @param ptThis is a pointer to the graphics controller.
 * @param ptDispAdapter is a pointer to the display adapter.
 * @return Return the operation status. When the return value is RT_EOK, the display adapter is found.
 *         If the return value is RT_ERROR, it represents the display adapter is not found.
*/
static rt_err_t _tnsq_gfx_query_disp_adapter(tnsq_gfx_ctrl_t const *ptThis, tnsq_gfx_disp_adapter_t const *ptDispAdapter)
{
    assert(ptThis != NULL);
    assert(ptDispAdapter != NULL);
    
    tnsq_gfx_disp_adapters_node_t *ptDispAdapterListPtr = this.ptDispAdapterList;
    while (ptDispAdapterListPtr != NULL)
    {
        if (ptDispAdapterListPtr->tDispAdapter.ptPlayer == ptDispAdapter->ptPlayer)
        {
            return RT_EOK;
        }
        ptDispAdapterListPtr = ptDispAdapterListPtr->ptNext;
    }
    return RT_ERROR;
}

/**
 * @brief The function will add the specified display adapter to the end of the display adapters list.
 * @param ptThis is a pointer to the graphics controller.
 * @param ptDispAdapter is a pointer to the display adapter.
 * @return Return the operation status. When the return value is RT_EOK, the display adapter is added.
 *         If the return value is RT_ENOMEM, it represents the display adapter is not added.
*/
static rt_err_t _tnsq_gfx_set_disp_adapter(tnsq_gfx_ctrl_t *ptThis, tnsq_gfx_disp_adapter_t const *ptDispAdapter)
{
    assert(ptThis != NULL);
    assert(ptDispAdapter != NULL);
    
    tnsq_gfx_disp_adapters_node_t *ptNewDispNode = (tnsq_gfx_disp_adapters_node_t *)malloc(sizeof(tnsq_gfx_disp_adapters_node_t));
    if (ptNewDispNode == NULL)
    {
        return RT_ENOMEM;
    }
    
    memset(ptNewDispNode, 0, sizeof(tnsq_gfx_disp_adapters_node_t));
    
    ptNewDispNode->tDispAdapter = *ptDispAdapter;
    ptNewDispNode->ptNext = NULL;
    
    tnsq_gfx_disp_adapters_node_t *ptDispAdapterListPtr = this.ptDispAdapterList;
    if (ptDispAdapterListPtr == NULL)
    {
        this.ptDispAdapterList = ptNewDispNode;
    }
    else
    {
        while (ptDispAdapterListPtr->ptNext != NULL)
        {
            ptDispAdapterListPtr = ptDispAdapterListPtr->ptNext;
        }
        ptDispAdapterListPtr->ptNext = ptNewDispNode;
    }
    return RT_EOK;
}
    
/**
 * @brief The function will get the display adapters list.
 * @param ptThis is a pointer to the graphics controller.
 * @return Return the display adapters list.
*/
tnsq_gfx_disp_adapters_node_t const *tnsq_gfx_get_disp_adapters_list(tnsq_gfx_ctrl_t const *ptThis)
{
    assert(ptThis != NULL);
    return this.ptDispAdapterList;
}

/**
 * @brief The function will register the display adapter to the graphics controller.
 * @param ptThis is a pointer to the graphics controller.
 * @param ptDispAdapter is a pointer to the display adapter.
 * @return Return the operation status. When the return value is RT_EOK, the display adapter is registered.
 *         If the return value is RT_ERROR, it represents the display adapter is not registered.
*/
rt_err_t tnsq_gfx_register_disp_adapter_to_crtl(tnsq_gfx_ctrl_t *ptThis, tnsq_gfx_disp_adapter_t const *ptDispAdapter)
{
    assert(ptThis != NULL);
    assert(ptDispAdapter != NULL);
    
    if (_tnsq_gfx_query_disp_adapter(ptThis, ptDispAdapter) == RT_ERROR)
    {
        if (_tnsq_gfx_set_disp_adapter(ptThis, ptDispAdapter) == RT_ERROR)
        {
            return RT_ERROR;
        }
    }
    
    return RT_EOK;
}

/**
 * @brief The function will destroy the display adapters list.
 * @param ptThis is a pointer to the graphics controller.
 * @return none
*/
void tnsq_gfx_destroy_disp_adapters_list(tnsq_gfx_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    tnsq_gfx_disp_adapters_node_t *ptDispAdapterListPtr = this.ptDispAdapterList;
    while (ptDispAdapterListPtr != NULL)
    {
        tnsq_gfx_disp_adapters_node_t *ptDispAdapterListPtrNext = ptDispAdapterListPtr->ptNext;
        free(ptDispAdapterListPtr);
        ptDispAdapterListPtr = ptDispAdapterListPtrNext;
    }
}

/**
 * @brief The function will initialize the semaphore for refresh.
 * @param ptThis is a pointer to the graphics controller.
 * @return Return the operation status. When the return value is RT_EOK, the semaphore is initialized.
 *         If the return value is RT_ERROR, it represents the semaphore is not initialized.
*/
static rt_err_t _tnsq_gfx_ctrl_refresh_sem_init(tnsq_gfx_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    this.tRefresh.ptSemWaitReq = rt_sem_create("tnsqWaitReq", 0, RT_IPC_FLAG_FIFO);
    if (this.tRefresh.ptSemWaitReq == RT_NULL)
    {
        return RT_ERROR;
    }

    this.tRefresh.ptSemGiveRsp = rt_sem_create("tnsqGiveRsp", 0, RT_IPC_FLAG_FIFO);
    if (this.tRefresh.ptSemGiveRsp == RT_NULL)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}
    
/**
 * @brief The function will initialize the graphics controller.
 * @param ptThis is a pointer to the graphics controller.
 * @return Return the operation status. When the return value is RT_EOK, the initialization is successful.
 *         If the return value is RT_ERROR, it represents the initialization failed.
*/
rt_err_t tnsq_gfx_ctrl_init(tnsq_gfx_ctrl_t *ptThis)
{
    assert(ptThis != NULL);
    
    memset(ptThis, 0, sizeof(tnsq_gfx_ctrl_t));
    
    *ptThis = (tnsq_gfx_ctrl_t) {
        .ptDispAdapterList = NULL,
        .tRefresh = {
            .ptSemGiveRsp = NULL,
            .ptSemWaitReq = NULL,
        },
    };
    
    if (_tnsq_gfx_ctrl_refresh_sem_init(ptThis) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
