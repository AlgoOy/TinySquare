# TinySquare API documentation

- [TinySquare API documentation](#tinysquare-api-documentation)
  - [C](#c)
    - [common](#common)
      - [run environment initialization](#run-environment-initialization)
    - [event](#event)
      - [get key event](#get-key-event)
      - [key event recording](#key-event-recording)
    - [graphics](#graphics)
      - [refresh layer](#refresh-layer)
      - [get screen size](#get-screen-size)
      - [stage initialization](#stage-initialization)
      - [register layer](#register-layer)
      - [remove layer](#remove-layer)
      - [make layer visible](#make-layer-visible)
      - [make layer invisible](#make-layer-invisible)
      - [get the layer object pointer](#get-the-layer-object-pointer)
      - [background color layer initialization](#background-color-layer-initialization)
      - [background layer initialization](#background-layer-initialization)
      - [cell layer initialization](#cell-layer-initialization)
      - [draw cell](#draw-cell)
      - [user layer initialization](#user-layer-initialization)
      - [draw user cell](#draw-user-cell)
      - [text layer initialization](#text-layer-initialization)
      - [draw text](#draw-text)
      - [number list layer initialization](#number-list-layer-initialization)
      - [get the selected number index](#get-the-selected-number-index)
      - [menu layer initialization](#menu-layer-initialization)
      - [get the name of the selected menu item](#get-the-name-of-the-selected-menu-item)
      - [get the selected menu item index](#get-the-selected-menu-item-index)
  - [PikaPython](#pikapython)
    - [common](#common-1)
      - [engine initialization](#engine-initialization)
      - [color conversion](#color-conversion)
    - [key event class](#key-event-class)
      - [key event class initialization](#key-event-class-initialization)
      - [update key status](#update-key-status)
      - [get key direction](#get-key-direction)
      - [get key events](#get-key-events)
    - [graphics class](#graphics-class)
      - [graphics class initialization](#graphics-class-initialization)
      - [apply for refresh](#apply-for-refresh)
      - [switch stage](#switch-stage)
    - [stage class](#stage-class)
      - [stage class initialization](#stage-class-initialization)
      - [register layer](#register-layer-1)
      - [remove layer](#remove-layer-1)
      - [make layer visible](#make-layer-visible-1)
      - [make layer invisible](#make-layer-invisible-1)
    - [screen class](#screen-class)
      - [screen class initialization](#screen-class-initialization)
      - [get screen width](#get-screen-width)
      - [get screen height](#get-screen-height)
    - [region class](#region-class)
      - [region class initialization](#region-class-initialization)
    - [border opacity class](#border-opacity-class)
      - [border opacity class initialization](#border-opacity-class-initialization)
    - [corner opacity class](#corner-opacity-class)
      - [corner opacity class initialization](#corner-opacity-class-initialization)
    - [background color layer class](#background-color-layer-class)
      - [background color layer class initialization](#background-color-layer-class-initialization)
    - [cell layer class](#cell-layer-class)
      - [cell layer class initialization](#cell-layer-class-initialization)
      - [draw cell](#draw-cell-1)
    - [user layer class](#user-layer-class)
      - [user layer class initialization](#user-layer-class-initialization)
      - [draw user cell](#draw-user-cell-1)
    - [text layer class](#text-layer-class)
      - [text layer class initialization](#text-layer-class-initialization)
      - [print string](#print-string)
      - [print number](#print-number)
    - [number list layer class](#number-list-layer-class)
      - [number list layer class initialization](#number-list-layer-class-initialization)
      - [get the index of the selected list item](#get-the-index-of-the-selected-list-item)
    - [item format class](#item-format-class)
      - [item format class initialization](#item-format-class-initialization)
    - [menu layer class](#menu-layer-class)
      - [menu layer class initialization](#menu-layer-class-initialization)
      - [get the index of the selected list item](#get-the-index-of-the-selected-list-item-1)

## C

### common

#### run environment initialization

`rt_err_t tnsq_init(void)`

> Initialize TinySquare's running environment and create graphics and event tasks.

| Parameters | Description |
|:-----|:-----|
| `None` | No parameters |
| **Return** | **Description** |
| `RT_EOK` | Correct execution |
| `RT_ERROR` | Error execution |

### event

#### get key event

`rt_err_t tnsq_evt_itc_get(tnsq_evt_key_t *ptKey, rt_int32_t timeout);`

> Within the specified time, remove relevant events from the event queue (FIFO) and store them in ptKey. If timeout is 0, it means there is no waiting to obtain events.

| Parameters | Description |
|:-----|:-----|
| `*ptKey` | Pointer to `tnsq_evt_key_t` structure, used to store event data obtained from the event queue |
| `timeout` | Timeout for waiting for events |
| **Return** | **Description** |
| `RT_EOK` | Correct execution |
| `-RT_ETIMEOUT` | Timeout |
| `-RT_ERROR` | Error execution |

#### key event recording

`rt_err_t tnsq_evt_itc_put(tnsq_evt_key_t *ptKey);`

> Store relevant events in the event queue (FIFO).

| Parameters | Description |
|:-----|:-----|
| `*ptKey` | Pointer to `tnsq_evt_key_t` structure, representing the event data to be put into the event queue |
| `timeout` | Timeout for waiting for events |
| **Return** | **Description** |
| `RT_EOK` | Correct execution |
| `-RT_EFULL` | The event queue is full |
| `-RT_ERROR` | Error execution |

### graphics

#### refresh layer

`void tnsq_gfx_apply_for_refresh(void);`

> Apply to refresh the screen.

| Parameters | Description |
|:-----|:-----|
| `None` | No parameters |
| **Return** | **Description** |
| `None` | No return value |

#### get screen size

`arm_2d_size_t tnsq_gfx_get_screen_size(arm_2d_scene_player_t *ptDispAdapter);
`

> Get the screen size corresponding to the specified display adapter.

| Parameters | Description |
|:-----|:-----|
| `*ptDispAdapter` | Pointer to the `arm_2d_scene_player_t` structure, representing the corresponding display adapter |
| **Return** | **Description** |
| `arm_2d_size_t` | A structure representing the size of the screen, including width (width) and height (height) |

#### stage initialization

`tnsq_gfx_stage_t *tnsq_gfx_stage_init(tnsq_gfx_stage_cfg_t *ptStageCFG, tnsq_gfx_stage_t *ptStage);`

> Initialize a stage. If `ptStage` is `RT_NULL` or empty, the corresponding stage object is dynamically allocated and recycled by the engine; if `ptStage` is not `RT_NULL`, the corresponding stage object is the responsibility of the user, and the user needs to ensure the life cycle The address space occupied by the inner stage object is always valid, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptStageCFG` | Pointer to `tnsq_gfx_stage_cfg_t` structure containing configuration parameters used to initialize the stage |
| `*ptStage` | Optional parameter, pointer to the `tnsq_gfx_stage_t` structure, indicating the stage object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_stage_t *` | Initialization successful, returns a pointer to the newly initialized stage object |
| `RT_NULL` | Initialization failed |

#### register layer

`rt_uint8_t tnsq_gfx_register_layer_to_stage(tnsq_gfx_stage_t *ptStage, void *ptLayer);`

> Register the specified layer into the specified stage and return an ID that uniquely identifies the layer.

| Parameters | Description |
|:-----|:-----|
| `*ptStage` | Pointer to the `tnsq_gfx_stage_t` structure, indicating the stage object of the layer to be registered |
| `*ptLayer` | Pointer to the layer object to be registered, which can be a specific type of layer object |
| **Return** | **Description** |
| `rt_uint8_t` | Uniquely represents the ID of the layer |

#### remove layer

`void tnsq_gfx_remove_layer(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> Remove the specified layer from the specified stage.

| Parameters | Description |
|:-----|:-----|
| `*ptStage` | Pointer to a `tnsq_gfx_stage_t` structure, representing the stage object from which the layer is to be removed |
| `*chLayerID` | Represents the unique identification ID of the layer to be removed |
| **Return** | **Description** |
| `None` | No return value |

#### make layer visible

`void tnsq_gfx_make_layer_visible(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> Make the specified layer visible in the specified stage.

| Parameters | Description |
|:-----|:-----|
| `*ptStage` | Pointer to `tnsq_gfx_stage_t` structure, representing the stage object of the operation |
| `*chLayerID` | Represents the unique identification ID of the layer to be made visible |
| **Return** | **Description** |
| `None` | No return value |

#### make layer invisible

`void tnsq_gfx_make_layer_invisible(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> Make the specified layer invisible in the specified stage.

| Parameters | Description |
|:-----|:-----|
| `*ptStage` | Pointer to `tnsq_gfx_stage_t` structure, representing the stage object of the operation |
| `*chLayerID` | Represents the unique identification ID of the layer to be made invisible |
| **Return** | **Description** |
| `None` | No return value |

#### get the layer object pointer

`void *tnsq_gfx_get_layer_ptr(tnsq_gfx_stage_t *ptStage, rt_uint8_t chLayerID);`

> Get the pointer of the layer object corresponding to the ID in the specified stage.

| Parameters | Description |
|:-----|:-----|
| `*ptStage` | Pointer to `tnsq_gfx_stage_t` structure, representing the stage object of the operation |
| `*chLayerID` | Represents the unique identification ID of the layer to obtain the pointer |
| **Return** | **Description** |
| `void *` | Pointer to the specified layer |
| `RT_NULL` | ID does not exist |

#### background color layer initialization

`tnsq_gfx_layer_bg_cl_t *tnsq_gfx_layer_bg_cl_init(tnsq_gfx_layer_bg_cl_cfg_t *ptLayerCFG, tnsq_gfx_layer_bg_cl_t *ptLayer);`

> Initialize a background color layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to Ensure that the address space occupied by the layer object is always valid during the life cycle, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_bg_cl_cfg_t` structure containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_bg_cl_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_bg_cl_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### background layer initialization

`tnsq_gfx_layer_bg_t *tnsq_gfx_layer_bg_init(tnsq_gfx_layer_bg_cfg_t *ptLayerCFG, tnsq_gfx_layer_bg_t *ptLayer);`

> Initialize a background layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to ensure The address space occupied by the layer object during the life cycle is always valid, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_bg_cfg_t` structure containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_bg_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_bg_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### cell layer initialization

`tnsq_gfx_layer_cell_t *tnsq_gfx_layer_cell_init(tnsq_gfx_layer_cell_cfg_t *ptLayerCFG, tnsq_gfx_layer_cell_t *ptLayer);`

> Initialize a cell layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to Ensure that the address space occupied by the layer object is always valid during the life cycle, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_cell_cfg_t` structure containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_cell_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_cell_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### draw cell

`void tnsq_gfx_layer_cell_draw(tnsq_gfx_layer_cell_t *ptLayer, rt_uint16_t iX, rt_uint16_t iY, rt_uint8_t chOpacity, COLOUR_INT tColor);`

> Through `iX` and `iY`, identify a specific unit in the cell layer and set its opacity and color.

| Parameters | Description |
|:-----|:-----|
| `*ptLayer` | Pointer to the `tnsq_gfx_layer_cell_t` structure, identifying the layer object to be drawn |
| `iX` | The abscissa position of the drawn cell |
| `iY` | The ordinate position of the drawn cell |
| `chOpacity` | Opacity, ranging from 0 to 255, 0 means fully transparent, 255 means opaque |
| `tColor` | The color used for drawing |
| **Return** | **Description** |
| `None` | No return value |

#### user layer initialization

`tnsq_gfx_layer_user_t *tnsq_gfx_layer_user_init(tnsq_gfx_layer_user_cfg_t *ptLayerCFG, tnsq_gfx_layer_user_t *ptLayer);`

> Initialize a user layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to Ensure that the address space occupied by the layer object is always valid during the life cycle, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_user_cfg_t` structure containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_user_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_user_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### draw user cell

`void tnsq_gfx_layer_user_draw(tnsq_gfx_layer_user_t *ptLayer, rt_uint16_t iX, rt_uint16_t iY, rt_uint8_t u7Idx);`

> Through `iX` and `iY`, identify a specific unit in the user layer, and perform the corresponding drawing operation according to `u7Idx` (when the user unit layer is initialized, the corresponding drawing function will be configured).

| Parameters | Description |
|:-----|:-----|
| `*ptLayer` | Pointer to the `tnsq_gfx_layer_user_t` structure, identifying the layer object to be drawn |
| `iX` | The abscissa position of the drawn cell |
| `iY` | The ordinate position of the drawn cell |
| `u7Idx` | Index of user-defined drawing operations, used to distinguish different drawing operations |
| **Return** | **Description** |
| `None` | No return value |

#### text layer initialization

`tnsq_gfx_layer_text_t *tnsq_gfx_layer_text_init(tnsq_gfx_layer_text_cfg_t *ptLayerCFG, tnsq_gfx_layer_text_t *ptLayer);`

> Initialize a text layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to ensure The address space occupied by the layer object during the life cycle is always valid, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_text_cfg_t` structure containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_text_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_text_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### draw text

`rt_int32_t tnsq_gfx_layer_text_printf(tnsq_gfx_layer_text_t *ptLayer, const char *format, ...);`

> Draw text on the specified text layer.

| Parameters | Description |
|:-----|:-----|
| `*ptLayer` | Pointer to the `tnsq_gfx_layer_text_t` structure, identifying the layer object to be drawn |
| `*format` | A format string used to specify the text format to be output. Supports format specifiers similar to the `printf` function |
| `...` | A variable number of arguments, text replacement based on the format specifier in the `format` string |
| **Return** | **Description** |
| `rt_int32_t` | Correct execution, returns the number of characters written into the text |
| `-1` | Error execution |

#### number list layer initialization

`tnsq_gfx_layer_num_t *tnsq_gfx_layer_num_init(tnsq_gfx_layer_num_cfg_t *ptLayerCFG, tnsq_gfx_layer_num_t *ptLayer);`

> Initialize a number list layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to Ensure that the address space occupied by the layer object is always valid during the life cycle, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_num_cfg_t` structure containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_num_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_num_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### get the selected number index

`rt_int8_t tnsq_gfx_layer_num_get_item_idx(tnsq_gfx_layer_num_t *ptLayer);`

> Get the number index selected by the specified number list layer.

| Parameters | Description |
|:-----|:-----|
| `*ptLayer` | Pointer to the `tnsq_gfx_layer_num_t` structure, identifying the layer object from which the current item index is to be obtained |
| **Return** | **Description** |
| `rt_int8_t` | Correct execution, returns the index of the current item |
| `-1` | Error execution |

#### menu layer initialization

`tnsq_gfx_layer_menu_t *tnsq_gfx_layer_menu_init(tnsq_gfx_layer_menu_cfg_t *ptLayerCFG, tnsq_gfx_layer_menu_t *ptLayer);`

> Initialize a menu layer. If `ptLayer` is `RT_NULL` or empty, the corresponding layer object is dynamically allocated and recycled by the engine; if `ptLayer` is not `RT_NULL`, the corresponding layer object is the responsibility of the user, and the user needs to ensure The address space occupied by the layer object during the life cycle is always valid, otherwise an undefined error will result.

| Parameters | Description |
|:-----|:-----|
| `*ptLayerCFG` | Pointer to `tnsq_gfx_layer_menu_cfg_t` structure, containing configuration parameters used to initialize the layer |
| `*ptLayer` | Optional parameter, pointer to the `tnsq_gfx_layer_menu_t` structure, indicating the layer object to be initialized. When `RT_NULL` and empty, it means dynamic initialization, otherwise, it means static initialization |
| **Return** | **Description** |
| `tnsq_gfx_layer_menu_t *` | Initialization successful, returns a pointer to the newly initialized layer object |
| `RT_NULL` | Initialization failed |

#### get the name of the selected menu item

`const char *tnsq_gfx_layer_menu_get_item_name(tnsq_gfx_layer_menu_t *ptLayer);`

> Get the name of the menu item selected by the specified menu layer.

| Parameters | Description |
|:-----|:-----|
| `*ptLayer` | Pointer to the `tnsq_gfx_layer_menu_t` structure, identifying the layer object from which the name of the current item is to be obtained |
| **Return** | **Description** |
| `const char *` | Correctly executed, returns the constant string address of the current menu item name |
| `NULL` | Error execution |

#### get the selected menu item index

`rt_int8_t tnsq_gfx_layer_menu_get_item_idx(tnsq_gfx_layer_menu_t *ptLayer);`

> Get the index of the menu item selected by the specified menu layer.

| Parameters | Description |
|:-----|:-----|
| `*ptLayer` | Pointer to the `tnsq_gfx_layer_menu_t` structure, identifying the layer object to get the current item index |
| **Return** | **Description** |
| `rt_int8_t` | Correct execution, returns the index of the current item |
| `-1` | Error execution |

## PikaPython

### common

#### engine initialization

`def __init__(self): ...`

> Initialize some constants in the engine.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

#### color conversion

`def RGB(r: int, g: int, b: int) -> int: ...`

> Convert RGB colors to the color type used by the engine.

| Parameters | Description |
|:-----|:-----|
| `r` | Integer value, representing the value of the red channel (0-255) |
| `g` | Integer value, representing the value of the green channel (0-255) |
| `b` | Integer value, representing the value of the blue channel (0-255) |
| **Return** | **Description** |
| `int` | The color representation used by the corresponding engine |

### key event class

#### key event class initialization

`def __init__(self): ...`

> Initialize the key event object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

#### update key status

`def update_key(self, timeout:int) -> int: ...`

> Update the button status according to the timeout period.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `timeout` | Integer value, indicating the timeout period, in milliseconds |
| **Return** | **Description** |
| `0` | Correct execution |
| `-1` | Error execution |
| `-2` | Timeout execution |

#### get key direction

`def get_direction(self) -> int: ...`

> Get key direction information.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `KEY_UP` | Up |
| `KEY_DOWN` | Down |
| `KEY_LEFT` | Left |
| `KEY_RIGHT` | Right |
| `KEY_X` | X |
| `KEY_Y` | Y |
| `KEY_A` | A |
| `KEY_B` | B |

#### get key events

`def get_event(self) -> int: ...`

> Get key event information.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `KEY_EVENT_UP` | Key up |
| `KEY_EVENT_DOWN` | Key pressed |
| `KEY_EVENT_PRESSED` | Short press |
| `KEY_EVENT_LONG_PRESSED` | Long press |

### graphics class

#### graphics class initialization

`def __init__(self): ...`

> Initialize the graphics object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

#### apply for refresh

`def refresh(self): ...`

> Request screen refresh.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

#### switch stage

`def switch_stage(self): ...`

> Switch to the next stage.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

### stage class

#### stage class initialization

`def __init__(self): ...`

> Initialize the stage object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

#### register layer

`def register_layer(self, layer: object) -> int: ...`

> Register the specified layer object into the stage.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `layer` | The layer object to be registered in the stage |
| **Return** | **Description** |
| `int` | The unique ID that represents the layer |

#### remove layer

`def remove_layer(self, layerID: int): ...`

> Remove the layer identified by the unique ID in the stage.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `layerID` | Unique ID that identifies the layer to be removed |
| **Return** | **Description** |
| `None` | No return value |

#### make layer visible

`def visible_layer(self, layerID: int): ...`

> Make the layer identified by the unique ID visible in the stage.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `layerID` | Unique ID that identifies the layer to be operated on |
| **Return** | **Description** |
| `None` | No return value |

#### make layer invisible

`def invisible_layer(self, layerID: int): ...`

> Make the layer identified by the unique ID invisible in the stage.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `layerID` | Unique ID that identifies the layer to be operated on |
| **Return** | **Description** |
| `None` | No return value |

### screen class

#### screen class initialization

`def __init__(self): ...`

> Initialize the screen object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `None` | No return value |

#### get screen width

`def width(self) -> int: ...`

> Get the width of screen.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `int` | width of screen |

#### get screen height

`def height(self) -> int: ...`

> Get the height of screen.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `int` | height of screen |

### region class

#### region class initialization

`def __init__(self, hwX: int, hwY: int, hwWidth: int, hwHeight: int): ...`

> Initialize the screen object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `hwX` | x starting coordinate of region |
| `hwY` | y starting coordinate of region |
| `hwWidth` | width of region |
| `hwHeight` | The height of the region |
| **Return** | **Description** |
| `None` | No return value |

### border opacity class

#### border opacity class initialization

`def __init__(self, left: int, right: int, top: int, bottom: int): ...`

> Initialize the border opacity object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `left` | The opacity of the left side, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| `right` | The opacity of the right, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| `top` | The opacity of the top, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| `bottom` | The opacity of the bottom, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| **Return** | **Description** |
| `None` | No return value |

### corner opacity class

#### corner opacity class initialization

`def __init__(self, leftTop: int, rightTop: int, rightBottom: int, leftBottom: int): ...`

> Initialize the corner opacity object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `leftTop` | The opacity of the upper left corner, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| `rightTop` | The opacity of the upper right corner, ranging from 0 to 255, 0 means fully transparent, 255 means opaque |
| `rightBottom` | The opacity of the lower right corner, ranging from 0 to 255, 0 means fully transparent, 255 means opaque |
| `leftBottom` | The opacity of the lower left corner, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| **Return** | **Description** |
| `None` | No return value |

### background color layer class

#### background color layer class initialization

`def __init__(self, type: int, color: int, opacity: int, region: Region, borderOpacity: BorderOpacity, cornerOpacity: CornerOpacity): ...`

> Initialize the corner opacity object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `type` | The type of background color layer, the options are: `BG_CL_NORMAL`, `BG_CL_BOX`, `BG_CL_BORDER` |
| `color` | background color |
| `opacity` | The opacity of the background color, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| `region` | The position and size of the background color layer |
| `borderOpacity` | When `type` is `BG_CL_BORDER`, specify border opacity |
| `cornerOpacity` | When `type` is `BG_CL_BORDER`, specify corner opacity |
| **Return** | **Description** |
| `None` | No return value |

### cell layer class

#### cell layer class initialization

`def __init__(self, hwXCount: int, hwYCount: int): ...`

> Initialize the cell layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `hwXCount` | Number of cells in x direction |
| `hwYCount` | Number of cells in y direction |
| **Return** | **Description** |
| `None` | No return value |

#### draw cell

`def draw_cell(self, hwX: int, hwY: int, color: int, opacity: int): ...`

> Draw the specified cell in the cell layer.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `hwX` | The abscissa position of the drawn cell |
| `hwY` | The ordinate position of the drawn cell |
| `color` | The color used for drawing |
| `opacity` | Opacity, ranging from 0 to 255, 0 means completely transparent, 255 means opaque |
| **Return** | **Description** |
| `None` | No return value |

### user layer class

#### user layer class initialization

`def __init__(self, hwXCount: int, hwYCount: int): ...`

> Initialize user layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `hwXCount` | Number of cells in x direction |
| `hwYCount` | Number of cells in y direction |
| **Return** | **Description** |
| `None` | No return value |

#### draw user cell

`def draw_userMap(self, hwX: int, hwY: int, idx: int): ...`

> Draws the specified cell in the user layer.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `hwX` | The abscissa position of the drawn cell |
| `hwY` | The ordinate position of the drawn cell |
| `idx` | The index of the system's custom drawing operation, used to distinguish different drawing operations (the specific drawing function is weakly defined. If the user wants to customize the drawing operation, he can redefine the drawing function) |
| **Return** | **Description** |
| `None` | No return value |

### text layer class

#### text layer class initialization

`def __init__(self, fontType: int, color: int, opacity: int, region: Region): ...`

> Initialize the text layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `fontType` | Font type, options are: `TEXT_FONT_6X8`, `TEXT_FONT_16X24`, `TEXT_FONT_A2_DIGITS_ONLY`, `TEXT_FONT_A4_DIGITS_ONLY`, `TEXT_FONT_A8_DIGITS_ONLY` |
| `color` | The color of the text |
| `opacity` | The opacity of the text, ranging from 0 to 255, 0 means fully transparent, 255 means opaque |
| `region` | The position and size of the text layer |
| **Return** | **Description** |
| `None` | No return value |

#### print string

`def print_str(self, format: str, string: str): ...`

> Draw a string into the text layer.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `format` | A format string used to specify the text format to be output. Supports format specifiers similar to the `printf` function |
| `string` | String parameters |
| **Return** | **Description** |
| `None` | No return value |

#### print number

`def print_num(self, format: str, number: int): ...`

> Draw numbers into the text layer.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `format` | A format string used to specify the text format to be output. Supports format specifiers similar to the `printf` function |
| `number` | Numeric parameter |
| **Return** | **Description** |
| `None` | No return value |

### number list layer class

#### number list layer class initialization

`def __init__(self, number:int, bgColor: int, textColor: int): ...`

> Initialize the number list layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `number` | The number of list items in the number list |
| `bgColor` | Background color of list items |
| `textColor` | The text color of the list item |
| **Return** | **Description** |
| `None` | No return value |

#### get the index of the selected list item

`def get_idx(self) -> int: ...`

> Get the index of the selected list item in the number list layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `int` | Correct execution, returns the selected index item |
| `-1` | Error execution |

### item format class

#### item format class initialization

`def __init__(self, boxColor: int, textColor: int, opacity: int): ...`

> Initialize the item format class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `boxColor` | The background color of item |
| `textColor` | The text color of item |
| `opacity` | The opacity of the text, ranging from 0 to 255, 0 means fully transparent, 255 means opaque |
| **Return** | **Description** |
| `None` | No return value |

### menu layer class

#### menu layer class initialization

`def __init__(self, strTable: tuple, fontType: int, itemWidth: int, itemHeight: int, itemNormal: ItemFormat, itemSelect: ItemFormat): ...`

> Initialize menu layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| `strTable` | A table of menu item names stored in `tuple` form |
| `fontType` | Font type, options are: `TEXT_FONT_6X8`, `TEXT_FONT_16X24`, `TEXT_FONT_A2_DIGITS_ONLY`, `TEXT_FONT_A4_DIGITS_ONLY`, `TEXT_FONT_A8_DIGITS_ONLY` |
| `itemWidth` | Width of menu item |
| `itemHeight` | The height of the menu item |
| `itemNormal` | The appearance of the menu item when not selected |
| `itemSelect` | The appearance of the menu item when selected |
| **Return** | **Description** |
| `None` | No return value |

#### get the index of the selected list item

`def get_idx(self) -> int: ...`

> Get the index of the selected list item in the menu layer class object.

| Parameters | Description |
|:-----|:-----|
| `self` | A reference to the object itself |
| **Return** | **Description** |
| `int` | Correct execution, returns the selected index item |
| `-1` | Error execution |