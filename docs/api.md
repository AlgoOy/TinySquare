# TinySquare API 文档

[toc]

## C

### common

#### 运行环境初始化

`rt_err_t tnsq_init(void)`

> 初始化 TinySquare 的运行环境。

| 参数 | 描述 |
|:-----|:-----|
| `无` | 无参数 |
| **返回** | **描述** |
| RT_EOK | 正确执行 |
| RT_ERROR | 错误执行 |

### event

#### 按键事件获取

`rt_err_t tnsq_evt_itc_get(tnsq_evt_key_t *ptKey, rt_int32_t timeout);`

> 在指定的时间内，从事件队列（FIFO）中移除相关事件并将其存储在 ptKey 中，若 timeout 为 0，表示无等待的获取事件。

| 参数 | 描述 |
|:-----|:-----|
| `ptKey` | 指向 `tnsq_evt_key_t` 结构的指针，用于存储从事件队列获取的事件数据 |
| `timeout` | 等待事件的超时时间 |
| **返回** | **描述** |
| RT_EOK | 正确执行 |
| -RT_ETIMEOUT | 超时 |
| -RT_ERROR | 错误执行 |

#### 按键事件记录

`rt_err_t tnsq_evt_itc_put(tnsq_evt_key_t *ptKey);`

> 将相关的事件，存入事件队列（FIFO）中。

| 参数 | 描述 |
|:-----|:-----|
| `ptKey` | 指向 `tnsq_evt_key_t` 结构的指针，表示要放入事件队列的事件数据 |
| `timeout` | 等待事件的超时时间 |
| **返回** | **描述** |
| RT_EOK | 正确执行 |
| -RT_EFULL | 事件队列已满 |
| -RT_ERROR | 错误执行 |

### graphics

## PikaPython