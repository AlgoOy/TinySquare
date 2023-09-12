#include "TinySquare_Common.h"

arm_2d_font_t *get_font_ptr(int idx)
{
    arm_2d_font_t *ptFont = (arm_2d_font_t *)&ARM_2D_FONT_6x8;
    switch (idx)
    {
    case 0:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_6x8;
        break;
    case 1:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_16x24;
        break;
    case 2:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A2_DIGITS_ONLY;
        break;
    case 3:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A4_DIGITS_ONLY;
        break;
    case 4:
        ptFont = (arm_2d_font_t *)&ARM_2D_FONT_A8_DIGITS_ONLY;
        break;
    }
    return ptFont;
}