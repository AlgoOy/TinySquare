/*
 * [Warning!] This file is auto-generated by pika compiler.
 * Do not edit it manually.
 * The source code is *.pyi file.
 * More details: 
 * English Doc:
 * https://pikadoc.readthedocs.io/en/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 * Chinese Doc:
 * https://pikadoc.readthedocs.io/zh/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 */

#include "PikaMain.h"
#include <stdio.h>
#include <stdlib.h>

volatile PikaObj *__pikaMain;
PikaObj *pikaScriptInit(void){
    __platform_printf("======[pikascript packages installed]======\r\n");
    pks_printVersion();
    __platform_printf("PikaStdLib==v1.12.0\r\n");
    __platform_printf("pikaRTThread==v1.3.2\r\n");
    __platform_printf("pika_libc==v1.0.2\r\n");
    __platform_printf("===========================================\r\n");
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __pikaMain = pikaMain;
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(pikaMain, pikaModules_py_a);
#if PIKA_INIT_STRING_ENABLE
    obj_run(pikaMain,
            "import PikaStdLib\n"
            "import TinySquare\n"
            "import pikaRTThread\n"
            "thd = pikaRTThread.Thread()\n"
            "evt = TinySquare.EvtKey()\n"
            "gfx = TinySquare.Gfx()\n"
            "screen_region = TinySquare.Region(0, 0, 240, 240)\n"
            "# welcome stage\n"
            "stage = TinySquare.Stage()\n"
            "stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, TinySquare.RGB(0xcf, 0xfd, 0xcb), 255, screen_region, None, None))\n"
            "user_layer = TinySquare.LayerUser(10, 10)\n"
            "stage.register_layer(user_layer)\n"
            "for i in range(4, 10):\n"
            "    user_layer.draw_userMap(i, 1, 1)\n"
            "for i in range(3, 7):\n"
            "    user_layer.draw_userMap(i, i - 1, 1)\n"
            "for i in range(0, 6):\n"
            "    if (not i):\n"
            "        user_layer.draw_userMap(i, 6, 2)\n"
            "        continue\n"
            "    user_layer.draw_userMap(i, 6, 1)\n"
            "text_layer = TinySquare.LayerText(0, TinySquare.RGB(0x00, 0x00, 0x00), 255, TinySquare.Region(0, 0, 240, 240))\n"
            "# setting stage\n"
            "# game stage\n"
            "gfx.refresh()\n"
            "while True:\n"
            "    direction = evt.get_direction()\n"
            "    thd.mdelay(1000)\n"
            "    evt.update_key(0)\n"
            "\n");
#else 
    obj_runModule((PikaObj*)pikaMain, "main");
#endif
    return pikaMain;
}

