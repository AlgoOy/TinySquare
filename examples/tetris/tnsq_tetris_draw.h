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

#define TNSQ_TETRIS_NEXT_BLOCK_X (TNSQ_TETRIS_X_COUNT -12)
#define TNSQ_TETRIS_NEXT_BLOCK_Y (TNSQ_TETRIS_Y_GAME_COUNT + 2)

#define TNSQ_TETRIS_SCORE_X (TNSQ_TETRIS_X_COUNT -17)
#define TNSQ_TETRIS_SCORE_Y (TNSQ_TETRIS_Y_GAME_COUNT + 2)

#define BOARD_BLOCK_INFO (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 0}
#define T_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 1}
#define L_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 2}
#define J_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 3}
#define Z_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 4}
#define S_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 5}
#define O_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 6}
#define I_BLOCK_INFO     (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 7}
#define CLEAR_BLOCK_INFO (tnsq_gfx_user_map_t){.bIsDirty = RT_TRUE, .u7Idx = 8}

tnsq_gfx_stage_t *tetris_menu_stage_init(void);
tnsq_gfx_stage_t *tetris_game_stage_init(void);

void tetris_init_bg_cl_layer(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tetris_init_bg_layer(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tetris_init_interface_layer(tnsq_gfx_stage_t *ptStage, tnsq_gfx_user_map_t *ptCells);
rt_uint8_t tetris_init_text_layer(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tetris_menu_layer_select(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tetris_memu_layer_diffculty(tnsq_gfx_stage_t *ptStage);
rt_uint8_t tetris_num_layer_level(tnsq_gfx_stage_t *ptStage);


#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif
 
#endif