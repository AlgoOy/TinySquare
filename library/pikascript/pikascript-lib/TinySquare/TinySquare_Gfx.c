#include "pikaScript.h"
#include "tnsq_gfx.h"

void TinySquare_Gfx___init__(PikaObj *self)
{

}

void TinySquare_Gfx_refresh(PikaObj *self)
{
    tnsq_gfx_apply_for_refresh();
}

void TinySquare_Gfx_switch_stage(PikaObj *self)
{
    arm_2d_scene_player_switch_to_next_scene(&DISP0_ADAPTER);
    tnsq_gfx_apply_for_refresh();
}