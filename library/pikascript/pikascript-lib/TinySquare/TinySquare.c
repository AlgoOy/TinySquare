#include "pikaScript.h"
#include "tiny_square.h"
#include "arm_2d.h"
#include "rtthread.h"

void TinySquare___init__(PikaObj *self)
{
    arm_irq_safe {
        arm_2d_init();
        tnsq_init();
    }
}

void TinySquare_init_evt(PikaObj *self, int priority, int stackSize, int timeSlice)
{
    rt_thread_startup(rt_thread_create("tnsq_gfx", tnsq_gfx_task_entry, NULL, stackSize, priority, timeSlice));
}

void TinySquare_init_gfx(PikaObj *self, int priority, int stackSize, int timeSlice)
{
    rt_thread_startup(rt_thread_create("tnsq_evt", tnsq_evt_task_entry, NULL, stackSize, priority, timeSlice));
}