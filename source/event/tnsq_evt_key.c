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

#include "tnsq_evt_key.h"

#define TNSQ_EVT_LONG_PRESSED_JUDEG_TIME  2000
 
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
 * @brief The function will get the key event.
 * @param ptThis is a pointer to the key struct.
 * @param ptMq is a pointer to the message queue.
 * @param timeout is the timeout value.
 * @return Return the operation status. When the return value is RT_EOK, the operation is successful.
 *         If the return value is -RT_ERROR, it represents the operation failed.
 *         If the return value is -RT_ETIMEOUT, it represents the operation timeout.
*/
static rt_err_t _tnsq_evt_key_get(tnsq_evt_key_t *ptThis, rt_mq_t ptMq, rt_int32_t timeout)
{
    return rt_mq_recv(ptMq, ptThis, sizeof(tnsq_evt_key_t), timeout);
}

/**
 * @brief The function will put the key event.
 * @param ptThis is a pointer to the key struct.
 * @param ptMq is a pointer to the message queue.
 * @return Return the operation status. When the return value is RT_EOK, the operation is successful.
 *         If the return value is -RT_ERROR, it represents the operation failed.
 *         If the return value is -RT_EFULL, it represents the message queue is full.
*/
static rt_err_t _tnsq_evt_key_put(tnsq_evt_key_t *ptThis, rt_mq_t ptMq)
{
    return rt_mq_send(ptMq, ptThis, sizeof(tnsq_evt_key_t));
}

/**
 * @brief The function will put the event to the message queue.
 * @param ptThis is a pointer to the key struct.
 * @return Return the operation status. When the return value is RT_EOK, the operation is successful.
 *         If the return value is -RT_ERROR, it represents the operation failed.
 *         If the return value is -RT_EFULL, it represents the message queue is full.
*/
rt_err_t tnsq_evt_itc_put(tnsq_evt_key_t *ptThis)
{
    tnsq_evt_ctrl_t *ptEvtCtrl = tnsq_evt_get_ctrl();
    
    if (ptEvtCtrl->tEvtLock.chPut)
    {
        return rt_mq_send(ptEvtCtrl->tEvtITC.ptMsgI2E, ptThis, sizeof(tnsq_evt_key_t));
    }
    else
    {
        return -RT_ERROR;
    }
}

/**
 * @brief The function will get the event from the message queue.
 * @param ptThis is a pointer to the key struct.
 * @param timeout is the timeout value.
 * @return Return the operation status. When the return value is RT_EOK, the operation is successful.
 *         If the return value is -RT_ERROR, it represents the operation failed.
 *         If the return value is -RT_ETIMEOUT, it represents the operation timeout.
*/
rt_err_t tnsq_evt_itc_get(tnsq_evt_key_t *ptThis, rt_int32_t timeout)
{
    tnsq_evt_ctrl_t *ptEvtCtrl = tnsq_evt_get_ctrl();
    
    if (ptEvtCtrl->tEvtLock.chGet)
    {
        return rt_mq_recv(ptEvtCtrl->tEvtITC.ptMsgE2G, ptThis, sizeof(tnsq_evt_key_t), timeout);
    }
    else
    {
        return -RT_ERROR;
    }
}
    
/**
 * @brief The function will handle the key event.
 * @param none
 * @return Return the operation status. When the return value is RT_EOK, the operation is successful.
 *         If the return value is RT_ERROR, it represents the operation failed.
*/
rt_err_t tnsq_evt_itc_key_handler(void)
{
    static rt_bool_t s_blsfinsh = RT_TRUE, s_blsLongPressed = RT_FALSE;
    
    static tnsq_evt_key_t tEvtKey = {0};
    
    tnsq_evt_ctrl_t *ptEvtCtrl = tnsq_evt_get_ctrl();
    
    /* long pressed judge */
    rt_err_t tErr = _tnsq_evt_key_get(&tEvtKey, ptEvtCtrl->tEvtITC.ptMsgI2E, TNSQ_EVT_LONG_PRESSED_JUDEG_TIME);
    if (tErr == -RT_ERROR)
    {
        return RT_ERROR;
    }
    else if(tErr == -RT_ETIMEOUT)
    {
        if (s_blsfinsh == RT_FALSE && s_blsLongPressed == RT_FALSE)
        {
            s_blsLongPressed = RT_TRUE;
            tEvtKey.tEvent = TNSQ_EVT_KEY_EVENT_LONG_PRESSED;
            if (_tnsq_evt_key_put(&tEvtKey, ptEvtCtrl->tEvtITC.ptMsgE2G) != RT_EOK)
            {
                return RT_ERROR;
            }
        }
        if (_tnsq_evt_key_get(&tEvtKey, ptEvtCtrl->tEvtITC.ptMsgI2E, RT_WAITING_FOREVER) != RT_EOK)
        {
            return RT_ERROR;
        }
    }
    
    switch(tEvtKey.tEvent)
    {
    case TNSQ_EVT_KEY_EVENT_DOWN:
        if (s_blsfinsh == RT_FALSE)
        {
            return RT_ERROR;
        }
        else
        {
            if (_tnsq_evt_key_put(&tEvtKey, ptEvtCtrl->tEvtITC.ptMsgE2G) != RT_EOK)
            {
                return RT_ERROR;
            }
            s_blsfinsh = RT_FALSE;
        }
        break;
    case TNSQ_EVT_KEY_EVENT_UP:
        if (s_blsfinsh == RT_TRUE)
        {
            return RT_ERROR;
        }
        else
        {
            if (_tnsq_evt_key_put(&tEvtKey, ptEvtCtrl->tEvtITC.ptMsgE2G) != RT_EOK)
            {
                return RT_ERROR;
            }
            if (s_blsLongPressed == RT_FALSE)
            {
                tEvtKey.tEvent = TNSQ_EVT_KEY_EVENT_PRESSED;
                if (_tnsq_evt_key_put(&tEvtKey, ptEvtCtrl->tEvtITC.ptMsgE2G) != RT_EOK)
                {
                    return RT_ERROR;
                }
            }
            else
            {
                s_blsLongPressed = RT_FALSE;
            }
            s_blsfinsh = RT_TRUE;
        }
        break;
    case TNSQ_EVT_KEY_EVENT_LONG_PRESSED:
    case TNSQ_EVT_KEY_EVENT_PRESSED:
    default:
        return RT_ERROR;
    }
    
    return RT_EOK;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
