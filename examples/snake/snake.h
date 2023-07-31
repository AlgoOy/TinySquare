#ifndef __SNAKE_H
#define __SNAKE_H

#include <stdint.h>
#include "arm_2d.h"
#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

typedef enum {
	foreground = 0x00,
	background = 0x01,
} DrawSenceSelection;

typedef enum {
	Snake_Game_No_Error = 0x00,
	Snake_Game_Error = 0x01,
	Snake_Game_No_Memory = 0x02,
}SnakeGameStatus;

typedef enum {
	Up = 0x00,
	Down = 0x01,
	Left = 0x02,
	Right = 0x03,
} Direction;

typedef enum {
	high_speed = 100,
	middle_speed = 200,
	// ö������Ϊʲô���ֵ��255��2�ֽڣ�������255�ͻ������ô���ó�4�ֽ�
	low_speed = 255,
}	Game_Speed;

struct Point
{
	 uint8_t x;
	 uint8_t y;
};

typedef struct Snake{
	 struct Point loc;
	 struct Snake *next;
}Snake;

typedef struct Fruit {
	struct Point loc;
	enum FruitState{notExist, exist} state;
}Fruit;

typedef struct Game_State_Info {
	uint16_t score;
	uint16_t length;
	enum GameState {begin, end_wall, end_self} state;
	Game_Speed speed;
}Game_State_Info;

// �����Ҫ������Ϊsize�Ĳ������˴�������ĸ߶ȼ���ᱨ�����
// #define STATE_VIEW_HEIGHT ARM_2D_FONT_6x8.use_as__arm_2d_font_t.tCharSize.iHeight*2
#define STATE_VIEW_HEIGHT 16

#define SNAKE_INITIAL_LOC_X 3
#define SNAKE_INITIAL_LOC_Y	3

#define SNAKE_WIDTH_PIXELS 	10
#define SNAKE_HEIGHT_PIXELS 	10

#define HORIZONTAL_NUM_MAX 	(__GLCD_CFG_SCEEN_WIDTH__ / SNAKE_WIDTH_PIXELS)
#define VERTICAL_NUM_MAX		((__GLCD_CFG_SCEEN_HEIGHT__ - STATE_VIEW_HEIGHT) / SNAKE_HEIGHT_PIXELS)

#define WIDTH_PIXELS_USED_BY_GAME		(HORIZONTAL_NUM_MAX * SNAKE_WIDTH_PIXELS)
#define HEIGHT_PIXELS_USED_BY_GAME	(VERTICAL_NUM_MAX * SNAKE_HEIGHT_PIXELS)

#define Cal_Loc_X(x)		(x * SNAKE_WIDTH_PIXELS + (__GLCD_CFG_SCEEN_WIDTH__ - WIDTH_PIXELS_USED_BY_GAME) / 2)
#define Cal_Loc_Y(y)		(y * SNAKE_HEIGHT_PIXELS + STATE_VIEW_HEIGHT)

Game_State_Info getGameState(void);

SnakeGameStatus DrawStartGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground);
SnakeGameStatus DrawEndGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground);
SnakeGameStatus DrawRunningGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground);
SnakeGameStatus DrawGameElements(const arm_2d_tile_t *ptTile);

//void CreateBoard(void);
SnakeGameStatus InitGame(void);
SnakeGameStatus QuitGame(bool *state);
SnakeGameStatus GameLogic(void);

#endif