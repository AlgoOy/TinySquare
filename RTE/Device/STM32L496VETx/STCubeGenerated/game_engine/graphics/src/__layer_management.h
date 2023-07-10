/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef ____LAYER_MANAGEMENT_H
#define ____LAYER_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "layer_management.h"
#include "rtthread.h"
#include "arm_2d.h"

typedef enum {
	Obj_Not_Initial = 0x00,
	Obj_Initial = 0x01,
} Obj_State;

typedef enum {
	Game_Engine_EOK = 0x00,
	Game_Engine_Err = 0x01,
} GameEngineStatus;

typedef struct stage_t {
	arm_2d_scene_t scene;
	layer_t *ptLayer;
} stage_t;

typedef struct engine_control_block {
	Obj_State chState;
	struct {
		rt_sem_t sem_req, sem_rsp;
	} refresh;
	arm_2d_scene_player_t *player;
	stage_t	*stage;
} ecb_t;

GameEngineStatus engine_init(void);
GameEngineStatus player_init(void);
GameEngineStatus stage_init(void);
GameEngineStatus scene_init(void);
GameEngineStatus refresh_init(void);
GameEngineStatus refresh_stage(const arm_2d_tile_t *ptTile);

#ifdef __cplusplus
}
#endif

#endif /* ____LAYER_MANAGEMENT_H */