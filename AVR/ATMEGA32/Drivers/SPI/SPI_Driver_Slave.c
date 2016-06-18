#include "SPI.h"
volatile uint8_t SPI_DATA;
void main()
{
	spiInit();
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	
	while(1)
	{
		
		//1 whitout interrupt in both
		GPIO_WritePort(PA,spiTranceiver(7),0xFF);
		GPIO_WritePort(PA,spiTranceiver(8),0xFF);
		
		//2 whitout interrupt in both
//		GPIO_WritePort(PA,spiSlaveReceive(),0xFF);
		
		
		//3 With interrupt enabled for slave
//		GPIO_WritePort(PA,SPI_DATA,0xFF);
		 
		//4 Slave transmit interrupt is enabled, 
		//a warning appears but it doesn't affect result as we aren't interestetd in getting data from master in this case
		//interrupt of slave can be disabled in this case no warning are showed
//		spiSlaveTransmit(7);
//		spiSlaveTransmit(8);

	}
}