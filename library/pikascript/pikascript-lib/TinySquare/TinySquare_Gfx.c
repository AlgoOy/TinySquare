#include "pikaScript.h"
#include "tnsq_gfx.h"

void TinySquare_Gfx___init__(PikaObj *self)
{

}

void TinySquare_Gfx_refresh(PikaObj *self)
{
    tnsq_gfx_apply_for_refresh();
}