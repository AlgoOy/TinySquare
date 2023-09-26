# pikaPython 库移植

## 准备环境

- 参考 [C 库移植](./guide_with_c_cn.md) 准备环境章节

- 在配置 menuconfig 时，将 using pikaScript lib 选项打开
  - ![TinySquare](./image/TinySquare.png)

## 库的移植

- 参考 [C 库移植](./guide_with_c_cn.md) 库的移植章节完成基础 C 运行环境的移植

- 移植完成基础 C 运行环境后，导入 pikaPython 头文件 `#include "pikaScript.h"`，创建一个 pikaPython 任务
    ```c
    static void tnsq_pika_task_entry(void *ptParam)
    {
        PikaObj* pikaMain = NULL;
        pikaMain = pikaScriptInit();
    }
    ```

- 运行该任务，即可得到 pikaPython 版的贪吃蛇游戏
    ```c
    rt_thread_t pikaTid = NULL;
    pikaTid = rt_thread_create("tnsq_pika", tnsq_pika_task_entry, RT_NULL, 4096, 20, 10);
    if (pikaTid != RT_NULL)
    {
        rt_thread_startup(pikaTid);
    }
    ```