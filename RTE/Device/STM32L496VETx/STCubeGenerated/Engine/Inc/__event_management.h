#ifndef ____EVENT_MANAGEMENT_H
#define ____EVENT_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtthread.h"
#include "event_management.h"

#define MAX_QUEUE_SIZE 64

typedef struct eventQueue_t {
	rt_uint8_t front, rear, size;
	key_t *events;
} eventQueue_t;

#ifdef __cplusplus
}
#endif

#endif /* ____EVENT_MANAGEMENT_H */