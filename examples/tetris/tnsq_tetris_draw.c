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

#include "arm_extra_controls.h"

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

extern const arm_2d_tile_t c_tilebg_tetrisRGB565;

rt_uint8_t tnsq_tetris_init_bg_layer(tnsq_gfx_stage_t *ptStage)
{
    tnsq_gfx_layer_bg_cfg_t tGameBGCFG = {
        .ptBackGround = &c_tilebg_tetrisRGB565,
        .ptBackGroundMask = NULL,
        .tRegion = {
            .tLocation = {
                .iX = 0,
                .iY = 0,
            },
            .tSize = c_tilebg_tetrisRGB565.tRegion.tSize,
        },
    };
    tnsq_gfx_layer_bg_t *ptGameBG = tnsq_gfx_layer_bg_init(&tGameBGCFG);
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameBG);
}

void tnsq_tetris_init_bg_cl_layer(tnsq_gfx_stage_t *ptStage)
{
    arm_2d_size_t tScreenSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
    
    tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
        .tType = TNSQ_GFX_BG_CL_NORMAL,
        .chOpacity = 32,
        .ptBackGroundColorMask = NULL,
        .tRegion = {
            .tLocation = {
                .iX = 0,
                .iY = 0,
            },
            .tSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER),
        },
        .tColor = (__arm_2d_color_t){GLCD_COLOR_BLACK},
        .borderOpacity = NULL,
        .cornerOpacity = NULL,
    };
    tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
//    tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
    
    tGameBGCLCFG = (tnsq_gfx_layer_bg_cl_cfg_t){
        .tType = TNSQ_GFX_BG_CL_NORMAL,
        .chOpacity = 128,
        .ptBackGroundColorMask = NULL,
        .tRegion = {
            .tLocation = {
                .iX = (TNSQ_TETRIS_Y_GAME_COUNT + 1) * (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT),
                .iY = 0,
            },
            .tSize = {
                .iWidth = (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT) * 6,
                .iHeight = tScreenSize.iHeight - (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT),
            },
        },
        .tColor = (__arm_2d_color_t){GLCD_COLOR_DARK_GREY},
        .borderOpacity = NULL,
        .cornerOpacity = NULL,
    };
    tnsq_gfx_layer_bg_cl_t *ptGameBGCL1 = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
    tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL1);
    
    tGameBGCLCFG = (tnsq_gfx_layer_bg_cl_cfg_t){
        .tType = TNSQ_GFX_BG_CL_BOX,
        .chOpacity = 128,
        .ptBackGroundColorMask = NULL,
        .tRegion = {
            .tLocation = {
                .iX = TNSQ_TETRIS_NEXT_BLOCK_Y * (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT),
                .iY = TNSQ_TETRIS_NEXT_BLOCK_X * (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT),
            },
            .tSize = {
                .iWidth = (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT) * 4,
                .iHeight = (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT) * 4,
            },
        },
        .tColor = (__arm_2d_color_t){GLCD_COLOR_BLACK},
        .borderOpacity = NULL,
        .cornerOpacity = NULL,
    };
    tnsq_gfx_layer_bg_cl_t *ptGameBGCL2 = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
    tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL2);
    
    tGameBGCLCFG = (tnsq_gfx_layer_bg_cl_cfg_t){
        .tType = TNSQ_GFX_BG_CL_BOX,
        .chOpacity = 128,
        .ptBackGroundColorMask = NULL,
        .tRegion = {
            .tLocation = {
                .iX = TNSQ_TETRIS_SCORE_Y * (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT),
                .iY = TNSQ_TETRIS_SCORE_X * (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT),
            },
            .tSize = {
                .iWidth = (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT) * 4,
                .iHeight = (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT) * 2,
            },
        },
        .tColor = (__arm_2d_color_t){GLCD_COLOR_BLACK},
        .borderOpacity = NULL,
        .cornerOpacity = NULL,
    };
    tnsq_gfx_layer_bg_cl_t *ptGameBGCL3 = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
    tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL3);
}

static void _tnsq_tetris_user_map_func(rt_uint8_t idx, arm_2d_tile_t const *ptTile, const rt_bool_t bIsNewFrame)
{
    arm_2d_canvas(ptTile, __user_map_canvas)
    {
        if (idx == 0)
        {
            arm_2dp_fill_colour_with_opacity
            (
                NULL,
                ptTile,
                &__user_map_canvas,
                (__arm_2d_color_t){GLCD_COLOR_DARK_GREY},
                128
            );
        }
        else if (idx == 1)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_BLUE, 255, bIsNewFrame);
        }
        else if (idx == 2)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_GREEN, 255, bIsNewFrame);
        }
        else if (idx == 3)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_CYAN, 255, bIsNewFrame);
        }
        else if (idx == 4)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_RED, 255, bIsNewFrame);
        }
        else if (idx == 5)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_YELLOW, 255, bIsNewFrame);
        }
        else if (idx == 6)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_OLIVE, 255, bIsNewFrame);
        }
        else if (idx == 7)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_PURPLE, 255, bIsNewFrame);
        }
        else if (idx == 8)
        {
            draw_round_corner_box(ptTile, &__user_map_canvas, GLCD_COLOR_WHITE, 0, bIsNewFrame);
        }
    }
}

rt_uint8_t tnsq_tetris_init_interface_layer(tnsq_gfx_stage_t *ptStage, tnsq_gfx_user_map_t *ptUserMap)
{
    tnsq_gfx_layer_user_cfg_t tInterfaceCFG = {
        .hwXCount = TNSQ_TETRIS_X_COUNT,
        .hwYCount = TNSQ_TETRIS_Y_COUNT,
        .pchUserMap = ptUserMap,
        .ptFunc = _tnsq_tetris_user_map_func,
    };
    tnsq_gfx_layer_user_t *ptGameInterfaceLayer = tnsq_gfx_layer_user_init(&tInterfaceCFG);
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameInterfaceLayer);
}

rt_uint8_t tnsq_tetris_init_text_layer(tnsq_gfx_stage_t *ptStage)
{
    arm_2d_size_t tScreenSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
    
    tnsq_gfx_layer_text_cfg_t tTextCFG = {
        .chOpacity = 255,
        .ptFont = &ARM_2D_FONT_6x8.use_as__arm_2d_font_t,
        .tColour = {
            .tForeground = GLCD_COLOR_GREEN,
        },
        .tRegion = {
            .tLocation = {
                .iX = TNSQ_TETRIS_SCORE_Y * (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT),
                .iY = TNSQ_TETRIS_SCORE_X * (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT),
            },
            .tSize = {
                .iWidth = (tScreenSize.iWidth / TNSQ_TETRIS_X_COUNT) * 4,
                .iHeight = (tScreenSize.iHeight / TNSQ_TETRIS_Y_COUNT) * 2,
            },
        }
    };
    tnsq_gfx_layer_text_t *ptGameTextLayer = tnsq_gfx_layer_text_init(&tTextCFG);
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameTextLayer);
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif