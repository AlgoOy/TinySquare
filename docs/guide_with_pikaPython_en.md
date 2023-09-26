# pikaPython library porting

- [pikaPython library porting](#pikapython-library-porting)
  - [Prepare environment](#prepare-environment)
  - [Library porting](#library-porting)

## Prepare environment

- Refer to [C library transplantation](./guide_with_c_cn.md) to prepare the environment chapter

- When configuring menuconfig, turn on the using pikaScript lib option
   - ![TinySquare](./image/TinySquare.png)

## Library porting

- Refer to [C Library Transplantation](./guide_with_c_cn.md) library transplantation chapter to complete the transplantation of the basic C runtime environment

- After transplanting the basic C runtime environment, import the pikaPython header file `#include "pikaScript.h"` and create a pikaPython task
     ```c
     static void tnsq_pika_task_entry(void *ptParam)
     {
         PikaObj* pikaMain = NULL;
         pikaMain = pikaScriptInit();
     }
     ```

- Run this task to get the pikaPython version of the Snake game
     ```c
     rt_thread_t pikaTid = NULL;
     pikaTid = rt_thread_create("tnsq_pika", tnsq_pika_task_entry, RT_NULL, 4096, 20, 10);
     if (pikaTid != RT_NULL)
     {
         rt_thread_startup(pikaTid);
     }
     ```