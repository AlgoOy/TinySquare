#ifndef __SPI_H
#define __SPI_H

#include "stdint.h"

void SPI_Init(void);
uint8_t SPI3_ReadWriteByte(uint8_t TxData);
uint8_t SPI3_WriteByte(uint8_t *TxData,uint16_t size);

#endif
