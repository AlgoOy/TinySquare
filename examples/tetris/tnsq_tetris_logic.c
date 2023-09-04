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
    
static rt_uint8_t bg_layer_id = 0;
static rt_uint8_t interface_layer_id = 0;
static rt_uint8_t text_layer_id = 0;

static tnsq_gfx_user_map_t s_tInterfaceCells[TNSQ_TETRIS_X_COUNT][TNSQ_TETRIS_Y_COUNT] = {0};

rt_bool_t bls_map[TNSQ_TETRIS_X_COUNT][TNSQ_TETRIS_Y_COUNT] = {0};

static rt_uint16_t score = 0;

static tnsq_gfx_stage_t *ptStage = NULL;
static tnsq_gfx_layer_text_t *textLayerPtr = NULL;

static tnsq_gfx_stage_t *ptMenuStage = NULL;

static rt_uint8_t menuLayerSelectID = 0;
static tnsq_gfx_layer_menu_t *menuLayerSelectPtr = NULL;

static rt_uint8_t menuLayerDiffcultyID = 0;
static tnsq_gfx_layer_menu_t *menuLayerDiffcultyPtr = NULL;

static rt_uint8_t numLayerLevelID = 0;
static tnsq_gfx_layer_num_t *numLayerLevelPtr = NULL;

static rt_uint32_t s_gameMode = 0;
static rt_uint8_t s_gameLevel = 0;

static struct tetris_block_t 
{
    tnsq_gfx_user_map_t space[4][4];
} block[7][4];

static void _tetris_register_layer(void)
{
    // initial stage
    ptStage = tetris_game_stage_init();
    
    arm_2d_scene_player_switch_to_next_scene(&DISP0_ADAPTER);
    
    tnsq_gfx_apply_for_refresh();
    
    // initial bg layer
    bg_layer_id = tetris_init_bg_layer(ptStage);
    
    // initial bg_cl layer
    tetris_init_bg_cl_layer(ptStage);
    
    // initial interface layer
    interface_layer_id = tetris_init_interface_layer(ptStage, s_tInterfaceCells[0]);
    
    // initial text layer
    text_layer_id = tetris_init_text_layer(ptStage);
}

static void _tetris_init_interface(void)
{
    for (int i = 0; i < TNSQ_TETRIS_X_COUNT-1; i ++)
    {
        s_tInterfaceCells[i][0] = BOARD_BLOCK_INFO;
        bls_map[i][0] = RT_TRUE;
        
        s_tInterfaceCells[i][TNSQ_TETRIS_Y_COUNT - 1] = BOARD_BLOCK_INFO;
        bls_map[i][TNSQ_TETRIS_Y_COUNT - 1] = RT_TRUE;
        
        s_tInterfaceCells[i][TNSQ_TETRIS_Y_GAME_COUNT] = BOARD_BLOCK_INFO;
        bls_map[i][TNSQ_TETRIS_Y_GAME_COUNT] = RT_TRUE;        
    }
    for (int i = 0; i < TNSQ_TETRIS_Y_COUNT; i ++)
    {
        s_tInterfaceCells[TNSQ_TETRIS_X_COUNT - 1][i] = BOARD_BLOCK_INFO;
        bls_map[TNSQ_TETRIS_X_COUNT - 1][i] = RT_TRUE;
    }
}
    
static void _tetris_init_block(void)
{
    for (int i = 0; i <= 2; i ++)
    {
        block[0][0].space[1][i] = T_BLOCK_INFO;
    }
    block[0][0].space[2][1] = T_BLOCK_INFO;
    
    for (int i = 1; i <= 3; i++)
    {
		block[1][0].space[i][1] = L_BLOCK_INFO;
    }
	block[1][0].space[3][2] = L_BLOCK_INFO;
    
    for (int i = 1; i <= 3; i++)
    {
		block[2][0].space[i][2] = J_BLOCK_INFO;
    }
	block[2][0].space[3][1] = J_BLOCK_INFO;
    
    for (int i = 0; i <= 1; i++)
	{
		block[3][0].space[1][i] = Z_BLOCK_INFO;
		block[3][0].space[2][i + 1] = Z_BLOCK_INFO;
        
		block[4][0].space[1][i + 1] = S_BLOCK_INFO;
		block[4][0].space[2][i] = S_BLOCK_INFO;
        
		block[5][0].space[1][i + 1] = O_BLOCK_INFO;
		block[5][0].space[2][i + 1] = O_BLOCK_INFO;
	}
    
    for (int i = 0; i <= 3;i++)
    {
		block[6][0].space[i][1] = I_BLOCK_INFO;
    }
    
    tnsq_gfx_user_map_t temp[4][4];
	for (int shape = 0; shape < 7; shape++)
	{
		for (int form = 0; form < 3; form++)
		{
			
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					block[shape][form + 1].space[i][j] = temp[3 - j][i];
				}
			}
		}
	}
}
 
static void _tetris_game_initial(void) 
{    
    // initial and register layer
    _tetris_register_layer();
    
    // initial game interface
    _tetris_init_interface();
    
    // initial block info
    _tetris_init_block();
    
    // initial seed
    srand((unsigned) arm_2d_helper_get_system_timestamp());
    
    textLayerPtr = tnsq_gfx_get_layer_ptr(ptStage, text_layer_id);
    
    tnsq_gfx_layer_text_printf(textLayerPtr, "%d", score);
}

static void _tetris_draw_block(rt_uint8_t shape, rt_uint8_t form, rt_uint8_t x, rt_uint8_t y)
{
    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
            if (block[shape][form].space[i][j].bIsDirty)
            {
                s_tInterfaceCells[x+i][y+j] = block[shape][form].space[i][j];
            }
        }
    }
}

static void _tetris_clear_block(rt_uint8_t shape, rt_uint8_t form, rt_uint8_t x, rt_uint8_t y)
{
    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
            if (block[shape][form].space[i][j].bIsDirty)
            {
                s_tInterfaceCells[x+i][y+j] = CLEAR_BLOCK_INFO;
            }
        }
    }
}

static rt_bool_t _tetris_is_legal(rt_uint8_t shape, rt_uint8_t form, rt_uint8_t x, rt_uint8_t y)
{
    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0; j < 4; j ++)
        {
            if (block[shape][form].space[i][j].bIsDirty && bls_map[x+i][y+j])
            {
                return RT_FALSE;
            }
        }
    }
    return RT_TRUE;
}

static rt_bool_t _tetris_judge()
{
    for (int i = TNSQ_TETRIS_X_COUNT - 2; i > 4; i --)
    {
        int sum = 0;
        for (int j = 1; j < TNSQ_TETRIS_Y_GAME_COUNT; j ++)
        {
            sum += bls_map[i][j];
        }
        
        if (sum == 0)
        {
            break;
        }
        
        if (sum == TNSQ_TETRIS_Y_GAME_COUNT - 1)
        {
            score += 100;
            tnsq_gfx_layer_text_printf(textLayerPtr, "%d", score);
            for (int j = 1; j < TNSQ_TETRIS_Y_GAME_COUNT; j ++)
            {
                s_tInterfaceCells[i][j] = CLEAR_BLOCK_INFO;
                bls_map[i][j] = RT_FALSE;
            }
            
            for (int m = i; m > 1; m --)
            {
                sum = 0;
                
                for (int n = 1; n < TNSQ_TETRIS_Y_GAME_COUNT; n ++)
                {
                    sum += bls_map[m - 1][n];
                    bls_map[m][n] = bls_map[m - 1][n];
                    if (bls_map[m][n] == RT_TRUE)
                    {
                        s_tInterfaceCells[m][n] = s_tInterfaceCells[m-1][n];
                        s_tInterfaceCells[m][n].bIsDirty = RT_TRUE;
                        s_tInterfaceCells[m-1][n] = CLEAR_BLOCK_INFO;
                    }
                }
                
                if(sum == 0)
                {
                    return RT_FALSE;
                }
            }
        }
    }
    
    for (int j = 1; j < TNSQ_TETRIS_Y_GAME_COUNT; j ++)
    {
        // Game Over!
        if (bls_map[1][j])
        {
            printf("Game Over!\n");
            while(1);
        }
    }
    return RT_TRUE;
}    

static int _tetris_evt_handler(void)
{
    tnsq_evt_key_t tKey = {0};
    rt_err_t tErr = tnsq_evt_itc_get(&tKey, RT_WAITING_NO);
    while(tErr != -RT_ETIMEOUT && tErr != -RT_ERROR)
    {
        if(tKey.tEvent != TNSQ_EVT_KEY_EVENT_PRESSED && tKey.tEvent != TNSQ_EVT_KEY_EVENT_LONG_PRESSED)
        {
            tErr = tnsq_evt_itc_get(&tKey, RT_WAITING_NO);
            continue;
        }
        else
        {
            switch (tKey.tDirection) 
            {
            case TNSQ_EVT_KEY_DERECTION_UP:
                return 1;
            case TNSQ_EVT_KEY_DERECTION_DOWN:
                return 2;
            case TNSQ_EVT_KEY_DERECTION_LEFT:
                return 3;
            case TNSQ_EVT_KEY_DERECTION_RIGHT:
                return 4;
            default:
                return 0;
            }
        }
    }
    return 0;
}

static void _tetris_game_logic(void)
{
    rt_uint8_t shape = rand() % 7, form = rand() % 4;
    
    while (1)
    {
        int t = 0;
        rt_uint8_t next_shape = rand() % 7, next_form = rand() % 4;
        rt_uint8_t x = 0, y = (TNSQ_TETRIS_Y_GAME_COUNT - 2) / 2;
        _tetris_draw_block(next_shape, next_form, TNSQ_TETRIS_NEXT_BLOCK_X, TNSQ_TETRIS_NEXT_BLOCK_Y);
        
        while (1)
        {
            int key = 0;
            _tetris_draw_block(shape, form, x, y);
            tnsq_gfx_apply_for_refresh();
            
            if (t == 0)
            {
                t = s_gameMode;
            }
            while (--t)
            {
                if ((key = _tetris_evt_handler()) != 0)
                {
                    break;
                }
            }
            if (t == 0)
            {
                if (_tetris_is_legal(shape, form, x + 1, y) == RT_FALSE)
                {
                    for (int i = 0; i < 4; i ++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (block[shape][form].space[i][j].bIsDirty == RT_TRUE)
                            {
                                bls_map[x+i][y+j] = RT_TRUE;
                            }
                        }
                    }
                    while (_tetris_judge() == RT_FALSE);
                    break;
                }
                else
                {
                    _tetris_clear_block(shape, form, x, y);
                    x++;
                }
            }
            else
            {
                switch (key)
                {
                case 1:
                    if (_tetris_is_legal(shape, (form + 1) % 4, x, y) == RT_TRUE)
                    {
                        _tetris_clear_block(shape, form, x, y);
                        form = (form + 1) % 4;
                    }
                    break;
                case 2:
                    if (_tetris_is_legal(shape, form, x + 1, y) == RT_TRUE)
                    {
                        _tetris_clear_block(shape, form, x, y);
                        x++;
                    }
                    break;
                case 3:
                    if (_tetris_is_legal(shape, form, x, y - 1) == RT_TRUE)
                    {
                        _tetris_clear_block(shape, form, x, y);
                        y--;
                    }
                    break;
                case 4:
                    if (_tetris_is_legal(shape, form, x, y + 1) == RT_TRUE)
                    {
                        _tetris_clear_block(shape, form, x, y);
                        y++;
                    }
                    break;
                }
            }
        }
        shape = next_shape, form = next_form;
        _tetris_clear_block(next_shape, next_form, TNSQ_TETRIS_NEXT_BLOCK_X, TNSQ_TETRIS_NEXT_BLOCK_Y);
    }
}

static void _tetris_game_menu_initial(void)
{
    ptMenuStage = tetris_menu_stage_init();
    
    menuLayerSelectID = tetris_menu_layer_select(ptMenuStage);
	
	menuLayerDiffcultyID = tetris_memu_layer_diffculty(ptMenuStage);
	tnsq_gfx_make_layer_invisible(ptMenuStage, menuLayerDiffcultyID);
	
	numLayerLevelID = tetris_num_layer_level(ptMenuStage);
	tnsq_gfx_make_layer_invisible(ptMenuStage, numLayerLevelID);
	
	tnsq_gfx_apply_for_refresh();
}

static void _tetris_game_get_menu_result(void)
{
	s_gameMode = 400000;
	s_gameLevel = 0;
	
    menuLayerSelectPtr = tnsq_gfx_get_layer_ptr(ptMenuStage, menuLayerSelectID);
	menuLayerDiffcultyPtr = tnsq_gfx_get_layer_ptr(ptMenuStage, menuLayerDiffcultyID);
	numLayerLevelPtr = tnsq_gfx_get_layer_ptr(ptMenuStage, numLayerLevelID);
	
	rt_int8_t chItemIdx = -1;
	do {
		while((chItemIdx = tnsq_gfx_layer_menu_get_item_idx(menuLayerSelectPtr)) == -1)
		{
			tnsq_gfx_apply_for_refresh();
		}
		
		switch (chItemIdx)
		{
		case 0:
			do {
				tnsq_gfx_make_layer_invisible(ptMenuStage, menuLayerSelectID);
				tnsq_gfx_make_layer_visible(ptMenuStage, menuLayerDiffcultyID);
				tnsq_gfx_apply_for_refresh();
				
				while((chItemIdx = tnsq_gfx_layer_menu_get_item_idx(menuLayerDiffcultyPtr)) == -1)
				{
					tnsq_gfx_apply_for_refresh();
				}
				
				switch (chItemIdx)
				{
				case 0:
					s_gameMode = 600000;
					break;
				case 1:
					s_gameMode = 500000;
					break;
				case 2:
					s_gameMode = 400000;
					break;
				case 3:
					s_gameMode = 300000;
					break;
				case 4:
					s_gameMode = 200000;
					break;
				}
				
				tnsq_gfx_make_layer_invisible(ptMenuStage, menuLayerDiffcultyID);
				tnsq_gfx_make_layer_visible(ptMenuStage, menuLayerSelectID);
				tnsq_gfx_apply_for_refresh();
			} while (0);
			chItemIdx = -1;
			break;
		case 1:
			do {
				tnsq_gfx_make_layer_invisible(ptMenuStage, menuLayerSelectID);
				tnsq_gfx_make_layer_visible(ptMenuStage, numLayerLevelID);
				tnsq_gfx_apply_for_refresh();
				
				while((chItemIdx = tnsq_gfx_layer_num_get_item_idx(numLayerLevelPtr)) == -1)
				{
					tnsq_gfx_apply_for_refresh();
				}
				
				s_gameLevel = chItemIdx;
				
				tnsq_gfx_make_layer_invisible(ptMenuStage, numLayerLevelID);
				tnsq_gfx_make_layer_visible(ptMenuStage, menuLayerSelectID);
				tnsq_gfx_apply_for_refresh();
			} while (0);
			chItemIdx = -1;
			break;
		case 2:
			break;
		}
	} while (chItemIdx != 2);
}
    
void tetris_task_entry(void *ptParam)
{
    (void)ptParam;
    
    disp_adapter0_init();
    
    _tetris_game_menu_initial();
    
    _tetris_game_get_menu_result();
    
    _tetris_game_initial();
    
    tnsq_gfx_apply_for_refresh();
    
    _tetris_game_logic();
}
    
#if defined(__clang__)
#   pragma clang diagnostic pop
#endif