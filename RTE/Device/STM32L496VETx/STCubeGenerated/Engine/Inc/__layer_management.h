#ifndef ____LAYER_MANAGEMENT_H
#define ____LAYER_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "layer_management.h"
#include "rtthread.h"

typedef enum {
	Game_Engine_EOK = 0x00,
	Game_Engine_Err = 0x01,
} GameEngineStatus;

typedef struct engine_control_block {
	layer_t *ptLayer;
	struct {
		rt_sem_t sem_req, sem_rsp;
	} refresh;
} ecb_t;

#ifdef __cplusplus
}
#endif

#endif /* ____LAYER_MANAGEMENT_H */