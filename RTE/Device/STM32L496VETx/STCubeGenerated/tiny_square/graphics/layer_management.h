/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#ifndef __LAYER_MANAGEMENT_H
#define __LAYER_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtthread.h"
#include "arm_2d_helper.h"

typedef enum {
	Obj_Not_Initial = 0x00,
	Obj_Initial = 0x01,
} Obj_State;

typedef enum {
	Game_Engine_EOK = 0x00,
	Game_Engine_Err = 0x01,
} GameEngineStatus;

typedef struct cell_t {
	__arm_2d_color_t tColor;
	uint8_t chOpacity;
	uint8_t blsDirty;
} cell_t;

typedef struct layer_t {
	uint16_t hwXCount;
	uint16_t hwYCount;
	cell_t *ptCells;
} layer_t;

void GameEngineEntry(void *param);
void register_layer(layer_t *layer);
void apply_for_refresh (void);
GameEngineStatus engine_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __LAYER_MANAGEMENT_H */