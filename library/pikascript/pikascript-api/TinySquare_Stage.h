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

#ifndef __TinySquare_Stage__H
#define __TinySquare_Stage__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_TinySquare_Stage(Args *args);

void TinySquare_Stage___init__(PikaObj *self);
Arg* TinySquare_Stage_get_layer(PikaObj *self, int chLayerID);
void TinySquare_Stage_invisible_layer(PikaObj *self, int chLayerID);
int TinySquare_Stage_register_layer(PikaObj *self, Arg* ptLayer);
void TinySquare_Stage_remove_layer(PikaObj *self, int chLayerID);
void TinySquare_Stage_visible_layer(PikaObj *self, int chLayerID);

#endif
