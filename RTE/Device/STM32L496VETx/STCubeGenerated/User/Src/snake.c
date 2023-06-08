#include <stdlib.h>
#include <time.h>
#include "../Inc/snake.h"

static Game_State_Info gameState= {0};

extern const arm_2d_tile_t c_tileSnakeLogoRGB565;
extern const arm_2d_tile_t c_tileSnakeLogoMask;

static Game_State_Info getGameState(void) {
	return gameState;
}

SnakeGameStatus DrawStartGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground) {
	if(ground == background) {
		/* background */
		arm_2d_canvas(ptTile, __top_canvas) {
			arm_2d_fill_colour(ptTile, NULL, GLCD_COLOR_WHITE);
			
			arm_2d_align_top_centre(__top_canvas, c_tileSnakeLogoRGB565.tRegion.tSize) {
				arm_2d_rgb565_tile_copy_with_src_mask(
					&c_tileSnakeLogoRGB565,
					&c_tileSnakeLogoMask,
					ptTile,
					&__top_centre_region,
					ARM_2D_CP_MODE_COPY
				);
			}
		}
		/* background */
	} else {
		/* foreground */
		arm_2d_canvas(ptTile, __top_canvas) {
			const char* pchString = "Press Any Key to Start Game";
			
			int16_t textWidth = strlen(pchString) * ARM_2D_FONT_6x8.use_as__arm_2d_font_t.tCharSize.iWidth;
			
			arm_lcd_text_set_target_framebuffer((arm_2d_tile_t *)ptTile);
			arm_lcd_text_set_font(&ARM_2D_FONT_6x8.use_as__arm_2d_font_t);
			arm_lcd_text_set_draw_region(NULL);
			
			arm_2dp_fill_colour_with_opacity(
                    NULL, 
                    ptTile, 
                    (arm_2d_region_t []){
                        {
                            .tLocation = {
                                .iX = 2,
                                .iY = __GLCD_CFG_SCEEN_HEIGHT__ - 17},
                            .tSize = {
                                .iWidth = __GLCD_CFG_SCEEN_WIDTH__ - 4,
                                .iHeight = 9,
                            },
                        },
                    }, 
                    (__arm_2d_color_t){__RGB(64, 64, 64)},
                    255 - 128);
			arm_2d_op_wait_async(NULL);
			arm_lcd_text_set_colour(GLCD_COLOR_GREEN, GLCD_COLOR_WHITE);
			arm_lcd_text_location((__GLCD_CFG_SCEEN_HEIGHT__ + 7) / 8 - 2,
										((__GLCD_CFG_SCEEN_WIDTH__ / ARM_2D_FONT_6x8.use_as__arm_2d_font_t.tCharSize.iWidth) - strlen(pchString)) / 2);
			arm_lcd_printf("%s", pchString);
    }
		/* foreground */
	}
	return Snake_Game_NO_ERR;
}

SnakeGameStatus DrawRunningGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground) {
	if (ground == background) {
		/* background */
		arm_2d_canvas(ptTile, __top_canvas) {
										
			arm_2dp_fill_colour_with_opacity(
										NULL, 
										ptTile, 
										(arm_2d_region_t []){
											{
												.tLocation = {
													.iX = 0,
													.iY = STATE_VIEW_HEIGHT + WIDTH_PIXELS_USED_BY_GAME,
												},
												.tSize = {
													.iWidth = __GLCD_CFG_SCEEN_WIDTH__,
													.iHeight = __GLCD_CFG_SCEEN_HEIGHT__ - (STATE_VIEW_HEIGHT + HEIGHT_PIXELS_USED_BY_GAME),
												},
											},
										}, 
										(__arm_2d_color_t){__RGB(64, 64, 64)},
										255 - 128
									);
			
			arm_2dp_fill_colour_with_opacity(
										NULL, 
										ptTile, 
										(arm_2d_region_t []){
											{
												.tLocation = {
													.iX = 0,
													.iY = STATE_VIEW_HEIGHT,
												},
												.tSize = {
													.iWidth = (__GLCD_CFG_SCEEN_WIDTH__ - WIDTH_PIXELS_USED_BY_GAME) / 2,
													.iHeight = HEIGHT_PIXELS_USED_BY_GAME,
												},
											},
										}, 
										(__arm_2d_color_t){__RGB(64, 64, 64)},
										255 - 128
									);
			
			arm_2dp_fill_colour_with_opacity(
										NULL, 
										ptTile, 
										(arm_2d_region_t []){
											{
												.tLocation = {
													.iX = __GLCD_CFG_SCEEN_WIDTH__ - ((__GLCD_CFG_SCEEN_WIDTH__ - WIDTH_PIXELS_USED_BY_GAME) / 2),
													.iY = STATE_VIEW_HEIGHT,
												},
												.tSize = {
													.iWidth = (__GLCD_CFG_SCEEN_WIDTH__ - WIDTH_PIXELS_USED_BY_GAME) / 2,
													.iHeight = HEIGHT_PIXELS_USED_BY_GAME,
												},
											},
										}, 
										(__arm_2d_color_t){__RGB(64, 64, 64)},
										255 - 128
									);
		}
		/* background */
	}	else {
		/* foreground */
		arm_2d_canvas(ptTile, __top_canvas) {			
			Game_State_Info gameState = getGameState();
			
			arm_2d_fill_colour(ptTile, NULL, GLCD_COLOR_WHITE);
			
			arm_2dp_fill_colour_with_opacity(
                    NULL, 
                    ptTile, 
                    (arm_2d_region_t []){
                        {
                            .tLocation = {
                                .iX = 0,
                                .iY = 0
														},
                            .tSize = {
                                .iWidth = __GLCD_CFG_SCEEN_WIDTH__,
                                .iHeight = STATE_VIEW_HEIGHT,
                            },
                        },
                    }, 
                    (__arm_2d_color_t){__RGB(64, 64, 64)},
                    255 - 128
									);
        arm_2d_op_wait_async(NULL);
			
			arm_lcd_text_set_target_framebuffer((arm_2d_tile_t *)ptTile);
			arm_lcd_text_set_font(&ARM_2D_FONT_6x8.use_as__arm_2d_font_t);
			arm_lcd_text_set_draw_region(NULL);
			
			arm_lcd_text_set_colour(GLCD_COLOR_GREEN, GLCD_COLOR_WHITE);
			arm_lcd_text_location(0, 2);
			arm_lcd_printf(" score: %4d\n  length: %4d", gameState.score, gameState.length);
										
			
    }
		/* foreground */
	}
	return Snake_Game_NO_ERR;
}

SnakeGameStatus DrawEndGamePanel(const arm_2d_tile_t *ptTile, DrawSenceSelection ground) {
	return Snake_Game_NO_ERR;
}

SnakeGameStatus InitGame(const arm_2d_tile_t *ptTile) {
	
	return Snake_Game_NO_ERR;
}

SnakeGameStatus CreateSnake(const arm_2d_tile_t *ptTile, Snake *body) {
	
	return Snake_Game_NO_ERR;
}

SnakeGameStatus CreateFruit(const arm_2d_tile_t *ptTile) {
	srand(time(NULL));
	uint8_t snake_x = (uint8_t)rand() % HORIZONTAL_NUM_MAX, snake_y = (uint8_t)rand() % VERTICAL_NUM_MAX;
	
	
	return Snake_Game_NO_ERR;
}
