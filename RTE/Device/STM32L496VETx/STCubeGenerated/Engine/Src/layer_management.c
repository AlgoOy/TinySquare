#include "layer_management.h"
#include "__layer_management.h"
#include "arm_2d.h"
#include "arm_2d_helper.h"

static ecb_t ecb = {0};

static GameEngineStatus engine_init(void) {
	if(ecb.refresh.sem_req == RT_NULL) {
		ecb.refresh.sem_req = rt_sem_create("engineReq", 0, RT_IPC_FLAG_FIFO);
	}
	if(ecb.refresh.sem_rsp == RT_NULL) {
		ecb.refresh.sem_rsp = rt_sem_create("engineRsp", 0, RT_IPC_FLAG_FIFO);
	}
	if (ecb.refresh.sem_req == RT_NULL || ecb.refresh.sem_rsp == RT_NULL) {
		return Game_Engine_Err;
	}
		
	return Game_Engine_EOK;
}

void register_layer(layer_t *layer) {
	ecb.ptLayer = layer;
}

void apply_for_refresh(void) {
	if(ecb.refresh.sem_req == RT_NULL || ecb.refresh.sem_rsp == RT_NULL) {
		engine_init();
	} else {
		while(rt_sem_release(ecb.refresh.sem_req) != RT_EOK);
		while(rt_sem_take(ecb.refresh.sem_rsp, RT_WAITING_FOREVER) != RT_EOK);
	}
}

static arm_2d_tile_t* initial_draw_cell_handler (rt_uint16_t width, rt_uint16_t height) {
	arm_2d_tile_t* draw_cell_handler = (arm_2d_tile_t *)malloc(sizeof(arm_2d_tile_t));
	uint8_t* cell_handler_buffer = (uint8_t *)malloc(width * height * sizeof(uint8_t));
	
	draw_cell_handler->tRegion.tLocation.iX = 0;
	draw_cell_handler->tRegion.tLocation.iY = 0;
	draw_cell_handler->tRegion.tSize.iWidth = width;
	draw_cell_handler->tRegion.tSize.iHeight = height;
	draw_cell_handler->pchBuffer = cell_handler_buffer;
	
	return draw_cell_handler;
}

extern 
int32_t Disp0_DrawBitmap(int16_t x, 
                        int16_t y, 
                        int16_t width, 
                        int16_t height, 
                        const uint8_t *bitmap);

static GameEngineStatus refresh_scene(const arm_2d_tile_t *ptCellHandler) {
	
	for(int i = 0;i < ecb.ptLayer->hwXCount*ecb.ptLayer->hwYCount; i++) {
		arm_2dp_fill_colour_with_opacity(
			NULL, 
			ptCellHandler, 
			&ptCellHandler->tRegion,
			//ecb.ptLayer->ptCells[i].tColor,
			//ecb.ptLayer->ptCells[i].chOpacity
			(__arm_2d_color_t){GLCD_COLOR_RED},
			255-128
		);
		
		Disp0_DrawBitmap(ptCellHandler->tRegion.tLocation.iX,
                    ptCellHandler->tRegion.tLocation.iY,
                    ptCellHandler->tRegion.tSize.iWidth,
                    ptCellHandler->tRegion.tSize.iHeight,
                    (const uint8_t *)ptCellHandler->pchBuffer);
	}
	return Game_Engine_EOK;
}

void GameEngineEntry(void *param) {
	if(engine_init() != Game_Engine_EOK) {
		return;
	}
	
	rt_uint16_t cell_width = Screen_Width/ecb.ptLayer->hwXCount;
	rt_uint16_t cell_height = Screen_Height/ecb.ptLayer->hwYCount;
	
	const arm_2d_tile_t *ptCellHandler =  initial_draw_cell_handler(cell_width, cell_height);
	
	while(1) {
		while(rt_sem_take(ecb.refresh.sem_req, RT_WAITING_FOREVER) != RT_EOK);
		
		refresh_scene(ptCellHandler);
		
		while(rt_sem_release(ecb.refresh.sem_rsp) != RT_EOK);
	}
}