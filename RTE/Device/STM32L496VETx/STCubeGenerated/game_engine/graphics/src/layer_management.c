/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#include "ge_graphics.h"
#include "arm_2d.h"
#include "arm_2d_helper.h"
#include "arm_2d_scenes.h"

static ecb_t ecb = {0};
Obj_State engine_state = Obj_Not_Initial;

// TODO: DISP0_ADAPTER
GameEngineStatus player_init(void) {
	disp_adapter0_init();
	ecb.player = &DISP0_ADAPTER;
	return Game_Engine_EOK;
}

static void __on_scene_depose(arm_2d_scene_t *ptScene)
{   
    ptScene->ptPlayer = NULL;
    free(ptScene);
}

static void __on_scene_frame_complete(arm_2d_scene_t *ptScene)
{
    
}

static
IMPL_PFB_ON_DRAW(__pfb_draw_scene_handler)
{
    ARM_2D_UNUSED(ptTile);
    ARM_2D_UNUSED(bIsNewFrame);
	
	refresh_stage(ptTile);
		
    arm_2d_op_wait_async(NULL);

    return arm_fsm_rt_cpl;
}

GameEngineStatus scene_init (void) {
	ecb.stage->scene = (arm_2d_scene_t){
//		.fnBackground   = &__pfb_draw_scene_background_handler,
		.fnScene        = &__pfb_draw_scene_handler,
//		.ptDirtyRegion  = (arm_2d_region_list_item_t *)s_tDirtyRegions,

//		.fnOnBGStart    = &__on_scene_background_start,
//		.fnOnBGComplete = &__on_scene_background_complete,
//		.fnOnFrameStart = &__on_scene_frame_start,
//		.fnBeforeSwitchOut = &__before_scene_switching_out,
		.fnOnFrameCPL   = &__on_scene_frame_complete,
		.fnDepose       = &__on_scene_depose,
    };

    arm_2d_scene_player_append_scenes(ecb.player, 
                                      &ecb.stage->scene, 
                                      1);
	
	return Game_Engine_EOK;
}

GameEngineStatus stage_init(void) {
	if(ecb.stage != NULL) {
		return Game_Engine_EOK;
	}
	ecb.stage = (stage_t *)malloc(sizeof(stage_t));
	if (ecb.stage == NULL) {
		return Game_Engine_Err;
	}
	memset(ecb.stage, 0, sizeof(stage_t));
	
	if (scene_init() != Game_Engine_EOK) {
		return Game_Engine_Err;
	}
	
	return Game_Engine_EOK;
}

GameEngineStatus refresh_init(void) {
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

GameEngineStatus engine_init(void) {		
	if (player_init() != Game_Engine_EOK) {
		return Game_Engine_Err;
	}
	
	if (stage_init() != Game_Engine_EOK) {
		return Game_Engine_Err;
	}
	
	if (refresh_init() != Game_Engine_EOK) {
		return Game_Engine_Err;
	}
	
	ecb.chState = Obj_Initial;
	engine_state = Obj_Initial;
	
	return Game_Engine_EOK;
}

void register_layer(layer_t *layer) {
	if(engine_state == Obj_Not_Initial) {
		engine_init();
	}
	ecb.stage->ptLayer = layer;
}

void apply_for_refresh(void) {
	if(engine_state == Obj_Not_Initial) {
		engine_init();
	}
	
	while(rt_sem_release(ecb.refresh.sem_req) != RT_EOK);
	while(rt_sem_take(ecb.refresh.sem_rsp, RT_WAITING_FOREVER) != RT_EOK);
}

GameEngineStatus refresh_stage(const arm_2d_tile_t *ptTile){
	for(int i = 0;i < ecb.stage->ptLayer->hwXCount * ecb.stage->ptLayer->hwYCount; i++) {		
		arm_2dp_fill_colour_with_opacity(
			NULL, 
			ptTile, 
			(arm_2d_region_t []){
				{
					.tLocation = {
						.iX = (i % ecb.stage->ptLayer->hwXCount) * (__GLCD_CFG_SCEEN_WIDTH__ / ecb.stage->ptLayer->hwXCount),
						.iY = (i / ecb.stage->ptLayer->hwXCount) * (__GLCD_CFG_SCEEN_HEIGHT__ / ecb.stage->ptLayer->hwYCount),
					},
					.tSize = {
						.iWidth = __GLCD_CFG_SCEEN_WIDTH__ / ecb.stage->ptLayer->hwXCount,
						.iHeight = __GLCD_CFG_SCEEN_HEIGHT__ / ecb.stage->ptLayer->hwYCount,
					},
				},
			}, 
			ecb.stage->ptLayer->ptCells->tColor,
			ecb.stage->ptLayer->ptCells->chOpacity
		);
		arm_2d_op_wait_async(NULL);
	}
	
//	arm_2dp_fill_colour_with_opacity(
//			NULL, 
//			ptTile, 
//			(arm_2d_region_t []){
//				{
//					.tLocation = {
//						.iX = 0,
//						.iY = 0,
//					},
//					.tSize = {
//						.iWidth = __GLCD_CFG_SCEEN_WIDTH__ / 10,
//						.iHeight = __GLCD_CFG_SCEEN_HEIGHT__ / 10,
//					},
//				},
//			},
//			(__arm_2d_color_t){GLCD_COLOR_RED},
//			255-128);
	
	return Game_Engine_EOK;
}

void GameEngineEntry(void *param) {
	if(engine_state == Obj_Not_Initial) {
		if(engine_init() != Game_Engine_EOK) {
			// error handle
			while(1);
		}
	}
	
	while(1) {
		while(rt_sem_take(ecb.refresh.sem_req, RT_WAITING_FOREVER) != RT_EOK);
		
		while(disp_adapter0_task() != arm_fsm_rt_cpl);
		
		while(rt_sem_release(ecb.refresh.sem_rsp) != RT_EOK);
	}
}