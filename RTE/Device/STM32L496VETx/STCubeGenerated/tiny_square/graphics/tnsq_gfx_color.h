/*
 * Copyright (c) 2023, AlgoOy
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2023-07-08     AlgoOy     the first version
 */
 
#ifndef __TNSQ_GFX_COLOR_H__
#define __TNSQ_GFX_COLOR_H__

#ifdef   __cplusplus
extern "C" {
#endif

#include "arm_2d_helper.h"

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#   pragma clang diagnostic ignored "-Wpadded"
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wpadded"
#endif

typedef __arm_2d_color_t tnsq_gfx_color_t;

#define TNSQ_GFX_COLOR_BLACK          (tnsq_gfx_color_t){GLCD_COLOR_BLACK}
#define TNSQ_GFX_COLOR_NAVY           (tnsq_gfx_color_t){GLCD_COLOR_NAVY}
#define TNSQ_GFX_COLOR_DARK_GREEN     (tnsq_gfx_color_t){GLCD_COLOR_DARK_GREEN}
#define TNSQ_GFX_COLOR_DARK_CYAN      (tnsq_gfx_color_t){GLCD_COLOR_DARK_CYAN}
#define TNSQ_GFX_COLOR_MAROON         (tnsq_gfx_color_t){GLCD_COLOR_MAROON}
#define TNSQ_GFX_COLOR_PURPLE         (tnsq_gfx_color_t){GLCD_COLOR_PURPLE}
#define TNSQ_GFX_COLOR_OLIVE          (tnsq_gfx_color_t){GLCD_COLOR_OLIVE}
#define TNSQ_GFX_COLOR_LIGHT_GREY     (tnsq_gfx_color_t){GLCD_COLOR_LIGHT_GREY}
#define TNSQ_GFX_COLOR_DARK_GREY      (tnsq_gfx_color_t){GLCD_COLOR_DARK_GREY}
#define TNSQ_GFX_COLOR_BLUE           (tnsq_gfx_color_t){GLCD_COLOR_BLUE}
#define TNSQ_GFX_COLOR_GREEN          (tnsq_gfx_color_t){GLCD_COLOR_GREEN}
#define TNSQ_GFX_COLOR_CYAN           (tnsq_gfx_color_t){GLCD_COLOR_CYAN}
#define TNSQ_GFX_COLOR_RED            (tnsq_gfx_color_t){GLCD_COLOR_RED}
#define TNSQ_GFX_COLOR_MAGENTA        (tnsq_gfx_color_t){GLCD_COLOR_MAGENTA}
#define TNSQ_GFX_COLOR_YELLOW         (tnsq_gfx_color_t){GLCD_COLOR_YELLOW}
#define TNSQ_GFX_COLOR_WHITE          (tnsq_gfx_color_t){GLCD_COLOR_WHITE}

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic pop
#endif

#ifdef   __cplusplus
}
#endif

#endif
