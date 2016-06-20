

#ifndef HAL_SPI_AVR_H_
#define HAL_SPI_AVR_H_

#include "../DIO/DIO.h"
#include <stdint.h>
#include <stdbool.h>
#include "SPI_Config.h"
#include "SPI.h"


#ifndef F_CPU
#define F_CPU 8000000ul
#endif

typedef struct {
	uint32_t u32MaxFreq;
	uint8_t u8Mode;
	uint8_t u8DataOrder;
}SPI_InitTypeDef;

typedef struct{
	uint8_t Txdata;
	uint8_t Rxdata;	
	}SPI_HandleTypeDef;

void HAL_SPI_Init(SPI_InitTypeDef * spi);
void HAL_SPI_InterruptInit();
void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA);
uint8_t HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA);

#endif /* HAL_SPI_AVR_H_ */