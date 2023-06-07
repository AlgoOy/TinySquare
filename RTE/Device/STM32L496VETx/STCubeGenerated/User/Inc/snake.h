#ifndef __SNAKE_H
#define __SNAKE_H

#include <stdint.h>

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
}Game_State_Info;

typedef enum {
	Snake_Game_NO_ERR = 0,
	Snake_Game_Error = 1,
}SnakeGameStatus;

#define STATE_VIEW_HEIGHT ARM_2D_FONT_6x8.use_as__arm_2d_font_t.tCharSize.iHeight*2

#define SNAKE_INITIAL_LOC_X 3
#define SNAKE_INITIAL_LOC_Y	3

#define SNAKE_WIDTH_PIXELS 	35
#define SNAKE_HEIGHT_PIXELS 	35

#define HORIZONTAL_NUM_MAX 	(__GLCD_CFG_SCEEN_WIDTH__ / SNAKE_WIDTH_PIXELS)
#define VERTICAL_NUM_MAX		((__GLCD_CFG_SCEEN_HEIGHT__ - STATE_VIEW_HEIGHT) / SNAKE_HEIGHT_PIXELS)

#define WIDTH_PIXELS_USED_BY_GAME		(HORIZONTAL_NUM_MAX * SNAKE_WIDTH_PIXELS)
#define HEIGHT_PIXELS_USED_BY_GAME	(VERTICAL_NUM_MAX * SNAKE_HEIGHT_PIXELS)

//int speed;

Game_State_Info getGameState(void);

void DrawStartGamePanel(void);
void DrawEndGamePanel(void);
void DrawRunningGamePanel(void);

void CreateBoard(void);
SnakeGameStatus CreateSnake(void);
SnakeGameStatus CreateFruit(void);

#endif