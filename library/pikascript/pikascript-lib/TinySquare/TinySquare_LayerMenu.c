#include "pikaScript.h"
#include "PikaStdData_Tuple.h"
#include "tnsq_gfx_layer_menu.h"

void TinySquare_LayerMenu___init__(PikaObj *self, PikaObj* strTable, int itemWidth, int itemHeight, PikaObj* itemNormal, PikaObj* itemSelect)
{
    int strCount = PikaStdData_Tuple_len(strTable);
    char** ptStrTable = (char**)malloc(sizeof(char*) * strCount);
    for (int i = 0; i < strCount; i++) {
        Arg* str = PikaStdData_Tuple_get(strTable, i);
        ptStrTable[i] = arg_getStr(str);
    }

    tnsq_gfx_layer_menu_cfg_t tCFG = {
        .tItemGeneral = {
            .pchFormatString = NULL,
            .chStringCount = strCount,
            .pchStringTable = (const char **)ptStrTable,
            .tItemSize = {
                .iWidth = itemWidth,
                .iHeight = itemHeight,
            },
            .tItemPadding = {0},
            .chShowItemNum = 3,
            .nFinishInMs = 150,
            .ptFont = NULL,
        },
        .tItemNormal = *(struct tItemFormat *)obj_getStruct(itemNormal, "_self"),
        .tItemSelected = *(struct tItemFormat *)obj_getStruct(itemSelect, "_self"),
    };
    tnsq_gfx_layer_menu_t *_self = tnsq_gfx_layer_menu_init(&tCFG);
    obj_setPtr(self, "_self", _self);
}

int TinySquare_LayerMenu_get_idx(PikaObj *self)
{
    tnsq_gfx_layer_menu_t *_self = obj_getPtr(self, "_self");
    return tnsq_gfx_layer_menu_get_item_idx(_self);
}