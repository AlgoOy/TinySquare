#include "pikaScript.h"
#include "tnsq_evt_key.h"

void TinySquare_EvtKey___init__(PikaObj *self)
{
    tnsq_evt_key_t _self = {0};
    obj_setStruct(self, "_self", self);
}

int TinySquare_EvtKey_update_key(PikaObj *self, int timeout)
{
    tnsq_evt_key_t *_self = obj_getStruct(self, "_self");
    return tnsq_evt_itc_get(_self, timeout);
}

int TinySquare_EvtKey_get_direction(PikaObj *self)
{
    tnsq_evt_key_t *_self = obj_getStruct(self, "_self");
    return _self->tDirection;
}

int TinySquare_EvtKey_get_event(PikaObj *self)
{
    tnsq_evt_key_t *_self = obj_getStruct(self, "_self");
    return _self->tEvent;
}