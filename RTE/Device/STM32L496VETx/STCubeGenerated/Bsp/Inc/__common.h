/**
 * Created by AlgoOy on 5/26/2023.
 */

#ifndef ____COMMON_H
#define ____COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#define PERIPHERAL_INITIALIZED     1
#define PERIPHERAL_DEINITIALIZED   0

typedef enum {
  PERIPHERAL_CFG_OK = 0x00,
  PERIPHERAL_CFG_ERROR = 0x01,
  PERIPHERAL_CFG_NOT_INITIALIZED = 0x02,
  PERIPHERAL_CFG_ALREADY_INITIALIZED = 0x03,
  PERIPHERAL_CFG_NOT_IMPLEMENTED = 0x04,
} PeripheralCfgStatus;

#ifdef __cplusplus
}
#endif

#endif /* __PERIPHERAL_COMMON_H */