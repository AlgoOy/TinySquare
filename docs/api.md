# TinySquare API 文档

- [TinySquare API 文档](#tinysquare-api-文档)
  - [C](#c)
    - [common](#common)
      - [运行环境初始化](#运行环境初始化)
    - [event](#event)
      - [按键事件获取](#按键事件获取)
      - [按键事件记录](#按键事件记录)
    - [graphics](#graphics)
      - [刷新图层](#刷新图层)
      - [获取屏幕大小](#获取屏幕大小)
      - [stage 初始化](#stage-初始化)
      - [注册 layer](#注册-layer)
      - [移除 layer](#移除-layer)
      - [使 layer 可见](#使-layer-可见)
      - [使 layer 不可见](#使-layer-不可见)
      - [获取 layer 对象指针](#获取-layer-对象指针)
      - [背景颜色 layer 初始化](#背景颜色-layer-初始化)
      - [背景 layer 初始化](#背景-layer-初始化)
      - [基本单元 layer 初始化](#基本单元-layer-初始化)
      - [绘制基本单元](#绘制基本单元)
      - [用户单元 layer 初始化](#用户单元-layer-初始化)
      - [绘制用户单元](#绘制用户单元)
      - [文本 layer 初始化](#文本-layer-初始化)
      - [绘制文本](#绘制文本)
      - [数字列表 layer 初始化](#数字列表-layer-初始化)
      - [获取选中数字索引](#获取选中数字索引)
      - [菜单 layer 初始化](#菜单-layer-初始化)
      - [获取选中菜单项名称](#获取选中菜单项名称)
      - [获取选中菜单项索引](#获取选中菜单项索引)
  - [PikaPython](#pikapython)
    - [common](#common-1)
      - [引擎初始化](#引擎初始化)
      - [颜色转换](#颜色转换)
    - [按键事件类](#按键事件类)
      - [按键事件类初始化](#按键事件类初始化)
      - [更新按键状态](#更新按键状态)
      - [获取按键方向](#获取按键方向)
      - [获取按键事件](#获取按键事件)
    - [graphics 类](#graphics-类)
      - [graphics 类初始化](#graphics-类初始化)
      - [申请刷新](#申请刷新)
      - [切换 stage](#切换-stage)
    - [stage 类](#stage-类)
      - [stage 类初始化](#stage-类初始化)
      - [注册 layer](#注册-layer-1)
      - [移除 layer](#移除-layer-1)
      - [使 layer 可见](#使-layer-可见-1)
      - [使 layer 不可见](#使-layer-不可见-1)
    - [screen 类](#screen-类)
      - [screen 类初始化](#screen-类初始化)
      - [获取 screen 宽度](#获取-screen-宽度)
      - [获取 screen 高度](#获取-screen-高度)
    - [region 类](#region-类)
      - [region 类初始化](#region-类初始化)
    - [border opacity 类](#border-opacity-类)
      - [border opacity 类初始化](#border-opacity-类初始化)
    - [corner opacity 类](#corner-opacity-类)
      - [corner opacity 类初始化](#corner-opacity-类初始化)
    - [背景颜色 layer 类](#背景颜色-layer-类)
      - [背景颜色 layer 类初始化](#背景颜色-layer-类初始化)
    - [基础单元 layer 类](#基础单元-layer-类)
      - [基础单元 layer 类初始化](#基础单元-layer-类初始化)
      - [基础单元绘制](#基础单元绘制)
    - [用户单元 layer 类](#用户单元-layer-类)
      - [用户单元 layer 类初始化](#用户单元-layer-类初始化)
      - [用户单元绘制](#用户单元绘制)
    - [文本 layer 类](#文本-layer-类)
      - [文本 layer 类初始化](#文本-layer-类初始化)
      - [绘制字符串](#绘制字符串)
      - [绘制数字](#绘制数字)
    - [数字列表 layer 类](#数字列表-layer-类)
      - [数字列表 layer 类初始化](#数字列表-layer-类初始化)
      - [选中列表项索引获取](#选中列表项索引获取)
    - [item format 类](#item-format-类)
      - [item format 类初始化](#item-format-类初始化)
    - [菜单 layer 类](#菜单-layer-类)
      - [菜单 layer 类初始化](#菜单-layer-类初始化)
      - [选中列表项索引获取](#选中列表项索引获取-1)

## C

### common

#### 运行环境初始化

`rt_err_t tnsq_init(void)`

> 初始化 TinySquare 的运行环境，创建 graphics 和 event 任务。

| 参数 | 描述 |
|:-----|:-----|
| `无` | 无参数 |
| **返回** | **描述** |
| `RT_EOK` | 正确执行 |
| `RT_ERROR` | 错误执行 |

### event

#### 按键事件获取

`rt_err_t tnsq_evt_itc_get(tnsq_evt_key_t *ptKey, rt_int32_t timeout);`

> 在指定的时间内，从事件队列（FIFO）中移除相关事件并将其存储在 ptKey 中，若 timeout 为 0，表示无等待的获取事件。

| 参数 | 描述 |
|:-----|:-----|
| `*ptKey` | 指向 `tnsq_evt_key_t` 结构的指针，用于存储从事件队列获取的事件数据 |
| `timeout` | 等待事件的超时时间 |
| **返回** | **描述** |
| `RT_EOK` | 正确执行 |
| `-RT_ETIMEOUT` | 超时 |
| `-RT_ERROR` | 错误执行 |

#### 按键事件记录

`rt_err_t tnsq_evt_itc_put(tnsq_evt_key_t *ptKey);`

> 将相关的事件，存入事件队列（FIFO）中。

| 参数 | 描述 |
|:-----|:-----|
| `*ptKey` | 指向 `tnsq_evt_key_t` 结构的指针，表示要放入事件队列的事件数据 |
| `timeout` | 等待事件的超时时间 |
| **返回** | **描述** |
| `RT_EOK` | 正确执行 |
| `-RT_EFULL` | 事件队列已满 |
| `-RT_ERROR` | 错误执行 |

### graphics

#### 刷新图层

`void tnsq_gfx_apply_for_refresh(void);`

> 申请刷新屏幕。

| 参数 | 描述 |
|:-----|:-----|
| `无` | 无参数 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 获取屏幕大小

`arm_2d_size_t tnsq_gfx_get_screen_size(arm_2d_scene_player_t *ptDispAdapter);
`

> 获取指定 display adapter 对应屏幕的大小。

| 参数 | 描述 |
|:-----|:-----|
| `*ptDispAdapter` | 指向`arm_2d_scene_player_t` 结构的指针，代表对应的 display adapter |
| **返回** | **描述** |
| `arm_2d_size_t` | 表示屏幕的大小的结构体，包括宽度（width）和高度（height） |

#### stage 初始化

`tnsq_gfx_stage_t *tnsq_gfx_stage_init(tnsq_gfx_stage_cfg_t *ptStageCFG, tnsq_gfx_stage_t *ptStage);`

> 初始化一个 stage，如果 `ptStage` 为 `RT_NULL` 或为空，对应的 stage 对象由引擎动态分配与回收；如果 `ptStage` 不为 `RT_NULL`，对应的 stage 对象由用户负责，用户需保证生命周期内 stage 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptStageCFG` | 指向 `tnsq_gfx_stage_cfg_t` 结构的指针，包含用于初始化 stage 的配置参数 |
| `*ptStage` | 可选参数，指向 `tnsq_gfx_stage_t` 结构的指针，表示要初始化的 stage 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_stage_t *` | 初始化成功，返回指向新初始化的 stage 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 注册 layer

`rt_uint8_t tnsq_gfx_register_layer_to_stage(tnsq_gfx_stage_t *ptStage, void *ptLayer);`

> 将指定的 layer 注册到 指定的 stage 中去，返回一个唯一标识 layer 的 ID。

| 参数 | 描述 |
|:-----|:-----|
| `*ptStage` | 指向 `tnsq_gfx_stage_t` 结构的指针，表示要注册 layer 的 stage 对象 |
| `*ptLayer` | 指向待注册的 layer 对象的指针，可以是特定类型的 layer 对象 |
| **返回** | **描述** |
| `rt_uint8_t` | 唯一表示 layer 的 ID |

#### 移除 layer

`void tnsq_gfx_remove_layer(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> 从指定的 stage 中，移除指定的 layer。

| 参数 | 描述 |
|:-----|:-----|
| `*ptStage` | 指向 `tnsq_gfx_stage_t` 结构的指针，表示要从中移除 layer 的 stage 对象 |
| `*chLayerID` | 表示要移除的 layer 的唯一标识 ID |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 使 layer 可见

`void tnsq_gfx_make_layer_visible(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> 使指定的 stage 中，指定的 layer 可见。

| 参数 | 描述 |
|:-----|:-----|
| `*ptStage` | 指向 `tnsq_gfx_stage_t` 结构的指针，表示操作的 stage 对象 |
| `*chLayerID` | 表示要使可见的 layer 的唯一标识 ID |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 使 layer 不可见

`void tnsq_gfx_make_layer_invisible(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> 使指定的 stage 中，指定的 layer 不可见。

| 参数 | 描述 |
|:-----|:-----|
| `*ptStage` | 指向 `tnsq_gfx_stage_t` 结构的指针，表示操作的 stage 对象 |
| `*chLayerID` | 表示要使不可见的 layer 的唯一标识 ID |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 获取 layer 对象指针

`void *tnsq_gfx_get_layer_ptr(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> 获取指定 stage 中对应 ID 标识的 layer 对象的指针。

| 参数 | 描述 |
|:-----|:-----|
| `*ptStage` | 指向 `tnsq_gfx_stage_t` 结构的指针，表示操作的 stage 对象 |
| `*chLayerID` | 表示要获取指针的 layer 的唯一标识 ID |
| **返回** | **描述** |
| `void *` | 指向指定 layer 的指针 |
| `RT_NULL` | ID 不存在 |

#### 背景颜色 layer 初始化

`tnsq_gfx_layer_bg_cl_t *tnsq_gfx_layer_bg_cl_init(tnsq_gfx_layer_bg_cl_cfg_t *ptLayerCFG, tnsq_gfx_layer_bg_cl_t *ptLayer);`

> 初始化一个背景颜色 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_bg_cl_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_bg_cl_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_bg_cl_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 背景 layer 初始化

`tnsq_gfx_layer_bg_t *tnsq_gfx_layer_bg_init(tnsq_gfx_layer_bg_cfg_t *ptLayerCFG, tnsq_gfx_layer_bg_t *ptLayer);`

> 初始化一个背景 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_bg_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_bg_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_bg_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 基本单元 layer 初始化

`tnsq_gfx_layer_cell_t *tnsq_gfx_layer_cell_init(tnsq_gfx_layer_cell_cfg_t *ptLayerCFG, tnsq_gfx_layer_cell_t *ptLayer);`

> 初始化一个基本单元 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_cell_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_cell_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_cell_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 绘制基本单元

`void tnsq_gfx_layer_cell_draw(tnsq_gfx_layer_cell_t *ptLayer, rt_uint16_t iX, rt_uint16_t iY, rt_uint8_t chOpacity, COLOUR_INT tColor);`

> 通过 `iX` 和 `iY`，标识基本单元 layer 中特定的一个单元，设置它的不透明度和颜色。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayer` | 指向 `tnsq_gfx_layer_cell_t` 结构的指针，标识要进行绘制操作的 layer 对象 |
| `iX` | 绘制的单元横坐标位置 |
| `iY` | 绘制的单元纵坐标位置 |
| `chOpacity` | 不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `tColor` | 绘制使用的颜色 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 用户单元 layer 初始化

`tnsq_gfx_layer_user_t *tnsq_gfx_layer_user_init(tnsq_gfx_layer_user_cfg_t *ptLayerCFG, tnsq_gfx_layer_user_t *ptLayer);`

> 初始化一个用户单元 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_user_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_user_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_user_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 绘制用户单元

`void tnsq_gfx_layer_user_draw(tnsq_gfx_layer_user_t *ptLayer, rt_uint16_t iX, rt_uint16_t iY, rt_uint8_t u7Idx);`

> 通过 `iX` 和 `iY`， 标识用户单元 layer 中特定的一个单元，根据 `u7Idx`，执行相应的绘制操作（在初始化用户单元 layer 时，会配置相应的绘制函数）。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayer` | 指向 `tnsq_gfx_layer_user_t` 结构的指针，标识要进行绘制操作的 layer 对象 |
| `iX` | 绘制的单元横坐标位置 |
| `iY` | 绘制的单元纵坐标位置 |
| `u7Idx` | 用户自定义绘制操作的索引，用于区分不同的绘制操作 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 文本 layer 初始化

`tnsq_gfx_layer_text_t *tnsq_gfx_layer_text_init(tnsq_gfx_layer_text_cfg_t *ptLayerCFG, tnsq_gfx_layer_text_t *ptLayer);`

> 初始化一个文本 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_text_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_text_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_text_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 绘制文本

`rt_int32_t tnsq_gfx_layer_text_printf(tnsq_gfx_layer_text_t *ptLayer, const char *format, ...);`

> 在指定的文本 layer 上，绘制文本。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayer` | 指向 `tnsq_gfx_layer_text_t` 结构的指针，标识要进行绘制操作的 layer 对象 |
| `*format` | 一个格式化字符串，用于指定要输出的文本格式。支持与 `printf` 函数相似的格式说明符 |
| `...` | 可变数量的参数，根据 `format` 字符串中的格式说明符进行文本替换 |
| **返回** | **描述** |
| `rt_int32_t` | 正确执行，返回写入文本的字符数 |
| `-1` | 错误执行 |

#### 数字列表 layer 初始化

`tnsq_gfx_layer_num_t *tnsq_gfx_layer_num_init(tnsq_gfx_layer_num_cfg_t *ptLayerCFG, tnsq_gfx_layer_num_t *ptLayer);`

> 初始化一个数字列表 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_num_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_num_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_num_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 获取选中数字索引

`rt_int8_t tnsq_gfx_layer_num_get_item_idx(tnsq_gfx_layer_num_t *ptLayer);`

> 获取指定数字列表 layer 选择的数字索引。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayer` | 指向 `tnsq_gfx_layer_num_t` 结构的指针，标识要获取当前项索引的 layer 对象 |
| **返回** | **描述** |
| `rt_int8_t` | 正确执行，返回当前项的索引 |
| `-1` | 错误执行 |

#### 菜单 layer 初始化

`tnsq_gfx_layer_menu_t *tnsq_gfx_layer_menu_init(tnsq_gfx_layer_menu_cfg_t *ptLayerCFG, tnsq_gfx_layer_menu_t *ptLayer);`

> 初始化一个菜单 layer，如果 `ptLayer` 为 `RT_NULL` 或为空，对应的 layer 对象由引擎动态分配与回收；如果 `ptLayer` 不为 `RT_NULL`，对应的 layer 对象由用户负责，用户需保证生命周期内 layer 对象占用的地址空间始终有效，否则将导致未定义的错误。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayerCFG` | 指向 `tnsq_gfx_layer_menu_cfg_t` 结构的指针，包含用于初始化 layer 的配置参数 |
| `*ptLayer` | 可选参数，指向 `tnsq_gfx_layer_menu_t` 结构的指针，表示要初始化的 layer 对象，为 `RT_NULL` 和为空时，表示动态初始化，否则，表示静态初始化 |
| **返回** | **描述** |
| `tnsq_gfx_layer_menu_t *` | 初始化成功，返回指向新初始化的 layer 对象的指针 |
| `RT_NULL` | 初始化失败 |

#### 获取选中菜单项名称

`const char *tnsq_gfx_layer_menu_get_item_name(tnsq_gfx_layer_menu_t *ptLayer);`

> 获取指定菜单 layer 选择的菜单项的名称。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayer` | 指向 `tnsq_gfx_layer_menu_t` 结构的指针，标识要获取当前项名称的 layer 对象 |
| **返回** | **描述** |
| `const char *` | 正确执行，返回当前菜单项名称的常量字符串地址 |
| `NULL` | 错误执行 |

#### 获取选中菜单项索引

`rt_int8_t tnsq_gfx_layer_menu_get_item_idx(tnsq_gfx_layer_menu_t *ptLayer);`

> 获取指定菜单 layer 选择的菜单项的索引。

| 参数 | 描述 |
|:-----|:-----|
| `*ptLayer` | 指向 `tnsq_gfx_layer_menu_t` 结构的指针，标识要获取当前项索引的 layer 对象 |
| **返回** | **描述** |
| `rt_int8_t` | 正确执行，返回当前项的索引 |
| `-1` | 错误执行 |

## PikaPython

### common

#### 引擎初始化

`def __init__(self): ...`

> 初始化引擎中的一些常量。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 颜色转换

`def RGB(r: int, g: int, b: int) -> int: ...`

> 将 RGB 颜色转换为引擎使用的颜色类型。

| 参数 | 描述 |
|:-----|:-----|
| `r` | 整数值，表示红色通道的值（0-255） |
| `g` | 整数值，表示绿色通道的值（0-255） |
| `b` | 整数值，表示蓝色通道的值（0-255） |
| **返回** | **描述** |
| `int` | 对应引擎使用的颜色表示 |

### 按键事件类

#### 按键事件类初始化

`def __init__(self): ...`

> 初始化按键事件对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 更新按键状态

`def update_key(self, timeout:int) -> int: ...`

> 根据超时时间，更新按键的状态。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `timeout` | 整数值，表示超时时间，以毫秒为单位 |
| **返回** | **描述** |
| `0` | 正确执行 |
| `-1` | 错误执行 |
| `-2` | 超时执行 |

#### 获取按键方向

`def get_direction(self) -> int: ...`

> 获取按键方向信息。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `KEY_DIRECTION_UP` | 向上 |
| `KEY_DIRECTION_DOWN` | 向下 |
| `KEY_DIRECTION_LEFT` | 向左 |
| `KEY_DIRECTION_RIGHT` | 向右 |

#### 获取按键事件

`def get_event(self) -> int: ...`

> 获取按键事件信息。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `KEY_EVENT_UP` | 按键抬起 |
| `KEY_EVENT_DOWN` | 按键按下 |
| `KEY_EVENT_PRESSED` | 短按 |
| `KEY_EVENT_LONG_PRESSED` | 长按 |

### graphics 类

#### graphics 类初始化

`def __init__(self): ...`

> 初始化 graphics 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 申请刷新

`def refresh(self): ...`

> 申请刷新屏幕。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 切换 stage

`def switch_stage(self): ...`

> 切换到下一个 stage。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

### stage 类

#### stage 类初始化

`def __init__(self): ...`

> 初始化 stage 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 注册 layer

`def register_layer(self, layer: object) -> int: ...`

> 将指定的 layer 对象注册到 stage 中。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `layer` | 欲注册到 stage 中的 layer 对象 |
| **返回** | **描述** |
| `int` | 唯一表示 layer 的 ID |

#### 移除 layer

`def remove_layer(self, layerID: int): ...`

> 移除 stage 中，唯一 ID 标识的 layer。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `layerID` | 标识待移除 layer 的唯一 ID |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 使 layer 可见

`def visible_layer(self, layerID: int): ...`

> 使 stage 中，唯一 ID 标识的 layer 可见。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `layerID` | 标识待操作 layer 的唯一 ID |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 使 layer 不可见

`def invisible_layer(self, layerID: int): ...`

> 使 stage 中，唯一 ID 标识的 layer 不可见。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `layerID` | 标识待操作 layer 的唯一 ID |
| **返回** | **描述** |
| `无` | 无返回值 |

### screen 类

#### screen 类初始化

`def __init__(self): ...`

> 初始化 screen 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 获取 screen 宽度

`def width(self) -> int: ...`

> 获取 screen 的宽度。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `int` | screen 的宽度 |

#### 获取 screen 高度

`def height(self) -> int: ...`

> 获取 screen 的高度。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `int` | screen 的高度 |

### region 类

#### region 类初始化

`def __init__(self, hwX: int, hwY: int, hwWidth: int, hwHeight: int): ...`

> 初始化 screen 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `hwX` | region 的 x 起始坐标 |
| `hwY` | region 的 y 起始坐标 |
| `hwWidth` | region 的宽度 |
| `hwHeight` | region 的高度 |
| **返回** | **描述** |
| `无` | 无返回值 |

### border opacity 类

#### border opacity 类初始化

`def __init__(self, left: int, right: int, top: int, bottom: int): ...`

> 初始化 border opacity 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `left` | 左边的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `right` | 右边的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `top` | 上边的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `bottom` | 下边的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| **返回** | **描述** |
| `无` | 无返回值 |

### corner opacity 类

#### corner opacity 类初始化

`def __init__(self, leftTop: int, rightTop: int, rightBottom: int, leftBottom: int): ...`

> 初始化 corner opacity 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `leftTop` | 左上角的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `rightTop` | 右上角的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `rightBottom` | 右下角的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `leftBottom` | 左下角的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| **返回** | **描述** |
| `无` | 无返回值 |

### 背景颜色 layer 类

#### 背景颜色 layer 类初始化

`def __init__(self, type: int, color: int, opacity: int, region: Region, borderOpacity: BorderOpacity, cornerOpacity: CornerOpacity): ...`

> 初始化 corner opacity 对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `type` | 背景颜色 layer 的类型，可选项为：`BG_CL_NORMAL`、`BG_CL_BOX`、`BG_CL_BORDER` |
| `color` | 背景颜色 |
| `opacity` | 背景颜色的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `region` | 背景颜色 layer 的位置和大小 |
| `borderOpacity` | 当 `type` 为 `BG_CL_BORDER` 时，指定 border opacity |
| `cornerOpacity` | 当 `type` 为 `BG_CL_BORDER` 时，指定 corner opacity |
| **返回** | **描述** |
| `无` | 无返回值 |

### 基础单元 layer 类

#### 基础单元 layer 类初始化

`def __init__(self, hwXCount: int, hwYCount: int): ...`

> 初始化基础单元 layer 类对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `hwXCount` | x 方向单元个数 |
| `hwYCount` | y 方向单元个数 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 基础单元绘制

`def draw_cell(self, hwX: int, hwY: int, color: int, opacity: int): ...`

> 绘制基础单元 layer 中的指定单元。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `hwX` | 绘制的单元横坐标位置 |
| `hwY` | 绘制的单元纵坐标位置 |
| `color` | 绘制使用的颜色 |
| `opacity` | 不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| **返回** | **描述** |
| `无` | 无返回值 |

### 用户单元 layer 类

#### 用户单元 layer 类初始化

`def __init__(self, hwXCount: int, hwYCount: int): ...`

> 初始化用户单元 layer 类对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `hwXCount` | x 方向单元个数 |
| `hwYCount` | y 方向单元个数 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 用户单元绘制

`def draw_userMap(self, hwX: int, hwY: int, idx: int): ...`

> 绘制用户单元 layer 中的指定单元。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `hwX` | 绘制的单元横坐标位置 |
| `hwY` | 绘制的单元纵坐标位置 |
| `idx` | 系统自定义绘制操作的索引，用于区分不同的绘制操作（具体绘制函数是弱定义的，用户若希望自定义绘制操作，可重定义绘制函数） |
| **返回** | **描述** |
| `无` | 无返回值 |

### 文本 layer 类

#### 文本 layer 类初始化

`def __init__(self, fontType: int, color: int, opacity: int, region: Region): ...`

> 初始化文本 layer 类对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `fontType` | 字体的类型，可选项有：`TEXT_FONT_6X8`、`TEXT_FONT_16X24`、`TEXT_FONT_A2_DIGITS_ONLY`、`TEXT_FONT_A4_DIGITS_ONLY`、`TEXT_FONT_A8_DIGITS_ONLY` |
| `color` | 文本的颜色 |
| `opacity` | 文本的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| `region` | 文本 layer 的位置和大小 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 绘制字符串

`def print_str(self, format: str, string: str): ...`

> 向文本 layer 中绘制字符串。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `format` | 一个格式化字符串，用于指定要输出的文本格式。支持与 `printf` 函数相似的格式说明符 |
| `string` | 字符串参数 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 绘制数字

`def print_num(self, format: str, number: int): ...`

> 向文本 layer 中绘制数字。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `format` | 一个格式化字符串，用于指定要输出的文本格式。支持与 `printf` 函数相似的格式说明符 |
| `number` | 数字参数 |
| **返回** | **描述** |
| `无` | 无返回值 |

### 数字列表 layer 类

#### 数字列表 layer 类初始化

`def __init__(self, number:int, bgColor: int, textColor: int): ...`

> 初始化数字列表 layer 类对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `number` | 数字列表的列表项个数 |
| `bgColor` | 列表项的背景颜色 |
| `textColor` | 列表项的文本颜色 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 选中列表项索引获取

`def get_idx(self) -> int: ...`

> 获取数字列表 layer 类对象中，被选中的列表项索引。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `int` | 正确执行，返回被选中的索引项 |
| `-1` | 错误执行 |

### item format 类

#### item format 类初始化

`def __init__(self, boxColor: int, textColor: int, opacity: int): ...`

> 初始化 item format 类对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `boxColor` | item 的背景颜色 |
| `textColor` | item 的文本颜色 |
| `opacity` | 文本的不透明度，范围为 0 到 255，0 表示完全透明，255 表示不透明 |
| **返回** | **描述** |
| `无` | 无返回值 |

### 菜单 layer 类

#### 菜单 layer 类初始化

`def __init__(self, strTable: tuple, fontType: int, itemWidth: int, itemHeight: int, itemNormal: ItemFormat, itemSelect: ItemFormat): ...`

> 初始化菜单 layer 类对象。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| `strTable` | 以 `tuple` 形式存储的菜单项名称表 |
| `fontType` | 字体的类型，可选项有：`TEXT_FONT_6X8`、`TEXT_FONT_16X24`、`TEXT_FONT_A2_DIGITS_ONLY`、`TEXT_FONT_A4_DIGITS_ONLY`、`TEXT_FONT_A8_DIGITS_ONLY` |
| `itemWidth` | 菜单项的宽度 |
| `itemHeight` | 菜单项的高度 |
| `itemNormal` | 未被选中时菜单项的外观 |
| `itemSelect` | 被选中时菜单项的外观 |
| **返回** | **描述** |
| `无` | 无返回值 |

#### 选中列表项索引获取

`def get_idx(self) -> int: ...`

> 获取菜单 layer 类对象中，被选中的列表项索引。

| 参数 | 描述 |
|:-----|:-----|
| `self` | 对象自身的引用 |
| **返回** | **描述** |
| `int` | 正确执行，返回被选中的索引项 |
| `-1` | 错误执行 |