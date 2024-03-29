/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */

#include "arm_2d.h"

#define __TNSQ_GFX_STAGE_IMPLEMENT__
#include "tnsq_gfx_stage.h"

#include "__tnsq_gfx_common.h"
#include "__tnsq_evt_common.h"

#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

// todo:just for debug
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

/**
 * @brief The function will be called when the stage is disposed.
 * @param ptScene is a pointer to the stage.
 * @return none
*/
static void _tnsq_gfx_on_stage_depose(arm_2d_scene_t *ptScene)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
    
    this.use_as__arm_2d_scene_t.ptPlayer = NULL;
    
    tnsq_gfx_layer_base_t *ptLayer = NULL;
    tnsq_gfx_layer_base_t *ptLayersList = this.ptLayersList;
    while (ptLayersList != NULL)
    {
        if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_MENU)
        {
            tnsq_evt_get_unlock(tnsq_evt_get_ctrl());
        }
		else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_NUM)
		{
			tnsq_evt_get_unlock(tnsq_evt_get_ctrl());
		}
        
        ptLayer = ptLayersList;
        ptLayersList = ptLayersList->ptNext;
        
        if (!ptLayer->blsUserAllocated)
        {
            free(ptLayer);
        }
    }

    if (!this.blsUserAllocated) {
        free(ptThis);
    }
}

/**
 * @brief The function will be called when the stage is draw background.
 * @param ptScene is a pointer to the stage.
 * @return none
*/
static void _tnsq_gfx_on_stage_background_start(arm_2d_scene_t *ptScene)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

/**
 * @brief The function will be called when the stage is draw background complete.
 * @param ptScene is a pointer to the stage.
 * @return none
*/
static void _tnsq_gfx_on_stage_background_complete(arm_2d_scene_t *ptScene)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

/**
 * @brief The function will be called when the stage is draw frame start.
 * @param ptScene is a pointer to the stage.
 * @return none
*/
static void _tnsq_gfx_on_stage_frame_start(arm_2d_scene_t *ptScene)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

/**
 * @brief The function will be called when the stage is draw frame complete.
 * @param ptScene is a pointer to the stage.
 * @return none
*/
static void _tnsq_gfx_on_stage_frame_complete(arm_2d_scene_t *ptScene)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
    
    tnsq_gfx_layer_base_t *ptLayersList = this.ptLayersList;
    while (ptLayersList != NULL)
    {
        if (ptLayersList->bIsVisible == RT_TRUE)
        {
            if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_CELL)
            {
                tnsq_gfx_clear_layer_cell_dirty_cell((tnsq_gfx_layer_cell_t *)ptLayersList);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_USER)
            {
                tnsq_gfx_clear_layer_user_dirty_cell((tnsq_gfx_layer_user_t *)ptLayersList);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_TEXT)
            {
                tnsq_gfx_clear_layer_text_dirty_region((tnsq_gfx_layer_text_t *)ptLayersList);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_MENU)
            {
                tnsq_gfx_clear_layer_menu_dirty_region((tnsq_gfx_layer_menu_t *)ptLayersList);
                tnsq_gfx_layer_menu_evt_handle((tnsq_gfx_layer_menu_t *)ptLayersList);
                tnsq_evt_get_lock(tnsq_evt_get_ctrl());
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_NUM)
            {
                tnsq_gfx_clear_layer_num_dirty_region((tnsq_gfx_layer_num_t *)ptLayersList);
                tnsq_gfx_layer_num_evt_handle((tnsq_gfx_layer_num_t *)ptLayersList);
                tnsq_evt_get_lock(tnsq_evt_get_ctrl());
            }
        }
        ptLayersList = ptLayersList->ptNext;
    }
}

/**
 * @brief The function will be called when the stage is switching out.
 * @param ptScene is a pointer to the stage.
 * @return none
*/
static void _tnsq_gfx_before_stage_switching_out(arm_2d_scene_t *ptScene)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
}

/**
 * @brief The function will be called when the stage is need to draw.
 * @param ptScene is a pointer to the stage.
 * @param ptTile is a pointer to the tile.
 * @param bIsNewFrame is a bool value to indicate whether it is a new frame.
 * @return Return the state of the draw function.
*/
static IMPL_PFB_ON_DRAW(_tnsq_gfx_pfb_draw_stage_handler)
{
    tnsq_gfx_stage_t *ptThis = (tnsq_gfx_stage_t *)pTarget;
    ARM_2D_UNUSED(ptTile);
    ARM_2D_UNUSED(bIsNewFrame);
    
    arm_2d_canvas(ptTile, __top_canvas) {
    /*-----------------------draw the foreground begin-----------------------*/
    
    tnsq_evt_get_unlock(tnsq_evt_get_ctrl());
    
    tnsq_gfx_layer_base_t *ptLayersList = this.ptLayersList;
    while (ptLayersList != NULL)
    {
        if (ptLayersList->bIsVisible == RT_TRUE)
        {
            if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_CELL)
            {
                tnsq_gfx_refresh_layer_cell((tnsq_gfx_layer_cell_t *)ptLayersList, ptTile, this.use_as__arm_2d_scene_t.ptDirtyRegion);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_USER)
            {
                tnsq_gfx_refresh_layer_user((tnsq_gfx_layer_user_t *)ptLayersList, ptTile, this.use_as__arm_2d_scene_t.ptDirtyRegion, bIsNewFrame);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_BG)
            {
                tnsq_gfx_refresh_layer_bg((tnsq_gfx_layer_bg_t *)ptLayersList, ptTile);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_BG_CL)
            {
                tnsq_gfx_refresh_layer_bg_cl((tnsq_gfx_layer_bg_cl_t *)ptLayersList, ptTile, bIsNewFrame);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_TEXT)
            {
                tnsq_gfx_refresh_layer_text((tnsq_gfx_layer_text_t *)ptLayersList, ptTile, this.use_as__arm_2d_scene_t.ptDirtyRegion);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_MENU)
            {
                tnsq_gfx_refresh_layer_menu((tnsq_gfx_layer_menu_t *)ptLayersList, ptTile, this.use_as__arm_2d_scene_t.ptDirtyRegion, bIsNewFrame);
            }
            else if (ptLayersList->tType == TNSQ_GFX_LAYER_TYPE_NUM)
            {
                tnsq_gfx_refresh_layer_num((tnsq_gfx_layer_num_t *)ptLayersList, ptTile, this.use_as__arm_2d_scene_t.ptDirtyRegion, bIsNewFrame);
            }
            arm_2d_op_wait_async(NULL);
        }
        ptLayersList = ptLayersList->ptNext;
    }

    /*-----------------------draw the foreground end  -----------------------*/
    }
    arm_2d_op_wait_async(NULL);

    return arm_fsm_rt_cpl;
}

/**
 * @brief The function will initialize the stage.
 * @param ptCFG is a pointer to the stage configuration.
 * @param ptThis is a pointer to the stage.
 * @return Return a pointer to the stage.
*/
ARM_NONNULL(1) tnsq_gfx_stage_t *__tnsq_gfx_stage_init(tnsq_gfx_stage_cfg_t *ptCFG, tnsq_gfx_stage_t *ptThis)
{
    assert(ptCFG != NULL);
    
    rt_bool_t blsUserAllocated = RT_FALSE;
    
    IMPL_ARM_2D_REGION_LIST(s_tDirtyRegions, static)
        
        ADD_LAST_REGION_TO_LIST(s_tDirtyRegions, 0),
        
    END_IMPL_ARM_2D_REGION_LIST(s_tDirtyRegions)
    
    s_tDirtyRegions[dimof(s_tDirtyRegions)-1].bUpdated = false;
    s_tDirtyRegions[dimof(s_tDirtyRegions)-1].ptNext = NULL;
    
    if (ptThis == NULL)
    {
        ptThis = (tnsq_gfx_stage_t *)malloc(sizeof(tnsq_gfx_stage_t));
        if (ptThis == NULL)
        {
            return NULL;
        }
    }
    else
    {
        blsUserAllocated = RT_TRUE;
    }

    memset(ptThis, 0, sizeof(tnsq_gfx_stage_t));

    *ptThis = (tnsq_gfx_stage_t){
        .use_as__arm_2d_scene_t = {
            .fnScene        = &_tnsq_gfx_pfb_draw_stage_handler,
            .ptDirtyRegion  = (arm_2d_region_list_item_t *)s_tDirtyRegions,

            //.fnOnBGStart    = &_tnsq_gfx_on_stage_background_start,
            //.fnOnBGComplete = &_tnsq_gfx_on_stage_background_complete,
            //.fnOnFrameStart = &_tnsq_gfx_on_stage_frame_start,
            //.fnBeforeSwitchOut = &_tnsq_gfx_before_stage_switching_out,
            .fnOnFrameCPL   = &_tnsq_gfx_on_stage_frame_complete,
            .fnDepose       = &_tnsq_gfx_on_stage_depose,
        },
        .blsUserAllocated = blsUserAllocated,
        .chLayerID = 0,
        .tStageCFG = *ptCFG,
        .ptLayersList = NULL,
    };
    
    tnsq_gfx_register_disp_adapter_to_crtl(tnsq_gfx_get_ctrl(), &ptCFG->ptDispAdapter);

    arm_2d_scene_player_append_scenes(ptCFG->ptDispAdapter.ptPlayer, &this.use_as__arm_2d_scene_t, 1);
    
    return ptThis;
}

/**
 * @brief The function will register the layer to the stage.
 * @param ptThis is a pointer to the stage.
 * @param ptLayer is a pointer to the layer.
 * @return Return the layer ID.
*/
ARM_NONNULL(1, 2) rt_uint8_t tnsq_gfx_register_layer_to_stage(tnsq_gfx_stage_t *ptThis, void *ptLayer)
{
    assert(ptThis != NULL);
    assert(ptLayer != NULL);
    
    tnsq_gfx_layer_base_t *ptLayerBase = (tnsq_gfx_layer_base_t *)ptLayer;
    assert(ptLayerBase->wMagic == TNSQ_GFX_LAYER_BASE_MAGIC);
    
    tnsq_gfx_layer_base_t *ptLayerListPtr = this.ptLayersList;
    
    if (ptLayerBase->tType == TNSQ_GFX_LAYER_TYPE_CELL)
    {
        tnsq_gfx_layer_cell_cal_pixel((tnsq_gfx_layer_cell_t *)ptLayerBase, this.tStageCFG.ptDispAdapter.ptPlayer);
    }
    else if (ptLayerBase->tType == TNSQ_GFX_LAYER_TYPE_USER)
    {
        tnsq_gfx_layer_user_cal_pixel((tnsq_gfx_layer_user_t *)ptLayerBase, this.tStageCFG.ptDispAdapter.ptPlayer);
    }
    else if (ptLayerBase->tType == TNSQ_GFX_LAYER_TYPE_MENU)
    {
        tnsq_gfx_layer_menu_get_dirty_region((tnsq_gfx_layer_menu_t *)ptLayerBase, this.tStageCFG.ptDispAdapter.ptPlayer);
    }
    else if (ptLayerBase->tType == TNSQ_GFX_LAYER_TYPE_NUM)
    {
        tnsq_gfx_layer_num_get_dirty_region((tnsq_gfx_layer_num_t *)ptLayerBase, this.tStageCFG.ptDispAdapter.ptPlayer);
    }
    
    ptLayerBase->u7LayerID = this.chLayerID ++;
    ptLayerBase->ptNext = NULL;
    
    if (ptLayerListPtr == NULL)
    {
        this.ptLayersList = ptLayerBase;
    }
    else
    {
        while (ptLayerListPtr->ptNext != NULL)
        {
            ptLayerListPtr = ptLayerListPtr->ptNext;
        }
        ptLayerListPtr->ptNext = ptLayerBase;
    }
    
    return ptLayerBase->u7LayerID;
}

/**
 * @brief The function will remove the layer from the stage.
 * @param ptThis is a pointer to the stage.
 * @param chLayerID is the layer ID.
 * @return none
*/
ARM_NONNULL(1) void tnsq_gfx_remove_layer(tnsq_gfx_stage_t *ptThis, rt_uint8_t chLayerID)
{
    assert(ptThis != NULL);
    
    tnsq_gfx_layer_base_t *ptLayerListPtr = this.ptLayersList;
    
    if (ptLayerListPtr == NULL)
    {
        return;
    }
    
    if (ptLayerListPtr->u7LayerID == chLayerID)
    {
        this.ptLayersList = ptLayerListPtr->ptNext;
        free(ptLayerListPtr);
        arm_2d_scene_player_update_scene_background(this.tStageCFG.ptDispAdapter.ptPlayer);
        return;
    }
    
    tnsq_gfx_layer_base_t *ptPreLayerListPtr = ptLayerListPtr;
    while ((ptLayerListPtr = ptLayerListPtr->ptNext) != NULL)
    {
        if (ptLayerListPtr->u7LayerID == chLayerID)
        {
            ptPreLayerListPtr->ptNext = ptLayerListPtr->ptNext;
            free(ptLayerListPtr);
            arm_2d_scene_player_update_scene_background(this.tStageCFG.ptDispAdapter.ptPlayer);
            return;
        }
        ptPreLayerListPtr = ptLayerListPtr;
    }
}

/**
 * @brief The function will make the layer visible.
 * @param ptThis is a pointer to the stage.
 * @param chLayerID is the layer ID.
 * @return none
*/
void tnsq_gfx_make_layer_visible(tnsq_gfx_stage_t *ptThis, rt_uint8_t chLayerID)
{
    assert(ptThis != NULL);
    
    tnsq_gfx_layer_base_t *ptLayerListPtr = this.ptLayersList;
    
    while (ptLayerListPtr != NULL)
    {
        if (ptLayerListPtr->u7LayerID == chLayerID)
        {
            ptLayerListPtr->bIsVisible = RT_TRUE;
            arm_2d_scene_player_update_scene_background(this.tStageCFG.ptDispAdapter.ptPlayer);
            return;
        }
        ptLayerListPtr = ptLayerListPtr->ptNext;
    }
}

/**
 * @brief The function will make the layer invisible.
 * @param ptThis is a pointer to the stage.
 * @param chLayerID is the layer ID.
 * @return none
*/
void tnsq_gfx_make_layer_invisible(tnsq_gfx_stage_t *ptThis, rt_uint8_t chLayerID)
{
    assert(ptThis != NULL);
    
    tnsq_gfx_layer_base_t *ptLayerListPtr = this.ptLayersList;
    
    while (ptLayerListPtr != NULL)
    {
        if (ptLayerListPtr->u7LayerID == chLayerID)
        {
            ptLayerListPtr->bIsVisible = RT_FALSE;
            arm_2d_scene_player_update_scene_background(this.tStageCFG.ptDispAdapter.ptPlayer);
            return;
        }
        ptLayerListPtr = ptLayerListPtr->ptNext;
    }
}

/**
 * @brief The function will get the layer pointer.
 * @param ptThis is a pointer to the stage.
 * @param chLayerID is the layer ID.
 * @return Return a pointer to the layer.
*/
void *tnsq_gfx_get_layer_ptr(tnsq_gfx_stage_t *ptThis, rt_uint8_t chLayerID)
{
    assert(ptThis != NULL);
    
    tnsq_gfx_layer_base_t *ptLayerListPtr = this.ptLayersList;
    
    while (ptLayerListPtr != NULL)
    {
        if (ptLayerListPtr->u7LayerID == chLayerID)
        {
            return ptLayerListPtr;
        }
        ptLayerListPtr = ptLayerListPtr->ptNext;
    }
    
    return NULL;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif
