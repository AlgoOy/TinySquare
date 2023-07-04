#ifndef __RTOS_SUPPORT_H
#define __RTOS_SUPPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
	RTOS_Support_OK = 0x00,
	RTOS_Support_Err = 0x01,
} RTOSSupportStatus;

RTOSSupportStatus rtos_support_init(void);
RTOSSupportStatus rtos_support_deinit(void);
RTOSSupportStatus rtos_support_ipc_create(void *ipc_handler);
RTOSSupportStatus rtos_support_ipc_acquire(void *ipc_handler);
RTOSSupportStatus rtos_support_ipc_release(void *ipc_handler);
RTOSSupportStatus rtos_support_ipc_delete(void *ipc_handler);

#ifdef __cplusplus
}
#endif

#endif /* __RTOS_SUPPORT_H */