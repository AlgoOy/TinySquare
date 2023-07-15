#include "uart.h"

static uint8_t DEBUG_USART_STATE = PERIPHERAL_DEINITIALIZED;

static UART_HandleTypeDef UartHandle = {0};


#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)

PUTCHAR_PROTOTYPE {
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

GETCHAR_PROTOTYPE {
  int ch;
  while (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) == RESET);
  if(HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF) != HAL_OK) {
    return -1;
  }
  return ch;
};



UART_HandleTypeDef *GET_DEBUG_USART_HANDLE(void) {
  return &UartHandle;
}

PeripheralCfgStatus DEBUG_USART_CONFIG_INIT(void) {
  if (DEBUG_USART_STATE == PERIPHERAL_INITIALIZED) {
    return PERIPHERAL_CFG_ALREADY_INITIALIZED;
  }

  UartHandle.Instance = DEBUG_USART;
  UartHandle.Init.BaudRate = DEBUG_USART_BAUDRATE;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  UartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;


  if (HAL_UART_Init(&UartHandle) != HAL_OK) {
    return PERIPHERAL_CFG_ERROR;
  }

  DEBUG_USART_STATE = PERIPHERAL_INITIALIZED;

  return PERIPHERAL_CFG_OK;
}

PeripheralCfgStatus DEBUG_USART_CONFIG_DEINIT(void) {
  if (DEBUG_USART_STATE == PERIPHERAL_DEINITIALIZED) {
    return PERIPHERAL_CFG_NOT_INITIALIZED;
  }

  if (HAL_UART_DeInit(&UartHandle) != HAL_OK) {
    return PERIPHERAL_CFG_ERROR;
  }

  DEBUG_USART_STATE = PERIPHERAL_DEINITIALIZED;

  return PERIPHERAL_CFG_OK;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
  GPIO_InitTypeDef GPIO_InitStruct;

  if (huart->Instance == DEBUG_USART) {
    DEBUG_USART_CLK_ENABLE();

    DEBUG_USART_RX_GPIO_CLK_ENABLE();
    DEBUG_USART_TX_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    GPIO_InitStruct.Alternate = DEBUG_USART_TX_AF;
    GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
    HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
    HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(DEBUG_USART_IRQn, PreemptPriority, SubPriority);
    HAL_NVIC_EnableIRQ(DEBUG_USART_IRQn);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
  if (huart->Instance == DEBUG_USART) {
    HAL_NVIC_DisableIRQ(DEBUG_USART_IRQn);

    DEBUG_USART_FORCE_RESET();
    DEBUG_USART_RELEASE_RESET();

    DEBUG_USART_CLK_DISABLE();

    HAL_GPIO_DeInit(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_PIN);
    HAL_GPIO_DeInit(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_PIN);

    DEBUG_USART_RX_GPIO_CLK_DISABLE();
    DEBUG_USART_TX_GPIO_CLK_DISABLE();
  }
}

void DEBUG_USART_IRQHandler(void) {

  /* interrupt handler code begin */
  HAL_UART_IRQHandler(&UartHandle);
  /* interrupt handler code end */

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

}

void UART_Print(const char* buf) {
  while('\0' != *buf) {
    HAL_UART_Transmit(&UartHandle, (uint8_t*)buf, 1, 0xFFFF);
    ++buf;
  }
}

void UART_PrintChar(int c) {
    HAL_UART_Transmit(&UartHandle, (uint8_t*)&c, 1, 0xFFFF);
}