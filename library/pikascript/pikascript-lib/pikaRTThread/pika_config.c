/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-07     lyon       the first version
 */

#include <rtthread.h>
#include "PikaPlatform.h"

#ifndef RT_USING_HEAP
#error "Please enable heap in the RT-Thread configuration"
#endif

int __platform_sprintf(char* buff, char* fmt, ...) {
    va_list args;
    int res;
    va_start(args, fmt);
    res = rt_vsprintf(buff, fmt, args);
    va_end(args);
    return res;
}
int __platform_vsprintf(char* buff, char* fmt, va_list args){
    return rt_vsprintf(buff, fmt, args);
}
//int __platform_vsnprintf(char* buff, size_t size, const char* fmt, va_list args){
//    return rt_vsnprintf(buff, size, fmt, args);
//}
void* __platform_malloc(size_t size) {
    return rt_malloc(size);
}
void __platform_free(void* ptr) {
    rt_free(ptr);
}
void* __platform_memset(void* mem, int ch, size_t size) {
    return rt_memset(mem, ch, size);
}
void* __platform_memcpy(void* dir, const void* src, size_t size) {
    return rt_memcpy(dir, src, size);
}
