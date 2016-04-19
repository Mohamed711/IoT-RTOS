#include "GPIO.h"

#include <avr/io.h>

#define WRITE_REG(Reg,Value,Mask) Reg&=~(Mask); Reg|=(Value & Mask)
#define READ_REG(Reg,Mask) Reg & Mask

void GPIO_InitPortDirection(u8 PortName,u8 PortDirection,u8 PortMask)
{
	switch(PortName)
	{
		case PA:
		{
			WRITE_REG(DDRA,PortDirection,PortMask);
		}
		break;
		case PB:
		{
			WRITE_REG(DDRB,PortDirection,PortMask);
		}
		break;
		case PC:
		{
			WRITE_REG(DDRC,PortDirection,PortMask);
		}
		break;
		case PD:
		{
			WRITE_REG(DDRD,PortDirection,PortMask);
		}
		break;
	}	
}
void GPIO_WritePort(u8 PortName,u8 PortData,u8 PortMask)
{
	switch(PortName)
	{
		case PA:
		{
			WRITE_REG(PORTA,PortData,PortMask);
		}
		break;
		case PB:
		{
			WRITE_REG(PORTB,PortData,PortMask);
		}
		break;
		case PC:
		{
			WRITE_REG(PORTC,PortData,PortMask);
		}
		break;
		case PD:
		{
			WRITE_REG(PORTD,PortData,PortMask);
		}
		break;
	}	
}
u8 GPIO_ReadPort(u8 PortName,u8 PortMask)
{
	u8 Data = 0;
	switch(PortName)
	{
		case PA:
		{
			Data = READ_REG(PINA,PortMask);
		}
		break;
		case PB:
		{
			Data = READ_REG(PINB,PortMask);
		}
		break;
		case PC:
		{
			Data = READ_REG(PINC,PortMask);
		}
		break;
		case PD:
		{
			Data = READ_REG(PIND,PortMask);
		}
		break;
		
	}
	return Data;
	
}