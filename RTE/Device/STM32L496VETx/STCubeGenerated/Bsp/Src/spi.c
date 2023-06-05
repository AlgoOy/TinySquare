#include "../Inc/spi.h"
#include "stm32l4xx.h"

SPI_HandleTypeDef SPI3_Handler;

void SPI_Init(void) {
    SPI3_Handler.Instance = SPI3;
    SPI3_Handler.Init.Mode = SPI_MODE_MASTER;
    SPI3_Handler.Init.Direction = SPI_DIRECTION_2LINES;
    SPI3_Handler.Init.DataSize = SPI_DATASIZE_8BIT;
    SPI3_Handler.Init.CLKPolarity = SPI_POLARITY_HIGH;
    SPI3_Handler.Init.CLKPhase = SPI_PHASE_2EDGE;
    SPI3_Handler.Init.NSS = SPI_NSS_SOFT;
    SPI3_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    SPI3_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;
    SPI3_Handler.Init.TIMode = SPI_TIMODE_DISABLE;
    SPI3_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    SPI3_Handler.Init.CRCPolynomial = 7;

    HAL_SPI_Init(&SPI3_Handler);
    __HAL_SPI_ENABLE(&SPI3_Handler);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI3_CLK_ENABLE();

    //PB3|5
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_5;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;
    GPIO_Initure.Pull=GPIO_PULLUP;
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;        
    GPIO_Initure.Alternate=GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

uint8_t SPI3_ReadWriteByte(uint8_t TxData) {
    uint8_t Rxdata;
    HAL_SPI_TransmitReceive(&SPI3_Handler,&TxData,&Rxdata,1,1000);
    return Rxdata;
}

uint8_t SPI3_WriteByte(uint8_t *TxData,uint16_t size) {
    return HAL_SPI_Transmit(&SPI3_Handler,TxData,size,1000);
}