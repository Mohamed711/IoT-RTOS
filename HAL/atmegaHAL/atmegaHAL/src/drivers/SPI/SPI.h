/*
 * SPI.h
 *
 * Created: 2/11/2016 12:47:30 AM
 *  Author: ZIKO
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "avr/interrupt.h"
#include "../DIO/DIO.h"
#include "SPI_Config.h"
#include "SPI_Lcfg.h"
#include "HAL_SPI_AVR.h"

void spiInit(uint32_t u32MaxFreq, uint8_t u8Mode, uint8_t u8DataOrder);
void SPIInterruptInit();
void spiMasterTransmit(uint8_t data);	//for both with and without interrupt
//void SPI_SlaveTransmit(uint8_t data);	//with interrupt
uint8_t SPI_SlaveReceive();			//without interrupt
uint8_t spiTranceiver(uint8_t data);		//for Master and Slave with and without interrupt
extern volatile uint8_t SPI_DATA ;
#endif /* SPI_H_ */