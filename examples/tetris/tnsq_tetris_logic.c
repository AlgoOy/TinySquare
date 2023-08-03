/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-03     AlgoOy     the first version
 */

#include "tnsq_tetris_logic.h"
#include "tnsq_tetris_draw.h"
#include "tiny_square.h"

// todo: just for debug
#include "stdio.h"
 
#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wunused-function"
#   pragma clang diagnostic ignored "-Wmissing-declarations"  
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_IAR__
#   pragma diag_suppress=Pa089,Pe188,Pe177,Pe174
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wunused-value"
#endif

#undef this
#define this (*ptThis)
    
rt_bool_t bls_map[TNSQ_TETRIS_X_COUNT][TNSQ_TETRIS_Y_COUNT] = {0};

static void _tnsq_tetris_init_interface(void)
{
    
}
    
static void _tnsq_tetris_init_block(void)
{

}
    
static void _game_initial(void) 
{
    // initial game interface
    _tnsq_tetris_init_interface();
    
    // draw game interface
    tnsq_tetris_draw_interface(bls_map, TNSQ_TETRIS_X_COUNT, TNSQ_TETRIS_Y_COUNT);
    
    // initial block info
    _tnsq_tetris_init_block();
    
    // initial seed
    srand((unsigned) arm_2d_helper_get_system_timestamp());
}

static void _tnsq_tetris_game_logic(void)
{
    
}
    
void tnsq_tetris_task_entry(void *ptParam)
{
    (void)ptParam;
    
    _game_initial();
    
    while (1)
    {
        // apply for fresh screen
        tnsq_gfx_apply_for_refresh();
        
        // execute game logic
        _tnsq_tetris_game_logic();
    }
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif