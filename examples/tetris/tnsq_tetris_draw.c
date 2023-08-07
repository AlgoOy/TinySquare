/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-08-03     AlgoOy     the first version
 */

#include "tnsq_tetris_draw.h"

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

tnsq_gfx_stage_t *tnsq_tetris_stage_init(void)
{
    disp_adapter0_init();
    tnsq_gfx_stage_cfg_t tGameStageCFG = {
        .ptDispAdapter = {
            .ptPlayer = &DISP0_ADAPTER,
            .ptPlayerTask = disp_adapter0_task,
        },
    };
    tnsq_gfx_stage_t *ptGameStage = tnsq_gfx_stage_init(&tGameStageCFG);
    if (ptGameStage == NULL)
    {
        /* error handle */
        printf("game stage init failed");
        return NULL;
    }
    else
    {
        return ptGameStage;
    }
}

rt_uint8_t tnsq_tetris_init_bg_cl_layer(tnsq_gfx_stage_t *ptStage)
{
    tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
        .chOpacity = 255,
        .ptBackGroundColorMask = NULL,
        .tRegion = {
            .tLocation = {
                .iX = 0,
                .iY = 0,
            },
            .tSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER),
        },
        .tColor = (__arm_2d_color_t){GLCD_COLOR_BLACK},
    };
    tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
}

rt_uint8_t tnsq_tetris_init_interface_layer(tnsq_gfx_stage_t *ptStage, tnsq_gfx_cell_t *ptCells)
{
    tnsq_gfx_layer_cell_cfg_t tInterfaceCFG = {
        .hwXCount = TNSQ_TETRIS_X_COUNT,
        .hwYCount = TNSQ_TETRIS_Y_COUNT,
        .ptCells  = ptCells,
    };
    tnsq_gfx_layer_cell_t *ptGameInterfaceLayer = tnsq_gfx_layer_cell_init(&tInterfaceCFG);
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameInterfaceLayer);
}

static void _draw_cell(tnsq_gfx_cell_t *ptCells, rt_uint16_t pos, rt_uint8_t chOpacity, __arm_2d_color_t tColor)
{
	ptCells[pos].bIsDirty = RT_TRUE;
	ptCells[pos].chOpacity = chOpacity;
	ptCells[pos].tColor = tColor;
}
    
void tnsq_tetris_draw_interface(tnsq_gfx_cell_t *ptCells, rt_uint8_t x, rt_uint8_t y)
{
    for (int i = 0; i < x * y; i ++)
    {
        if (ptCells[i].bIsDirty == RT_TRUE)
        {
            _draw_cell(ptCells, i, 255, (__arm_2d_color_t){GLCD_COLOR_DARK_GREY});
        }
    }
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif