# TinySquare

[中文页](./docs/README_cn.md)

## 1. Introduction

TinySquare is an embedded block game engine designed to provide a lightweight game development solution for devices targeting Cortex-M processors. TinySquare's design principles are small code size and lightweight running costs to ensure that the engine can run efficiently on resource-constrained embedded devices. TinySquare has the following features and advantages:
- Layer rendering uses the Arm-2d library as the underlying support, which is specifically optimized for the Cortex-M processor. By fully utilizing the characteristics of the Cortex-M processor, the engine can provide efficient performance and optimized gaming experience.
- In order to meet the resource constraints of embedded systems, TinySquare focused on the small code size of the engine and the lightweight running environment during the development process. During the running process, dynamic dirty matrix refresh technology was used, and only one partial frame buffer was needed to refresh. All layers greatly save RAM overhead during runtime to ensure that the performance and functionality of the engine can be balanced under limited resources.
- TinySquare focuses on block game types. Whether it is classic games like Snake, Tetris, or other innovative block-based gameplay, the engine provides highly customized configuration items for layers to support game development and customization.
- TinySquare focuses on lightweight design, while also having a certain degree of flexibility and high configurability. The engine provides a concise and powerful set of APIs: only 24 C APIs and only 18 Python APIs. A rich set of configurable options allows developers to customize according to their needs to create a unique and satisfying gaming experience.
- TinySquare code writing and API naming follow RT-Thread coding standards. The development process follows the principle of minimum information disclosure. In theory, developers using TinySquare only need to pay attention to the API documentation to quickly get started with TinySquare development.

### 1.1 Contents

| Name | Description |
| ---- | ---- |
| docs | Document directory |
| examples | examples directory |
| library | dependent library directory |
| port | ported code directory |
| source | source code directory |

### 1.2 License

TinySquare is licensed under the Apache-2.0 license, see the `LICENSE` file for details.

### 1.3 Dependence

- Arm-2D v1.1.5
- RT-Thread
- pikaPython

## 2. How to port TinySquare

- [C library porting](./docs/guide_with_c_en.md)
- [pikaPython library porting](./docs/guide_with_pikaPython_en.md)

## 3. How to use TinySquare

- [C library usage - Tetris](./docs/example_tetris_en.md)
- [pikaPython library usage - Snake](./docs/example_snake_en.md)
- [API](./docs/api_en.md)

## 4. Notice

- [Notice](./docs/notice_en.md)

## 5. Contact & Thanks

* Maintainer: [AlgoOy](https://github.com/AlgoOy)
* Home page: https://github.com/AlgoOy/TinySquare
* Thanks: [GorgonMeducer](https://github.com/GorgonMeducer)