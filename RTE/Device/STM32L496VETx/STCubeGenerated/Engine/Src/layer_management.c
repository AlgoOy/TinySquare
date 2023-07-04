#include "layer_management.h"
#include "__layer_management.h"

static ecb_t ecb;

static GameEngineStatus engine_init(void) {
	ecb.refresh.sem_req = rt_sem_create("engineReq", 0, RT_IPC_FLAG_FIFO);
	ecb.refresh.sem_rsp = rt_sem_create("engineRsp", 0, RT_IPC_FLAG_FIFO);
	if (ecb.refresh.sem_req == RT_NULL || ecb.refresh.sem_rsp == RT_NULL) {
		return Game_Engine_Err;
	}
		
	return Game_Engine_EOK;
}

void register_layer(layer_t *layer) {
	ecb.ptLayer = layer;
}

void apply_for_refresh(void) {
	while(rt_sem_release(ecb.refresh.sem_req) != RT_EOK);
	while(rt_sem_take(ecb.refresh.sem_rsp, RT_WAITING_FOREVER) != RT_EOK);
}

static GameEngineStatus refresh_scene(void) {
	
	return Game_Engine_EOK;
}

void GameEngineEntry(void *param) {
	if(engine_init() != Game_Engine_EOK) {
		return;
	}
	while(1) {
		while(rt_sem_take(ecb.refresh.sem_req, RT_WAITING_FOREVER) != RT_EOK);
		
		refresh_scene();
		
		while(rt_sem_release(ecb.refresh.sem_rsp) != RT_EOK);
	}
}