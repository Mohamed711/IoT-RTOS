

#ifndef HAL_SPI_AVR_H_
#define HAL_SPI_AVR_H_

#include "DIO.h"
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
}SPI_INITTypeDef;

typedef struct{
	uint8_t Txdata;
	uint8_t Rxdata;	
	}SPI_HandleTypeDef;
	
typedef struct
{
	uint32_t u32TempFreq;
	uint8_t u8RegVal;
}CLK_Rate;

void HAL_SPI_Init(SPI_INITTypeDef * spi);
void HAL_SPI_InterruptInit();
void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA);
uint8_t HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA);


extern const CLK_Rate clk[PRESCALAR_NUM];
#endif /* HAL_SPI_AVR_H_ */