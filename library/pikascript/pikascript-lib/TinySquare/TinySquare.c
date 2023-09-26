#include "pikaScript.h"
#include "tnsq_gfx_layer_bg_cl.h"

void TinySquare___init__(PikaObj *self)
{
    obj_setInt(self, "BG_CL_NORMAL", TNSQ_GFX_BG_CL_NORMAL);
    obj_setInt(self, "BG_CL_BOX", TNSQ_GFX_BG_CL_BOX);
    obj_setInt(self, "BG_CL_BORDER", TNSQ_GFX_BG_CL_BORDER);
    obj_setInt(self, "TEXT_FONT_6X8", 0);
    obj_setInt(self, "TEXT_FONT_16X24", 1);
    obj_setInt(self, "TEXT_FONT_A2_DIGITS_ONLY", 2);
    obj_setInt(self, "TEXT_FONT_A4_DIGITS_ONLY", 3);
    obj_setInt(self, "TEXT_FONT_A8_DIGITS_ONLY", 4);
    obj_setInt(self, "KEY_UP", 1);
    obj_setInt(self, "KEY_DOWN", 2);
    obj_setInt(self, "KEY_LEFT", 3);
    obj_setInt(self, "KEY_RIGHT", 4);
    obj_setInt(self, "KEY_X", 5);
    obj_setInt(self, "KEY_Y", 6);
    obj_setInt(self, "KEY_A", 7);
    obj_setInt(self, "KEY_B", 8);
    obj_setInt(self, "KEY_EVENT_UP", 1);
    obj_setInt(self, "KEY_EVENT_DOWN", 2);
    obj_setInt(self, "KEY_EVENT_PRESSED", 3);
    obj_setInt(self, "KEY_EVENT_LONG_PRESSED", 4);
}

int TinySquare_RGB(PikaObj *self, int r, int g, int b)
{
    return __RGB(r, g, b);
}