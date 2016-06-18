
#include "SPI.h"
volatile uint8_t SPI_DATA;

void main()
{
	spi_Init();
	GPIO_InitPortDirection(PA,0xFF,0xFF);/*show data on PORTA*/
	
	while(1)
	{
		
		//1 whitout interrupt in both
		GPIO_WritePort(PA,spiTranceiver(7),0xFF);
		GPIO_WritePort(PA,spiTranceiver(16),0xFF);
		//////////////////////////////////////////////////////////////
		
		//2 whitout interrupt in both
//		spiMasterTransmit(7);
//		spiMasterTransmit(16);
		
		
		//3 With Interrupt enbaled for Slave only
//		spiMasterTransmit(7);
//		spiMasterTransmit(16);
		
		//4 Interrupt enabled for Master ONLY
//		GPIO_WritePort(PA,SPI_DATA,0xFF);

	}
}