/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __GE_COLOR_H__
#define __GE_COLOR_H__

#include "arm_2d_helper.h"

typedef __arm_2d_color_t ge_color_t;

#define GE_COLOR_BLACK          (ge_color_t){GLCD_COLOR_BLACK}
#define GE_COLOR_NAVY           (ge_color_t){GLCD_COLOR_NAVY}
#define GE_COLOR_DARK_GREEN     (ge_color_t){GLCD_COLOR_DARK_GREEN}
#define GE_COLOR_DARK_CYAN      (ge_color_t){GLCD_COLOR_DARK_CYAN}
#define GE_COLOR_MAROON         (ge_color_t){GLCD_COLOR_MAROON}
#define GE_COLOR_PURPLE         (ge_color_t){GLCD_COLOR_PURPLE}
#define GE_COLOR_OLIVE          (ge_color_t){GLCD_COLOR_OLIVE}
#define GE_COLOR_LIGHT_GREY     (ge_color_t){GLCD_COLOR_LIGHT_GREY}
#define GE_COLOR_DARK_GREY      (ge_color_t){GLCD_COLOR_DARK_GREY}
#define GE_COLOR_BLUE           (ge_color_t){GLCD_COLOR_BLUE}
#define GE_COLOR_GREEN          (ge_color_t){GLCD_COLOR_GREEN}
#define GE_COLOR_CYAN           (ge_color_t){GLCD_COLOR_CYAN}
#define GE_COLOR_RED            (ge_color_t){GLCD_COLOR_RED}
#define GE_COLOR_MAGENTA        (ge_color_t){GLCD_COLOR_MAGENTA}
#define GE_COLOR_YELLOW         (ge_color_t){GLCD_COLOR_YELLOW}
#define GE_COLOR_WHITE          (ge_color_t){GLCD_COLOR_WHITE}

#endif