/*
 * [Warning!] This file is auto-generated by pika compiler.
 * Do not edit it manually.
 * The source code is *.pyi file.
 * More details: 
 * English Doc:
 * https://pikadoc.readthedocs.io/en/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 * Chinese Doc:
 * https://pikadoc.readthedocs.io/zh/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 */

#ifndef __TinySquare_LayerUser__H
#define __TinySquare_LayerUser__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_TinySquare_LayerUser(Args *args);

void TinySquare_LayerUser___init__(PikaObj *self, int hwXCount, int hwYCount, Arg* ptUserMap, Arg* ptFunc);
void TinySquare_LayerUser_draw_userMap(PikaObj *self, int hwX, int hwY, int Idx);

#endif