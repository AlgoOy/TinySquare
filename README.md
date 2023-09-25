# TinySquare

## 1、介绍

TinySquare 是一款嵌入式方块游戏引擎，该引擎旨在为面向 Cortex-M 处理器的设备提供一个轻量化的游戏开发解决方案。 TinySquare 的设计原则是代码尺寸小，轻量化运行成本，以确保引擎可以高效的运行在资源受限的嵌入式设备上。TinySquare有如下特点和优势：
- 图层渲染方面采用 Arm-2d 库作为底层支持，专门针对 Cortex-M 处理器进行优化，通过充分利用 Cortex-M 处理器的特性，使得引擎能够提供高效的性能和优化的游戏体验。
- 为满足嵌入式系统的资源限制，TinySquare 在开发过程中，注重引擎的代码尺寸小和运行环境轻量化，在运行过程中，使用了动态脏矩阵刷新技术，仅需一个 partial frame buffer 即可刷新所有图层，极大的节省了运行时对 RAM 的开销，以确保在有限的资源下，能够平衡引擎的性能和功能。
- TinySquare 专注于方块游戏类型，无论是类似贪吃蛇、俄罗斯方块的经典游戏还是其他基于方块的创新玩法，引擎都提供了对图层的高度自定义配置项来支持游戏的开发和定制。
- TinySquare 在设计上专注于轻量化设计，同时具备一定的灵活性和高可配性。引擎提供了一套简洁而强大的 API：仅 24 个 C API，仅 18 个 Python API。提供了丰富的可配置项允许开发人员根据自己的需求进行定制，以创建独特而令人满意的游戏体验。
- TinySquare 代码撰写和 API 命名遵循 RT-Thread 编码规范。开发过程遵循最小信息公开原则。理论上，使用 TinySquare 的开发人员仅需要关注 API 文档即可快速上手 TinySquare 的开发。

### 1.1 目录结构

| 名称 | 说明 |
| ---- | ---- |
| docs | 文档目录 |
| examples | 例子目录 |
| library | 依赖库目录 |
| port | 移植代码目录 |
| source | 源代码目录 |

### 1.2 许可证

TinySquare 遵循 Apache-2.0 许可，详见`LICENSE`文件。

### 1.3 依赖

- Arm-2D v1.1.5
- RT-Thread
- pikaPython

## 2、如何打开TinySquare

- [Get start with C](./docs/guide_with_c.md)
- [Get start with pikaPython](./docs/guide_with_pikaPython.md)

## 3、如何使用TinySquare

- [Get start with C](./docs/example_tetris.md)
- [Get start with pikaPython](./docs/example_snake.md)

## 4、注意事项

- [相关配置](./docs/notice.md)

## 5、联系方式 & 感谢

* 维护：[AlgoOy](https://github.com/AlgoOy)
* 主页：https://github.com/AlgoOy/TinySquare
* 感谢：[GorgonMeducer](https://github.com/GorgonMeducer)