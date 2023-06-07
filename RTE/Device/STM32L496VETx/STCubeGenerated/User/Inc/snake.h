#ifndef __SNAKE_H
#define __SNAKE_H

#include "stdint.h"

// struct Point
// {
//     uint8_t x;
//     uint8_t y;
// };

// typedef struct Snake Snake;

// struct Snake {
//     int size;
//     int direction;
//     int speed;
//     struct Point location;
// }

typedef struct Game_State_Info {
	uint16_t score;
	uint16_t length;
}Game_State_Info;

#define STATE_VIEW_HEIGHT ARM_2D_FONT_6x8.use_as__arm_2d_font_t.tCharSize.iHeight*2

#define SNAKE_WIDTH 	35
#define SNAKE_HEIGHT 	35

#define WIDTH_PIXELS_USED_BY_GAME		((__GLCD_CFG_SCEEN_WIDTH__ / SNAKE_WIDTH) * SNAKE_WIDTH)
#define HEIGHT_PIXELS_USED_BY_GAME	(((__GLCD_CFG_SCEEN_HEIGHT__ - STATE_VIEW_HEIGHT) / SNAKE_HEIGHT) * SNAKE_HEIGHT)

Game_State_Info getGameState(void);

void DrawStartGamePanel(void);
void DrawEndGamePanel(void);
void DrawRunningGamePanel(void);

void CreateBoard(void);
void CreateSnake(void);
void CreateFruit(void);

#endif