#ifndef __KEY_H
#define __KEY_H

#include "stm32l4xx.h"

#define KEY0_GPIO_PORT          GPIOD
#define KEY0_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()
#define KEY0_GPIO_PIN           GPIO_PIN_10
#define KEY0_EXIT_IRQ           EXTI15_10_IRQn
#define KEY0_IRQHandler         EXTI15_10_IRQHandler

#define KEY1_GPIO_PORT          GPIOD
#define KEY1_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()
#define KEY1_GPIO_PIN           GPIO_PIN_9
#define KEY1_EXIT_IRQ           EXTI9_5_IRQn
#define KEY1_IRQHandler         EXTI9_5_IRQHandler

#define KEY2_GPIO_PORT          GPIOD
#define KEY2_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()
#define KEY2_GPIO_PIN           GPIO_PIN_8
#define KEY2_EXIT_IRQ           EXTI9_5_IRQn
#define KEY2_IRQHandler         EXTI9_5_IRQHandler

#define KEY3_GPIO_PORT          GPIOC
#define KEY3_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
#define KEY3_GPIO_PIN           GPIO_PIN_13
#define KEY3_EXIT_IRQ           EXTI15_10_IRQn
#define KEY3_IRQHandler         EXTI15_10_IRQHandler

typedef enum {
	no_key_press = 0x00,
	key_0 = 0x01,
	key_1 = 0x02,
	key_2 = 0x03,
	key_3 = 0x04,
}Key_State;

void Key_Init(void);

#endif