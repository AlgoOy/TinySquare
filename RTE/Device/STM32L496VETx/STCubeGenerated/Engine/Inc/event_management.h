#ifndef __EVENT_MANAGEMENT_H
#define __EVENT_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtdef.h"

typedef struct key_t {
	rt_uint8_t chValue;
	enum {
		Key_Invalid = 0x00,
		Key_Down = 0x01,
		Key_Up = 0x02,
		Key_Press = 0x03,
		Key_Long_Press = 0x04,
	} tEvent;
} key_t;

void EventProcessEntry(void *param);

#ifdef __cplusplus
}
#endif

#endif /* __EVENT_MANAGEMENT_H */