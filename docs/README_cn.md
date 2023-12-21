# TinySquare

## 1、介绍

TinySquare 是一款嵌入式方块游戏引擎，该引擎旨在为面向 Cortex-M 处理器的设备提供一个轻量化的游戏开发解决方案。 TinySquare 的设计原则是代码尺寸小，轻量化运行成本，以确保引擎可以高效的运行在资源受限的嵌入式设备上。TinySquare有如下特点和优势：

- 图层渲染方面采用 Arm-2d 库作为底层支持，专门针对 Cortex-M 处理器进行优化，通过充分利用 Cortex-M 处理器的特性，使得引擎能够提供高效的性能和优化的游戏体验。
- 为满足嵌入式系统的资源限制，TinySquare 在开发过程中，注重引擎的代码尺寸小和运行环境轻量化，在运行过程中，使用了动态脏矩阵刷新技术，仅需一个 dirty region 即可刷新所有的脏区域，极大的节省了运行时对 RAM 的开销，以确保在有限的资源下，能够平衡引擎的性能和功能。
- TinySquare 专注于方块游戏类型，无论是类似贪吃蛇、俄罗斯方块的经典游戏还是其他基于方块的创新玩法，引擎都提供了对图层的高度自定义配置项来支持游戏的开发和定制。
- TinySquare 在设计上专注于轻量化设计，同时具备一定的灵活性和高可配性。引擎提供了一套简洁而强大的 API：仅 24 个 C API，仅 18 个 Python API。提供了丰富的可配置项允许开发人员根据自己的需求进行定制，以创建独特而令人满意的游戏体验。
- TinySquare 代码撰写和 API 命名遵循 RT-Thread 编码规范。开发过程遵循最小信息公开原则。理论上，使用 TinySquare 的开发人员仅需要关注 API 文档即可快速上手 TinySquare 的开发。

以一个最小功能的贪吃蛇为参考，给出 TinySquare 的空间开销和性能表现。注意，本用例未使用 Python 虚拟机：

<div align="center"> <img src="./image/simple_snake.jpg" width = 300 /> </div>

<table>
  <tr>
    <th colspan="5"> 参考数据 </th>
  </tr>
  <tr>
    <th colspan="2"></th>
    <th> -Os 优化 </th>
    <th> -Oz 优化 </th>
    <th> 备注 </th>
  </tr>
  <tr>
    <th rowspan="7"> 配置 </th>
    <th> 主频 </th>
    <td style="text-align:center"> 80MHz </td>
    <td style="text-align:center"> 80MHz </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> 优化等级 </th>
    <td style="text-align:center"> -Os -lto </td>
    <td style="text-align:center"> -Oz -lto </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> 屏幕尺寸 </th>
    <td style="text-align:center"> 240 * 240 </td>
    <td style="text-align:center"> 240 * 240 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> PFB 尺寸 </th>
    <td style="text-align:center"> 240 * 4 </td>
    <td style="text-align:center"> 240 * 4 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> 堆 </th>
    <td style="text-align:center"> 0x100 </td>
    <td style="text-align:center"> 0x100 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> 栈 </th>
    <td style="text-align:center"> 0x100 </td>
    <td style="text-align:center"> 0x100 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> rt heap </th>
    <td style="text-align:center"> 0x2400 </td>
    <td style="text-align:center"> 0x2400 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> 性能 </th>
    <th> FPS </th>
    <td style="text-align:center"> 140：7ms </td>
    <td style="text-align:center"> 128：7ms </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th rowspan="4"> 程序大小 </th>
    <th> Code </th>
    <td style="text-align:center"> 34156 </td>
    <td style="text-align:center"> 29688 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> RO-data </th>
    <td style="text-align:center"> 2520 </td>
    <td style="text-align:center"> 2512 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> RW-data </th>
    <td style="text-align:center"> 180 </td>
    <td style="text-align:center"> 180 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> ZI-data </th>
    <td style="text-align:center"> 16052 </td>
    <td style="text-align:center"> 16052 </td>
    <td style="text-align:center"> 包括 LCD buffer、PFB pool、rt heap、rt stack、stack、heap、snake resource 等 </td>
  </tr>
</table>

结合以上数据不难得出，引擎本身占用资源非常小，而对应的性能也非常强悍！嵌入式领域根本不需要 FPS 达到 128 甚至是 140。因此以上数据还可以进一步优化，PFB 的尺寸可以进一步降低，引擎任务和游戏任务的任务堆栈在当前测试环境下也是非常富裕，可以进一步压缩以缩小 rt heap 大小。
综上，TinySquare 满足了“代码尺寸小，轻量化运行成本”的设计原则，同时也展现了极佳的性能。

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

## 2、如何移植TinySquare

- [C 库移植](./guide_with_c_cn.md)
- [pikaPython 库移植](./guide_with_pikaPython_cn.md)

## 3、如何使用TinySquare

- [C 库使用 - 俄罗斯方块](./example_tetris_cn.md)
- [pikaPython 库使用 - 贪吃蛇](./example_snake_cn.md)
- [API](./api_cn.md)

## 4、注意事项

- [相关配置](./notice_cn.md)

## 5、联系方式 & 感谢

* 维护：[AlgoOy](https://github.com/AlgoOy)
* 主页：https://github.com/AlgoOy/TinySquare
* 感谢：[GorgonMeducer](https://github.com/GorgonMeducer)
