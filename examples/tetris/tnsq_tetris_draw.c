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
    
tnsq_gfx_stage_t *tetris_game_stage_init(void)
{
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
        printf("game stage init failed\n");
        return NULL;
    }
    else
    {
        return ptGameStage;
    }
}

tnsq_gfx_stage_t *tetris_menu_stage_init(void)
{
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
        printf("game stage init failed\n");
        return NULL;
    }
    else
    {
        return ptGameStage;
    }
}

extern const arm_2d_tile_t c_tilebg_tetrisRGB565;
rt_uint8_t tetris_init_bg_layer(tnsq_gfx_stage_t *ptStage)
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
    if (ptGameBG == NULL)
    {
        printf("bg layer init failed\n");
    }
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameBG);
}

void tetris_init_bg_cl_layer(tnsq_gfx_stage_t *ptStage)
{
    arm_2d_size_t tScreenSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
    
    do {
        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
            .tType = TNSQ_GFX_BG_CL_NORMAL,
            .chOpacity = 128,
            .ptBackGroundColorMask = NULL,
            .tRegion = {
                .tLocation = {
                    .iX = (TETRIS_Y_GAME_COUNT + 1) * (tScreenSize.iWidth / TETRIS_X_COUNT),
                    .iY = 0,
                },
                .tSize = {
                    .iWidth = (tScreenSize.iWidth / TETRIS_X_COUNT) * 6,
                    .iHeight = tScreenSize.iHeight - (tScreenSize.iHeight / TETRIS_Y_COUNT),
                },
            },
            .tColor = GLCD_COLOR_DARK_GREY,
            .borderOpacity = NULL,
            .cornerOpacity = NULL,
        };
        
        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
        if (ptGameBGCL == NULL)
        {
            printf("bg cl layer init failed\n");
        }
        
        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
    } while (0);
    
    do {
        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = (tnsq_gfx_layer_bg_cl_cfg_t){
            .tType = TNSQ_GFX_BG_CL_BOX | TNSQ_GFX_BG_CL_BORDER,
            .chOpacity = 128,
            .ptBackGroundColorMask = NULL,
            .tRegion = {
                .tLocation = {
                    .iX = TETRIS_NEXT_BLOCK_Y * (tScreenSize.iWidth / TETRIS_X_COUNT),
                    .iY = TETRIS_NEXT_BLOCK_X * (tScreenSize.iHeight / TETRIS_Y_COUNT),
                },
                .tSize = {
                    .iWidth = (tScreenSize.iWidth / TETRIS_X_COUNT) * 4,
                    .iHeight = (tScreenSize.iHeight / TETRIS_Y_COUNT) * 4,
                },
            },
            .tColor = GLCD_COLOR_BLACK,
            .borderOpacity = {32, 32, 255-64, 255-64},
            .cornerOpacity = {0, 128, 128, 128},
        };
        
        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
        if (ptGameBGCL == NULL)
        {
            printf("bg cl layer init failed\n");
        }
        
        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
    } while (0);
    
    do {
        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = (tnsq_gfx_layer_bg_cl_cfg_t){
            .tType = TNSQ_GFX_BG_CL_BOX | TNSQ_GFX_BG_CL_BORDER,
            .chOpacity = 128,
            .ptBackGroundColorMask = NULL,
            .tRegion = {
                .tLocation = {
                    .iX = TETRIS_SCORE_Y * (tScreenSize.iWidth / TETRIS_X_COUNT),
                    .iY = TETRIS_SCORE_X * (tScreenSize.iHeight / TETRIS_Y_COUNT),
                },
                .tSize = {
                    .iWidth = (tScreenSize.iWidth / TETRIS_X_COUNT) * 4,
                    .iHeight = (tScreenSize.iHeight / TETRIS_Y_COUNT) * 2,
                },
            },
            .tColor = GLCD_COLOR_BLACK,
            .borderOpacity = {32, 32, 255-64, 255-64},
            .cornerOpacity = {0, 128, 128, 128},
        };
        
        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
        if (ptGameBGCL == NULL)
        {
            printf("bg cl layer init failed\n");
        }
        
        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);    
    } while (0);
}

static void _tetris_user_map_func(rt_uint8_t idx, arm_2d_tile_t const *ptTile, const rt_bool_t bIsNewFrame)
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

rt_uint8_t tetris_init_interface_layer(tnsq_gfx_stage_t *ptStage, tnsq_gfx_user_map_t *ptUserMap)
{
    tnsq_gfx_layer_user_cfg_t tInterfaceCFG = {
        .hwXCount = TETRIS_X_COUNT,
        .hwYCount = TETRIS_Y_COUNT,
        .pchUserMap = ptUserMap,
        .ptFunc = _tetris_user_map_func,
    };
    
    tnsq_gfx_layer_user_t *ptGameInterfaceLayer = tnsq_gfx_layer_user_init(&tInterfaceCFG);
    if (ptGameInterfaceLayer == NULL)
    {
        printf("interface layer init failed\n");
    }
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameInterfaceLayer);
}

rt_uint8_t tetris_init_text_layer(tnsq_gfx_stage_t *ptStage)
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
                .iX = TETRIS_SCORE_Y * (tScreenSize.iWidth / TETRIS_X_COUNT),
                .iY = TETRIS_SCORE_X * (tScreenSize.iHeight / TETRIS_Y_COUNT),
            },
            .tSize = {
                .iWidth = (tScreenSize.iWidth / TETRIS_X_COUNT) * 4,
                .iHeight = (tScreenSize.iHeight / TETRIS_Y_COUNT) * 2,
            },
        }
    };
    
    tnsq_gfx_layer_text_t *ptGameTextLayer = tnsq_gfx_layer_text_init(&tTextCFG);
    if (ptGameTextLayer == NULL)
    {
        printf("text layer init failed\n");
    }
    
    return tnsq_gfx_register_layer_to_stage(ptStage, ptGameTextLayer);
}

rt_uint8_t tetris_menu_layer_select(tnsq_gfx_stage_t *ptStage)
{
	arm_2d_size_t tScreenSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
	
	arm_2d_size_t tItemSize = {
        .iWidth = 160,
        .iHeight = 30,
    };
	
	rt_uint8_t chShowItemNum = 3;
    
    do {
        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
            .tType = TNSQ_GFX_BG_CL_NORMAL,
            .chOpacity = 255,
            .ptBackGroundColorMask = NULL,
            .tRegion = {
                .tLocation = {0},
                .tSize = tScreenSize,
            },
            .tColor = __RGB(0x6d, 0x54, 0x84),
            .borderOpacity = NULL,
            .cornerOpacity = NULL,
        };
        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
        if (ptGameBGCL == NULL)
        {
            printf("menu layer init failed\n");
        }
        
        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
    } while (0);
    
//    do {
//        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
//            .tType = TNSQ_GFX_BG_CL_BORDER,
//            .tRegion = {
//                .tLocation = {
//                    .iX = (tScreenSize.iWidth - tItemSize.iWidth - 4) >> 1,
//                    .iY = (tScreenSize.iHeight - tItemSize.iHeight * chShowItemNum - 4) >> 1,
//                },
//                .tSize = {
//                    .iWidth = tItemSize.iWidth + 4,
//                    .iHeight = tItemSize.iHeight * chShowItemNum + 4,
//                },
//            },
//            .tColor = GLCD_COLOR_WHITE,
//            .borderOpacity = {255, 255, 255, 255},
//            .cornerOpacity = {255, 255, 255, 255},
//        };
//        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
//        if (ptGameBGCL == NULL)
//        {
//            printf("menu layer init failed\n");
//        }
//        
//        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
//    } while (0);
    
    do {
         static const char *pchStringTable[] = {
			"start",
            "difficulty",
			"challenge"
        };
        tnsq_gfx_layer_menu_cfg_t tMenuCFG = {
            .tItemGeneral = {
                .chStringCount = sizeof(pchStringTable) >> 2,
                .pchStringTable = pchStringTable,
                .tItemSize = tItemSize,
                .tItemPadding = 0,
                .chShowItemNum = chShowItemNum,
                .nFinishInMs = 150,
                .ptFont = (struct arm_2d_font_t *)&ARM_2D_FONT_16x24,
            },
            .tItemNormal = {
                .tColor = {
                    .box = __RGB(0x6d, 0x54, 0x84),
                    .font = __RGB(0x94, 0xd2, 0x52),
                },
                .chOpacity = 255,
            },
            .tItemSelected = {
                .tColor = {
                    .box = __RGB(0xff, 0xff, 0xff),
                    .font = __RGB(0x6d, 0x54, 0x84),
                },
                .chOpacity = 255,
            },
        };
        
        tnsq_gfx_layer_menu_t *ptMenuLayer = tnsq_gfx_layer_menu_init(&tMenuCFG);
        if (ptMenuLayer == NULL)
        {
            printf("menu layer init failed\n");
        }
        
        return tnsq_gfx_register_layer_to_stage(ptStage, ptMenuLayer);
    } while (0);
}

rt_uint8_t tetris_memu_layer_diffculty(tnsq_gfx_stage_t *ptStage)
{
    arm_2d_size_t tScreenSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
    
    arm_2d_size_t tItemSize = {
        .iWidth = 160,
        .iHeight = 30,
    };
    
    rt_uint8_t chShowItemNum = 3;
    
//    do {
//        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
//            .tType = TNSQ_GFX_BG_CL_NORMAL,
//            .chOpacity = 255,
//            .ptBackGroundColorMask = NULL,
//            .tRegion = {
//                .tLocation = {0},
//                .tSize = tScreenSize,
//            },
//            .tColor = __RGB(0x6d, 0x54, 0x84),
//            .borderOpacity = NULL,
//            .cornerOpacity = NULL,
//        };
//        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
//        if (ptGameBGCL == NULL)
//        {
//            printf("menu layer init failed\n");
//        }
//        
//        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
//    } while (0);
    
//    do {
//        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
//            .tType = TNSQ_GFX_BG_CL_BORDER,
//            .tRegion = {
//                .tLocation = {
//                    .iX = (tScreenSize.iWidth - tItemSize.iWidth - 4) >> 1,
//                    .iY = (tScreenSize.iHeight - tItemSize.iHeight * chShowItemNum - 4) >> 1,
//                },
//                .tSize = {
//                    .iWidth = tItemSize.iWidth + 4,
//                    .iHeight = tItemSize.iHeight * chShowItemNum + 4,
//                },
//            },
//            .tColor = GLCD_COLOR_WHITE,
//            .borderOpacity = {255, 255, 255, 255},
//            .cornerOpacity = {255, 255, 255, 255},
//        };
//        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
//        if (ptGameBGCL == NULL)
//        {
//            printf("menu layer init failed\n");
//        }
//        
//        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
//    } while (0);
    
    do {
        static const char *pchItems[] = {
            "Very Easy",
            "Easy",
            "Normal",
            "Hard",
            "Insane"
        };
        tnsq_gfx_layer_menu_cfg_t tMenuCFG = {
            .tItemGeneral = {
                .chStringCount = sizeof(pchItems) >> 2,
                .pchStringTable = pchItems,
                .tItemSize = tItemSize,
                .tItemPadding = 0,
                .chShowItemNum = chShowItemNum,
                .nFinishInMs = 150,
                .ptFont = (struct arm_2d_font_t *)&ARM_2D_FONT_16x24,
            },
            .tItemNormal = {
                .tColor = {
                    .box = __RGB(0x6d, 0x54, 0x84),
                    .font = __RGB(0x94, 0xd2, 0x52),
                },
                .chOpacity = 255,
            },
            .tItemSelected = {
                .tColor = {
                    .box = __RGB(0xff, 0xff, 0xff),
                    .font = __RGB(0x6d, 0x54, 0x84),
                },
                .chOpacity = 255,
            },
        };
        
        tnsq_gfx_layer_menu_t *ptMenuLayer = tnsq_gfx_layer_menu_init(&tMenuCFG);
        if (ptMenuLayer == NULL)
        {
            printf("menu layer init failed\n");
        }
        
        return tnsq_gfx_register_layer_to_stage(ptStage, ptMenuLayer);
    } while (0);
}

rt_uint8_t tetris_num_layer_level(tnsq_gfx_stage_t *ptStage)
{
    arm_2d_size_t tScreenSize = tnsq_gfx_get_screen_size(&DISP0_ADAPTER);
    
//    do {
//        tnsq_gfx_layer_bg_cl_cfg_t tGameBGCLCFG = {
//            .tType = TNSQ_GFX_BG_CL_NORMAL,
//            .chOpacity = 255,
//            .ptBackGroundColorMask = NULL,
//            .tRegion = {
//                .tLocation = {0},
//                .tSize = tScreenSize,
//            },
//            .tColor = GLCD_COLOR_BLACK,
//            .borderOpacity = NULL,
//            .cornerOpacity = NULL,
//        };
//        tnsq_gfx_layer_bg_cl_t *ptGameBGCL = tnsq_gfx_layer_bg_cl_init(&tGameBGCLCFG);
//        if (ptGameBGCL == NULL)
//        {
//            printf("menu layer init failed\n");
//        }
//        
//        tnsq_gfx_register_layer_to_stage(ptStage, ptGameBGCL);
//    } while (0);
    
    do {
        tnsq_gfx_layer_num_cfg_t tNumCFG = {
            .chNum = 10,
            .chShowItemNum = 3,
            .nFinishInMs = 100,
            .tColor = {
                .background = __RGB(0x6d, 0x54, 0x84),
                .font = __RGB(0x94, 0xd2, 0x52),
            },
            .tPadding = {
                .pre = 3,
                .next = 3,
            },
            .ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A4_DIGITS_ONLY,
        };
        
        tnsq_gfx_layer_num_t *ptNumLayer = tnsq_gfx_layer_num_init(&tNumCFG);
        if (ptNumLayer == NULL)
        {
            printf("num layer init failed\n");
        }
        
        return tnsq_gfx_register_layer_to_stage(ptStage, ptNumLayer);
    } while (0);
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif