

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

SPI_InitTypeDef *spiy;
SPI_HandleTypeDef *spiz;

#define spimasterinit(x) spiy = x; spiInitMaster(spiy->u32MaxFreq, spiy->u8Mode, spiy->u8DataOrder)
#define spislaveinit(x) spiy = x; spiInitMaster(spiy->u32MaxFreq, spiy->u8Mode, spiy->u8DataOrder)
#define spiinterruptenable()  SPIInterruptInit()
#define spimastertransmit(x) spiz = x; spiMasterTransmit(spiz->Txdata)
#define spireceive(x) spiTranceiver(spiz->Txdata); spiz=x;

void HAL_SPI_InterruptInit();
void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA);
uint8_t HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA);

#endif /* HAL_SPI_AVR_H_ */