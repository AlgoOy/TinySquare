/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#include "tnsq_snake.h"
#include "tiny_square.h"
#include "uart.h"
 
#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wunused-function"
#   pragma clang diagnostic ignored "-Wmissing-declarations"  
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_IAR__
#   pragma diag_suppress=Pa089,Pe188,Pe177,Pe174
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wunused-value"
#endif

#undef this
#define this (*ptThis)
    
#define FGCellsXCount   10
#define FGCellsYCount   10

#define OBSTACLE_NUM    3

typedef enum {
    GAME_LOW_SPEED  = 400,
    GAME_HIGH_SPPED = 200,
} tnsq_snake_game_speed_t;

typedef struct {
	rt_uint8_t x;
	rt_uint8_t y;
} tnsq_snake_point_t;

struct {
	tnsq_snake_point_t bodyloc[FGCellsXCount*FGCellsYCount];
	rt_uint16_t length;
	enum {
		Up = 0x00,
		Down = 0x01,
		Left = 0x02,
		Right = 0x03,
	} direction;
    tnsq_snake_game_speed_t tSpeed;
} snake = {0};

struct {
	tnsq_snake_point_t loc;
	enum {
		notExist = 0x00,
		Exist = 0x01,
	} state;
} fruit = {0};

struct {
    tnsq_snake_point_t loc[OBSTACLE_NUM];
} obstacle = {0};

static tnsq_gfx_cell_t s_tFGCells[FGCellsXCount * FGCellsXCount] = {0};
static rt_uint8_t s_UserMap[FGCellsXCount * FGCellsXCount] = {0};

static rt_bool_t bls_map[FGCellsXCount * FGCellsYCount] = {0};

static tnsq_gfx_stage_t *_tnsq_snake_stage_init(void)
{
    disp_adapter0_init();
    tnsq_gfx_stage_cfg_t tGameStageCFG = (tnsq_gfx_stage_cfg_t) {
        .ptDispAdapter = (tnsq_gfx_disp_adapter_t) {
            .ptPlayer = &DISP0_ADAPTER,
            .ptPlayerTask = disp_adapter0_task,
        },
    };
    tnsq_gfx_stage_t *ptGameStage = tnsq_gfx_stage_init(&tGameStageCFG);
    if (ptGameStage == NULL)
    {
        /* error handle */
        UART_Print("game stage init failed");
        return NULL;
    }
    else
    {
        return ptGameStage;
    }
}

extern const arm_2d_tile_t c_tileFruitRGB565;
extern const arm_2d_tile_t c_tileFruitMask;
extern const arm_2d_tile_t c_tileSnakeBodyRGB565;
extern const arm_2d_tile_t c_tileSnakeBodyMask;
void UserMapFunc(rt_uint8_t idx, arm_2d_tile_t const *ptTile, arm_2d_region_t const *ptRegion)
{
    if (idx == 1)
    {
        arm_2d_tile_copy_with_src_mask(
            &c_tileFruitRGB565,
            &c_tileFruitMask,
            ptTile,
            ptRegion,
            ARM_2D_CP_MODE_COPY
        );
    }
    else if (idx == 2)
    {
        arm_2d_tile_copy_with_src_mask(
            &c_tileSnakeBodyRGB565,
            &c_tileSnakeBodyMask,
            ptTile,
            ptRegion,
            ARM_2D_CP_MODE_COPY
        );
    }
    else
    {
        arm_2d_fill_colour_with_opacity(
            ptTile, 
            ptRegion,
            (__arm_2d_color_t){GLCD_COLOR_BLUE},
            255
        );
    }
}

extern const arm_2d_tile_t c_tilebg_mapRGB565;
extern const arm_2d_tile_t c_tilebg_mapMask;
static void _tnsq_snake_layer_init(tnsq_gfx_stage_t *ptGameStage)
{
    tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = (tnsq_gfx_layer_bg_cl_cfg_t) {
        .chOpacity = 255,
        .ptBackGroundColorMask = NULL,
        .tRegion = (arm_2d_region_t) {
            .tLocation = (arm_2d_location_t){
                .iX = 0,
                .iY = 0,
            },
            .tSize = (arm_2d_size_t) {
                .iWidth = tnsq_gfx_get_screen_size(&DISP0_ADAPTER).iWidth,
                .iHeight = tnsq_gfx_get_screen_size(&DISP0_ADAPTER).iHeight,
            },
        },
        .tColor = (__arm_2d_color_t){GLCD_COLOR_WHITE},
    };
    tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
    
    tnsq_gfx_layer_bg_cfg_t tGameBGCFG = (tnsq_gfx_layer_bg_cfg_t) {
        .ptBackGround = &c_tilebg_mapRGB565,
        .ptBackGroundMask = &c_tilebg_mapMask,
        .tRegion = (arm_2d_region_t) {
            .tLocation = (arm_2d_location_t){
                .iX = 0,
                .iY = 0,
            },
            .tSize = (arm_2d_size_t) {
                .iWidth = tnsq_gfx_get_screen_size(&DISP0_ADAPTER).iWidth,
                .iHeight = tnsq_gfx_get_screen_size(&DISP0_ADAPTER).iHeight,
            },
        },
    };
    tnsq_gfx_layer_bg_t *ptGameBG = tnsq_gfx_layer_bg_init(&tGameBGCFG);
    
    tnsq_gfx_layer_user_cfg_t tGameUserCFG = (tnsq_gfx_layer_user_cfg_t) {
        .hwXCount = FGCellsXCount,
        .hwYCount = FGCellsYCount,
        .pchUserMap = s_UserMap,
        .ptFunc = UserMapFunc,
    };
    tnsq_gfx_layer_user_t *ptGameUser = tnsq_gfx_layer_user_init(&tGameUserCFG);
    
    tnsq_gfx_layer_cell_cfg_t tGameFGLayerCFG = (tnsq_gfx_layer_cell_cfg_t) {
        .hwXCount = FGCellsXCount,
        .hwYCount = FGCellsYCount,
        .ptCells = s_tFGCells,
    };
    tnsq_gfx_layer_cell_t *ptGameFGLayer = tnsq_gfx_layer_cell_init(&tGameFGLayerCFG);
    
    tnsq_gfx_register_layer_to_stage(ptGameStage, ptGameBGCL);
    tnsq_gfx_register_layer_to_stage(ptGameStage, ptGameBG);
    tnsq_gfx_register_layer_to_stage(ptGameStage, ptGameUser);
    tnsq_gfx_register_layer_to_stage(ptGameStage, ptGameFGLayer);
}

static rt_uint16_t _tnsq_pos_cal(tnsq_snake_point_t loc, rt_uint16_t YCount)
{
	return (loc.x-1) * YCount + (loc.y-1);
}

static void draw_cell(tnsq_gfx_cell_t *ptCells, rt_uint16_t pos, rt_uint8_t chOpacity, __arm_2d_color_t tColor)
{
	ptCells[pos].blsDirty = RT_TRUE;
	ptCells[pos].chOpacity = chOpacity;
	ptCells[pos].tColor = tColor;
}

static void _tnsq_draw_fg(rt_uint16_t pos, rt_uint8_t chOpacity, __arm_2d_color_t tColor)
{
    draw_cell(s_tFGCells, pos, chOpacity, tColor);
}

static void _tnsq_snake_obstacle_init(void)
{
    for (int i = 0; i < OBSTACLE_NUM; i ++)
    {
        do
        {
            srand((unsigned) HAL_GetTick());
            obstacle.loc[i].x = (uint8_t)rand() % FGCellsXCount + 1;
            obstacle.loc[i].y = (uint8_t)rand() % FGCellsYCount + 1;
        } while (bls_map[_tnsq_pos_cal(obstacle.loc[i], FGCellsYCount)] == RT_TRUE);
        
        bls_map[_tnsq_pos_cal(obstacle.loc[i], FGCellsYCount)] = RT_TRUE;
        
        s_UserMap[_tnsq_pos_cal(obstacle.loc[i], FGCellsYCount)] = i;
    }
}

static void _tnsq_snake_create_fruit(void)
{
    if (fruit.state != Exist)
    {
        do
        {
            srand((unsigned) HAL_GetTick());
            fruit.loc.x = (uint8_t)rand() % FGCellsXCount + 1;
            fruit.loc.y = (uint8_t)rand() % FGCellsYCount + 1;
        } while (bls_map[_tnsq_pos_cal(fruit.loc, FGCellsYCount)] == RT_TRUE);
        
        fruit.state = Exist;
        bls_map[_tnsq_pos_cal(fruit.loc, FGCellsYCount)] = RT_TRUE;
        
        _tnsq_draw_fg(_tnsq_pos_cal(fruit.loc, FGCellsYCount), 255, FRUIT_COLOR);
    }
}

static void _tnsq_snake_fg_init(void)
{
    do
    {
        snake.length = 1;
        
        snake.bodyloc[snake.length-1].x = snake.bodyloc[0].x = FGCellsXCount/4;
        snake.bodyloc[snake.length-1].y = snake.bodyloc[0].y = FGCellsXCount/4;
        
        bls_map[_tnsq_pos_cal(snake.bodyloc[0], FGCellsYCount)] = RT_TRUE;
        
        _tnsq_draw_fg(_tnsq_pos_cal(snake.bodyloc[0], FGCellsYCount), 255, SNAKE_COLOR);
        
        snake.direction = Right;
        
        snake.tSpeed = GAME_LOW_SPEED;
    } while (0);
    
    do
    {
        _tnsq_snake_create_fruit();
    } while (0);
}
    
static void _tnsq_snake_game_init(void)
{
    tnsq_gfx_stage_t *ptGameStage = _tnsq_snake_stage_init();
    if (ptGameStage != NULL)
    {
        _tnsq_snake_layer_init(ptGameStage);
    }
    
    _tnsq_snake_obstacle_init();
    _tnsq_snake_fg_init();
}

static void _tnsq_snake_game_evt_handler(void)
{
    tnsq_evt_key_t tKey = {0};
    while(tnsq_evt_itc_get(&tKey, RT_WAITING_NO) != -RT_ETIMEOUT)
    {
        if(tKey.tEvent != TNSQ_EVT_KEY_EVENT_PRESSED && tKey.tEvent != TNSQ_EVT_KEY_EVENT_LONG_PRESSED)
        {
            continue;
        }
        else
        {
            switch (tKey.tDirection) 
            {
            case TNSQ_EVT_KEY_DERECTION_UP:
                if (snake.direction != Down) 
                {
                    snake.direction = Up;
                }
                break;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                if (snake.direction != Up) 
                {
                    snake.direction = Down;
                }
                break;
            case TNSQ_EVT_KEY_DERECTION_LEFT:
                if (snake.direction != Right) 
                {
                    snake.direction = Left;
                }
                break;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                if (snake.direction != Left) 
                {
                    snake.direction = Right;
                }
                break;
            default:
                break;
            }
            if (tKey.tEvent == TNSQ_EVT_KEY_EVENT_PRESSED)
            {
                snake.tSpeed = GAME_LOW_SPEED;
            }
            else
            {
                snake.tSpeed = GAME_HIGH_SPPED;
            }
        }
    }
}

static rt_bool_t _tnsq_snake_not_hit_obstacle(tnsq_snake_point_t newHead)
{
    for (int i = 0; i < OBSTACLE_NUM; i ++)
    {
        if (newHead.x == obstacle.loc[i].x && newHead.y == obstacle.loc[i].y)
        {
            return RT_FALSE;
        }
    }
    return RT_TRUE;
}

static void _tnsq_snake_game_logic(void)
{  
    tnsq_snake_point_t newHead = (tnsq_snake_point_t){
        .x = snake.bodyloc[snake.length-1].x,
        .y = snake.bodyloc[snake.length-1].y,
    };
    
    _tnsq_snake_game_evt_handler();
    switch (snake.direction)
    {
    case Up:
        newHead.x --;
        break;
    case Down:
        newHead.x ++;
        break;
    case Left:
        newHead.y --;
        break;
    case Right:
        newHead.y ++;
        break;
    default:
        break;
    }
    
    if(newHead.y == FGCellsYCount)
    {
        newHead.x ++;
        newHead.y = 0;
    }
    if(newHead.x == FGCellsXCount)
    {
        
    }
    
    if (newHead.x == fruit.loc.x && newHead.y == fruit.loc.y)
    {
        fruit.state = notExist;
        _tnsq_snake_create_fruit();
        
        snake.length ++;
        snake.bodyloc[snake.length - 1] = (tnsq_snake_point_t) {
            .x = newHead.x,
            .y = newHead.y,
        };
        _tnsq_draw_fg(_tnsq_pos_cal(snake.bodyloc[snake.length - 1], FGCellsYCount), 255, SNAKE_COLOR);
    }
    else if (newHead.x < 1 || newHead.y < 1 || newHead.x > FGCellsXCount || newHead.y > FGCellsYCount)
    {
        UART_Print("hit the wall\n");
        while (1);
    }
    else if (_tnsq_snake_not_hit_obstacle(newHead) == RT_FALSE)
    {
        UART_Print("hit the obstacle\n");
        while (1);
    }
    else
    {
        bls_map[_tnsq_pos_cal(snake.bodyloc[0], FGCellsYCount)] = RT_FALSE;
        _tnsq_draw_fg(_tnsq_pos_cal(snake.bodyloc[0], FGCellsYCount), 255, BG_COLOR);
        
        for (int i = 1; i < snake.length; i ++) {
			if(newHead.x == snake.bodyloc[i].x && newHead.y == snake.bodyloc[i].y) {
				UART_Print("hit it self\n");
				while(1);
			}
            snake.bodyloc[i - 1] = (tnsq_snake_point_t) {
                .x = snake.bodyloc[i].x,
                .y = snake.bodyloc[i].y,
            };
		}
        snake.bodyloc[snake.length - 1] = (tnsq_snake_point_t) {
            .x = newHead.x,
            .y = newHead.y,
        };
        
        bls_map[_tnsq_pos_cal(snake.bodyloc[snake.length - 1], FGCellsYCount)] = RT_TRUE;
        _tnsq_draw_fg(_tnsq_pos_cal(snake.bodyloc[snake.length - 1], FGCellsYCount), 255, SNAKE_COLOR);
    }
    
    rt_thread_mdelay(snake.tSpeed);
}
    
void tnsq_snake_task_entry(void *ptParam)
{
    _tnsq_snake_game_init();
    while (1)
    {
        tnsq_gfx_apply_for_refresh();
        _tnsq_snake_game_logic();
    }
}
    
#if 0
void tnsq_snake_task_entry(void *ptParam)
{
    tnsq_evt_key_t tEvtKey = {0};
    while (1)
    {
        tnsq_evt_itc_get(&tEvtKey, RT_WAITING_FOREVER);
        switch (tEvtKey.tEvent) 
        {
        case TNSQ_EVT_KEY_EVENT_DOWN:
            UART_Print("key down\n");
            switch (tEvtKey.tDirection)
            {
            case TNSQ_EVT_KEY_DERECTION_UP:
                UART_Print("DERECTION_UP\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                UART_Print("DERECTION_DOWN\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_LEFT:
                UART_Print("DERECTION_LEFT\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                UART_Print("DERECTION_RIGHT\n");
                break;
            default:
                break;
            }
            break;
        case TNSQ_EVT_KEY_EVENT_UP:
            UART_Print("key up\n");
            switch (tEvtKey.tDirection)
            {
            case TNSQ_EVT_KEY_DERECTION_UP:
                UART_Print("DERECTION_UP\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                UART_Print("DERECTION_DOWN\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_LEFT:
                UART_Print("DERECTION_LEFT\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                UART_Print("DERECTION_RIGHT\n");
                break;
            default:
                break;
            }
            break;
        case TNSQ_EVT_KEY_EVENT_PRESSED:
            UART_Print("key pressed\n");
            switch (tEvtKey.tDirection)
            {
            case TNSQ_EVT_KEY_DERECTION_UP:
                UART_Print("DERECTION_UP\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                UART_Print("DERECTION_DOWN\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_LEFT:
                UART_Print("DERECTION_LEFT\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                UART_Print("DERECTION_RIGHT\n");
                break;
            default:
                break;
            }
            break;
        case TNSQ_EVT_KEY_EVENT_LONG_PRESSED:
            UART_Print("key long pressed\n");
            switch (tEvtKey.tDirection)
            {
            case TNSQ_EVT_KEY_DERECTION_UP:
                UART_Print("DERECTION_UP\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                UART_Print("DERECTION_DOWN\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_LEFT:
                UART_Print("DERECTION_LEFT\n");
                break;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                UART_Print("DERECTION_RIGHT\n");
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    
}
#endif
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
