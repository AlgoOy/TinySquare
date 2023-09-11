#include "pikaScript.h"
#include "tiny_square.h"
#include "arm_2d.h"
#include "rtthread.h"

void TinySquare_Engine___init__(PikaObj *self)
{
    arm_irq_safe {
        //arm_2d_init();
        tnsq_init();
    }
}

void TinySquare_Engine_init_evt(PikaObj *self, int priority, int stackSize, int timeSlice)
{
    printf("111\n");
    rt_thread_startup(rt_thread_create("tnsq_gfx", tnsq_evt_task_entry, NULL, stackSize, priority, timeSlice));
}

void TinySquare_Engine_init_gfx(PikaObj *self, int priority, int stackSize, int timeSlice)
{
    printf("222\n");
    rt_thread_startup(rt_thread_create("tnsq_evt", tnsq_gfx_task_entry, NULL, stackSize, priority, timeSlice));
}