#ifndef __SNAKE_H
#define __SNAKE_H

#include <stdint.h>
#include "arm_2d.h"
#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

struct Point
{
	 uint8_t x;
	 uint8_t y;
};

typedef struct Snake {
	 struct Point loc;
	 struct Snake *next;
}Snake;

typedef struct Game_State_Info {
	uint16_t score;
	uint16_t length;
	//uint16_t speed;
}Game_State_Info;

typedef enum {
	foreground = 0x00,
	background = 0x01,
} DrawSenceSelection;

typedef enum {
	Snake_Game_NO_ERR = 0x00,
	Snake_Game_Error = 0x01,
}SnakeGameStatus;

// 脏矩阵要求常量作为size的参数，此处用字体的高度计算会报编译错
// #define STATE_VIEW_HEIGHT ARM_2D_FONT_6x8.use_as__arm_2d_font_t.tCharSize.iHeight*2
#define STATE_VIEW_HEIGHT 16

#define SNAKE_INITIAL_LOC_X 3
#define SNAKE_INITIAL_LOC_Y	3

#define SNAKE_WIDTH_PIXELS 	35
#define SNAKE_HEIGHT_PIXELS 	35

#define HORIZONTAL_NUM_MAX 	(__GLCD_CFG_SCEEN_WIDTH__ / SNAKE_WIDTH_PIXELS)
#define VERTICAL_NUM_MAX		((__GLCD_CFG_SCEEN_HEIGHT__ - STATE_VIEW_HEIGHT) / SNAKE_HEIGHT_PIXELS)

#define WIDTH_PIXELS_USED_BY_GAME		(HORIZONTAL_NUM_MAX * SNAKE_WIDTH_PIXELS)
#define HEIGHT_PIXELS_USED_BY_GAME	(VERTICAL_NUM_MAX * SNAKE_HEIGHT_PIXELS)

// Game_State_Info getGameState(void);

SnakeGameStatus DrawStartGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground);
SnakeGameStatus DrawEndGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground);
SnakeGameStatus DrawRunningGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground);

//void CreateBoard(void);
SnakeGameStatus InitGame(const arm_2d_tile_t *ptTile);
SnakeGameStatus CreateSnake(const arm_2d_tile_t *ptTile, Snake *body);
SnakeGameStatus CreateFruit(const arm_2d_tile_t *ptTile);

#endif