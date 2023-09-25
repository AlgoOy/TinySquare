/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#define __TNSQ_GFX_LAYER_CELL_IMPLEMENT__
#include "tnsq_gfx_layer_cell.h"

#include "arm_2d.h"

#include <stdlib.h>

// todo :delete
#include <stdio.h>

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
    
static int __idx = -1;

/**
 * @brief The function will refresh the cell layer.
 * @param ptThis is a pointer to the cell layer.
 * @param ptTile is a pointer to the tile.
 * @param ptDirtyRegion is a pointer to the dirty region.
 * @return none
*/
void tnsq_gfx_refresh_layer_cell(tnsq_gfx_layer_cell_t *ptThis, const arm_2d_tile_t *ptTile, arm_2d_region_list_item_t *ptDirtyRegion)
{
    for (int curIdx = 0; curIdx < this.tCount.totalCount; curIdx ++)
    {
        if (this.ptCells[curIdx].bIsDirty == RT_TRUE)
        {
            int16_t iX = (curIdx % this.tCount.hwXCount) * this.tPixel.hwXPixel;
            int16_t iY = (curIdx / this.tCount.hwXCount) * this.tPixel.hwYPixel;
            
            arm_2d_canvas(ptTile, __layer_cell_canvas)
            {                
                arm_2dp_fill_colour_with_opacity
                (
                    NULL,
                    ptTile,
                    &(arm_2d_region_t) {
                        .tLocation = {
                            .iX = iX,
                            .iY = iY,
                        },
                        .tSize = {
                            .iWidth = this.tPixel.hwXPixel,
                            .iHeight = this.tPixel.hwYPixel,
                        },
                    },
                    (__arm_2d_color_t)this.ptCells[curIdx].tColor,
                    this.ptCells[curIdx].chOpacity
                );
            }
            arm_2d_op_wait_async(NULL);
            
            if (ptDirtyRegion[0].bUpdated == false)
            {
                if (__idx == curIdx || __idx > curIdx)
                {
                    continue;
                }
                __idx = curIdx;
                
                ptDirtyRegion[0].tRegion = (arm_2d_region_t) {
                    .tLocation = {
                        .iX = iX,
                        .iY = iY,
                    },
                    .tSize = {
                        .iWidth = this.tPixel.hwXPixel,
                        .iHeight = this.tPixel.hwYPixel,
                    },
                };
                ptDirtyRegion[0].bUpdated = true;
            }
        }
    }
}

/**
 * @brief The function will clear the dirty cell.
 * @param ptThis is a pointer to the cell layer.
 * @return none
*/
void tnsq_gfx_clear_layer_cell_dirty_cell(tnsq_gfx_layer_cell_t *ptThis)
{
    for (int i = 0; i < this.tCount.totalCount; i ++)
    {
        if (this.ptCells[i].bIsDirty == RT_TRUE)
        {
            this.ptCells[i].bIsDirty = RT_FALSE;
        }
    }
    __idx = -1;
}

/**
 * @brief The function will draw the cell.
 * @param ptThis is a pointer to the cell layer.
 * @param iX is the x coordinate of the cell.
 * @param iY is the y coordinate of the cell.
 * @param chOpacity is the opacity of the cell.
 * @param tColor is the color of the cell.
 * @return none
*/
void tnsq_gfx_layer_cell_draw(tnsq_gfx_layer_cell_t *ptThis, rt_uint16_t iX, rt_uint16_t iY, rt_uint8_t chOpacity, COLOUR_INT tColor)
{
    rt_uint16_t pos = this.tCount.hwXCount * iY + iX;
    this.ptCells[pos].bIsDirty = RT_TRUE;
    this.ptCells[pos].chOpacity = chOpacity;
    this.ptCells[pos].tColor = tColor;
}

/**
 * @brief The function will calculate the pixel of the cell.
 * @param ptThis is a pointer to the cell layer.
 * @param ptDispAdapter is a pointer to the display adapter.
 * @return none
*/
void tnsq_gfx_layer_cell_cal_pixel(tnsq_gfx_layer_cell_t *ptThis, arm_2d_scene_player_t *ptDispAdapter)
{
    arm_2d_region_t tScreen = arm_2d_helper_pfb_get_display_area(
        &ptDispAdapter->use_as__arm_2d_helper_pfb_t);
    
    this.tPixel.hwXPixel = tScreen.tSize.iWidth / this.tCount.hwXCount;
    this.tPixel.hwYPixel = tScreen.tSize.iHeight / this.tCount.hwYCount;
}

/**
 * @brief The function will initialize the cell layer.
 * @param ptCFG is a pointer to the cell layer configuration.
 * @param ptThis is a pointer to the cell layer.
 * @return Return the pointer to the cell layer.
*/
ARM_NONNULL(1) tnsq_gfx_layer_cell_t *__tnsq_gfx_layer_cell_init(tnsq_gfx_layer_cell_cfg_t *ptCFG, tnsq_gfx_layer_cell_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_layer_cell_t *)malloc(sizeof(tnsq_gfx_layer_cell_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }
    
    memset(ptThis, 0, sizeof(tnsq_gfx_layer_cell_t));
    
    *ptThis = (tnsq_gfx_layer_cell_t) {
        .use_as__tnsq_gfx_layer_base_t = {
            .ptNext = NULL,
            .tType  = TNSQ_GFX_LAYER_TYPE_CELL,
            .blsUserAllocated = blsUserAllocated,
            .bIsVisible = RT_TRUE,
            .u7LayerID = 0,
            .wMagic = TNSQ_GFX_LAYER_BASE_MAGIC,
        },
        .tCount = {
            .hwXCount = ptCFG->hwXCount,
            .hwYCount = ptCFG->hwYCount,
            .totalCount = ptCFG->hwXCount * ptCFG->hwYCount,
        },
        .ptCells = ptCFG->ptCells,
    };
    
    return ptThis;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
