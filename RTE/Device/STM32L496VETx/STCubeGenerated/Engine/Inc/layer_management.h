#ifndef __LAYER_MANAGEMENT_H
#define __LAYER_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "arm_2d_helper.h"

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

#ifdef __cplusplus
}
#endif

#endif /* __LAYER_MANAGEMENT_H */