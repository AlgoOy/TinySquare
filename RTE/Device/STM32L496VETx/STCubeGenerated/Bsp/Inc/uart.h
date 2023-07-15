#ifndef __DEBUG_USART_CFG_H
#define __DEBUG_USART_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "__common.h"

#include "stm32l4xx_hal.h"

#define DEBUG_USART_BAUDRATE                   115200

#define DEBUG_USART                            USART1
#define DEBUG_USART_CLK_ENABLE()               __USART1_CLK_ENABLE()

#define DEBUG_USART_RX_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()
#define DEBUG_USART_RX_GPIO_PORT               GPIOA
#define DEBUG_USART_RX_PIN                     GPIO_PIN_10
#define DEBUG_USART_RX_AF                      GPIO_AF7_USART1

#define DEBUG_USART_TX_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()
#define DEBUG_USART_TX_GPIO_PORT               GPIOA
#define DEBUG_USART_TX_PIN                     GPIO_PIN_9
#define DEBUG_USART_TX_AF                      GPIO_AF7_USART1

#define DEBUG_USART_IRQn                       USART1_IRQn
#define DEBUG_USART_IRQHandler                 USART1_IRQHandler

#define PreemptPriority                        3
#define SubPriority                            0

#define DEBUG_USART_FORCE_RESET()              __USART1_FORCE_RESET()
#define DEBUG_USART_RELEASE_RESET()            __USART1_RELEASE_RESET()

#define DEBUG_USART_CLK_DISABLE()              __USART1_CLK_DISABLE()

#define DEBUG_USART_RX_GPIO_CLK_DISABLE()      __GPIOA_CLK_DISABLE()
#define DEBUG_USART_TX_GPIO_CLK_DISABLE()      __GPIOA_CLK_DISABLE()

UART_HandleTypeDef *GET_DEBUG_USART_HANDLE(void);

PeripheralCfgStatus DEBUG_USART_CONFIG_INIT(void);
PeripheralCfgStatus DEBUG_USART_CONFIG_DEINIT(void);
void UART_Print(const char* buf);

#ifdef __cplusplus
}
#endif

#endif //__DEBUG_USART_CFG_H