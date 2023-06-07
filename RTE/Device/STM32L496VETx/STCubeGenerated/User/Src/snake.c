#include <stdlib.h>
#include <time.h>
#include "../Inc/snake.h"
#include "arm_2d.h"
#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

static Game_State_Info gameState= {0};

Game_State_Info getGameState(void) {
	return gameState;
}

SnakeGameStatus CreateSNAKE(void) {
		
	return Snake_Game_NO_ERR;
}

SnakeGameStatus CreateFruit(void) {
	srand(time(NULL));
	uint8_t snake_x = (uint8_t)rand() % HORIZONTAL_NUM_MAX, snake_y = (uint8_t)rand() % VERTICAL_NUM_MAX;
	
	
	return Snake_Game_NO_ERR;
}

void DrawStartGamePanel(void) {

}

void DrawEndGamePanel(void) {
	
}

void DrawRunningGamePanel(void) {
	// 设置背景颜色
}

void InitGame(void) {
    
}