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
#include <pikaScript.h>
#include <stdint.h>

#define DBG_TAG    "PikaScript"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

PikaObj *pikaMain = 0;
uint8_t pika_is_inited = 0;

static void pikascript_rt_init(void *parameter){
    rt_kprintf("------------------------------------------------------------------\r\n");
    rt_kprintf("|                                                                |\r\n");
    rt_kprintf("|     ____   _   __            _____              _          __  |\r\n");
    rt_kprintf("|    / __ \\ (_) / /__ ____ _  / ___/ _____ _____ (_) ____   / /_ |\r\n");
    rt_kprintf("|   / /_/ // / / //_// __ `/  \\__ \\ / ___// ___// / / __ \\ / __/ |\r\n");
    rt_kprintf("|  / ____// / / ,<  / /_/ /  ___/ // /__ / /   / / / /_/ // /_   |\r\n");
    rt_kprintf("| /_/    /_/ /_/|_| \\__,_/  /____/ \\___//_/   /_/ / .___/ \\__/   |\r\n");
    rt_kprintf("|                                                /_/             |\r\n");
    rt_kprintf("|          PikaScript - An Ultra Lightweight Python Engine       |\r\n");
    rt_kprintf("|                                                                |\r\n");
    rt_kprintf("|           [ https://github.com/pikastech/pikascript ]          |\r\n");
    rt_kprintf("|           [  https://gitee.com/lyon1998/pikascript  ]          |\r\n");
    rt_kprintf("|                                                                |\r\n");
    rt_kprintf("------------------------------------------------------------------\r\n");
    pikaMain = pikaScriptInit();
    pika_is_inited = 1;
}

static void pikascript_entry(void *parameter){
    if(!pika_is_inited){
        pikascript_rt_init(NULL);
    }
    pikaScriptShell(pikaMain);
}

#ifdef PKG_PIKASCRIPT_USING_AUTORUNNING

#ifdef PKG_PIKASCRIPT_STACK_SIZE
#define PIKASCRIPT_STACK_SIZE   PKG_PIKASCRIPT_STACK_SIZE
#else
#define PIKASCRIPT_STACK_SIZE   4096
#endif

#ifdef PKG_PIKASCRIPT_STACK_PRIO
#define PIKASCRIPT_STACK_PRIO   PKG_PIKASCRIPT_STACK_PRIO
#else
#define PIKASCRIPT_STACK_PRIO   20
#endif


static int rt_pika_init(void){
    rt_thread_t tid;
    tid = rt_thread_create("PikaScript",
                            pikascript_entry, RT_NULL,
                            PIKASCRIPT_STACK_SIZE,
                            PIKASCRIPT_STACK_PRIO, 10);

    if (tid != RT_NULL){
        rt_thread_startup(tid);
    }
    else{
        LOG_E("PikaScript thread initialization failed!");
    }
    return 0;
}
INIT_APP_EXPORT(rt_pika_init);
#endif /* PKG_PIKASCRIPT_USING_AUTORUNNING */

static int pika_main(int argc, char *argv[]){
    pikascript_entry(NULL);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(pika_main, pika, run PikaScript);
