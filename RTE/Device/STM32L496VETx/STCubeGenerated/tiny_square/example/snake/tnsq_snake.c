/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#include "tnsq_snake.h"
#include "tnsq_evt.h"
#include "uart.h"
 
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
    
void tnsq_snake_task_entry(void *ptParam)
{
    tnsq_evt_key_t tEvtKey = {0};
    while (1)
    {
        tnsq_evt_itc_get(&tEvtKey, RT_WAITING_FOREVER);
        switch (tEvtKey.tEvent) 
        {
        case tnsq_evt_key_down:
            UART_Print("key down\n");
            break;
        case tnsq_evt_key_up:
            UART_Print("key up\n");
            break;
        case tnsq_evt_key_pressed:
            UART_Print("key pressed\n");
            break;
        case tnsq_evt_key_long_pressed:
            UART_Print("key long pressed\n");
            break;
        default:
            break;
        }
    }
    
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
