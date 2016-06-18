
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "avr/interrupt.h"
#include "GPIO.h"

void spiInit(void);
void spiMasterTransmit(uint8_t data);
void spiSlaveTransmit(uint8_t data);
uint8_t spiSlaveReceive();
uint8_t spiTranceiver(uint8_t data);		
extern volatile uint8_t SPI_DATA ;
#endif /* SPI_H_ */