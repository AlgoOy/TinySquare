#include <stdlib.h>
#include "snake_v2.h"
#include "rtthread.h"
#include "layer_management.h"

static cell_t cells[CellsXCount * CellsYCount] = {0};
static layer_t layer = {CellsXCount, CellsYCount, cells};
static rt_uint8_t bls_map[CellsXCount * CellsYCount] = {0};

typedef struct {
	rt_uint8_t x;
	rt_uint8_t y;
} point_t;

struct {
	point_t bodyloc[CellsXCount*CellsYCount];
	rt_uint16_t length;
	enum {
		Up = 0x00,
		Down = 0x01,
		Left = 0x02,
		Right = 0x03,
	} direction;
} snake = {0};

struct {
	point_t loc;
	enum {
		Exist = 0x00,
		notExist = 0x01,
	} state;
} fruit = {0};

static rt_uint16_t pos_cal(point_t loc) {
	return (loc.x-1) * CellsYCount + (loc.y-1);
}



static void draw_cell(rt_uint16_t pos, rt_uint8_t chOpacity, __arm_2d_color_t tColor) {
	layer.ptCells[pos].blsDirty = 1;
	layer.ptCells[pos].chOpacity = chOpacity;
	layer.ptCells[pos].tColor = tColor;
}

static void clear_cell(rt_uint16_t pos) {
	draw_cell(pos, 255, (__arm_2d_color_t){GLCD_COLOR_WHITE});
}

static void draw_snake_body (rt_uint16_t pos) {
	draw_cell(pos, 255, (__arm_2d_color_t){GLCD_COLOR_BLACK});
}

static void draw_fruit (rt_uint16_t pos) {
	draw_cell(pos, 255, (__arm_2d_color_t){GLCD_COLOR_RED});
}

static void create_fruit(void) {
	if (fruit.state != Exist) {
		do {
			srand(arm_2d_helper_get_system_timestamp());
			fruit.loc.x = (uint8_t)rand() % CellsXCount;
			fruit.loc.y = (uint8_t)rand() % CellsYCount;
		} while(bls_map[pos_cal(fruit.loc)] == 1);
		
		fruit.state = Exist;
		bls_map[pos_cal(fruit.loc)] = 1;
		
		draw_fruit(pos_cal(fruit.loc));
	}
}

static void snake_init(void) {
	snake.length = 1;
	
	snake.bodyloc[snake.length-1].x = snake.bodyloc[0].x = CellsXCount/4;
	snake.bodyloc[snake.length-1].y = snake.bodyloc[0].y = CellsYCount/4;
	
	bls_map[pos_cal(snake.bodyloc[snake.length-1])] = 1;
	draw_snake_body(pos_cal(snake.bodyloc[snake.length-1]));
	
	snake.direction = Right;
}

static void game_init(void) {
	register_layer(&layer);
	
	for(int i = 0;i < CellsXCount * CellsYCount; i++) {
		clear_cell(i);
	}
	
	snake_init();
	create_fruit();
}

//! todo:modify it to event FIFO
#include "key.h"
extern Key_State check_key(void);
static void set_snake_direction(void) {
	switch(check_key()) {
		case key_0:
			if (snake.direction != Left) {
				snake.direction = Right;
			}
			break;
		case key_1:
			if (snake.direction != Up) {
				snake.direction = Down;
			}
			break;
		case key_2:
			if (snake.direction != Right) {
				snake.direction = Left;
			}
			break;
		case key_3:
			if (snake.direction != Down) {
				snake.direction = Up;
			}
			break;
		case no_key_press:
		default:
			break;
	}
}

static void game_logic(void){
	point_t newHead = {0};
	memcpy(&newHead, &snake.bodyloc[snake.length-1], sizeof(point_t));
	
	set_snake_direction();
	switch(snake.direction) {
		case Up:
			newHead.y--;
			break;
		case Down:
			newHead.y++;
			break;
		case Left:
			newHead.x--;
			break;
		case Right:
			newHead.x++;
			break;
		default:
			break;
	}
	if(newHead.x == fruit.loc.x && newHead.y == fruit.loc.y) {
		fruit.state = notExist;
		create_fruit();
		
		snake.length++;
		memcpy(&snake.bodyloc[snake.length-1], &newHead, sizeof(point_t));
		draw_snake_body(pos_cal(snake.bodyloc[snake.length-1]));
	} else if (newHead.x < 1 || newHead.y < 1 || 
			newHead.x > CellsXCount || newHead.y > CellsYCount) {
		// hit wall, game over
		while(1);
	} else {
		bls_map[pos_cal(snake.bodyloc[0])] = 0;
		clear_cell(pos_cal(snake.bodyloc[0]));
		for(int i = 1;i < snake.length; i++) {
			// check hit self
			if(newHead.x == snake.bodyloc[i].x && newHead.y == snake.bodyloc[i].y) {
				// hit self, game over
				while(1);
			}
			memcpy(&snake.bodyloc[i-1], &snake.bodyloc[i],sizeof(point_t));
		}
		memcpy(&snake.bodyloc[snake.length-1], &newHead, sizeof(point_t));
	}
}

void SnakeGameEntry(void *param) {
	game_init();
	apply_for_refresh();
	while(1) {
		game_logic();
		rt_thread_mdelay(200);
	}
}