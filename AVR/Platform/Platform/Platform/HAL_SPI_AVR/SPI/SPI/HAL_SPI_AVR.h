/*
 * HAL_SPI_AVR.h
 *
 * Created: 2/20/2016 4:04:21 PM
 *  Author: ZIKO
 */ 


#ifndef HAL_SPI_AVR_H_
#define HAL_SPI_AVR_H_

#include "GPIO.h"
#include "StdTypes.h"
#include "SPI_Config.h"
#include "SPI.h"

typedef struct {
	//u8 SPIData;
	u32 u32MaxFreq;
	u8 u8Mode;
	u8 u8DataOrder;
}SPI_INITTypeDef;

typedef struct{
	u8 Txdata;
	u8 Rxdata;	
	}SPI_HandleTypeDef;
	
typedef struct
{
	u32 u32TempFreq;
	u8 u8RegVal;
}CLK_Rate;

void HAL_SPI_Init(SPI_INITTypeDef * spi);
void HAL_SPI_InterruptInit();
void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA);
//void HAL_SPI_SlaveTransmit(SPI_INITTypeDef * spi);
u8 HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA);
//u8 HAL_SPI_Tranceiver(SPI_INITTypeDef * spi);



extern const CLK_Rate clk[PRESCALAR_NUM];
#endif /* HAL_SPI_AVR_H_ */