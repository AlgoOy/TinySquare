/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-03     AlgoOy     the first version
 */

#ifndef __TNSQ_TETRIS_DRAW_H__
#define __TNSQ_TETRIS_DRAW_H__

#ifdef   __cplusplus
extern "C" {
#endif

#include "tiny_square.h"

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#   pragma clang diagnostic ignored "-Wpadded"
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wpadded"
#endif

#define TNSQ_TETRIS_X_COUNT 20
#define TNSQ_TETRIS_Y_COUNT 20
#define TNSQ_TETRIS_Y_GAME_COUNT (20 - 8)

#define T_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_BLUE}
#define L_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_GREEN}
#define J_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_CYAN}
#define Z_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_RED}
#define S_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_YELLOW}
#define O_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_OLIVE}
#define I_BLOCK_INFO (tnsq_gfx_cell_t){.bIsDirty = RT_TRUE, .chOpacity = 255, .tColor = GLCD_COLOR_PURPLE}

tnsq_gfx_stage_t *tnsq_tetris_stage_init(void);

rt_uint8_t tnsq_tetris_init_bg_cl_layer(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tnsq_tetris_init_bg_layer(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tnsq_tetris_init_interface_layer(tnsq_gfx_stage_t *ptStage, tnsq_gfx_cell_t *ptCells);
rt_uint8_t tnsq_tetris_init_text_layer(tnsq_gfx_stage_t *ptStage);

void draw_cell(tnsq_gfx_cell_t *ptCells, rt_uint16_t pos, rt_uint8_t chOpacity, __arm_2d_color_t tColor);

void tnsq_tetris_draw_interface(tnsq_gfx_cell_t *ptCells, rt_uint8_t x, rt_uint8_t y);

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif