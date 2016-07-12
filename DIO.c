/*
 * DIO.c
 *
 * Created: 24/08/2015 12:51:22 ص
 *  Author: hossam
 */ 
#include "DIO.h"
// write a macro to write a register with a certain value on specific bits locations
#define WRITE_REG(Reg,Value,Mask) Reg&=~(Mask); Reg|=(Value & Mask)
//read a maco to read specific bits from a register
#define READ_REG(Reg,Mask) Reg & Mask

void DIO_InitPortDirection(uint8_t PortName,uint8_t PortDirection,uint8_t PortMask)
{
	//check the required port, specified bits and direction on the Data Direction Register
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

void DIO_WritePort(uint8_t PortName,uint8_t PortData,uint8_t PortMask)
{
	//check the required port, specified bits and value on the Port Data Register
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
uint8_t DIO_ReadPort(uint8_t PortName,uint8_t PortMAsk)
{
	//check the required port, specified bits and value from the Port input Register
	uint8_t Data;
	switch(PortName)
	{
		case PA:
		{
			Data = READ_REG(PINA,PortMAsk);
		}
		break;
		case PB:
		{
			Data = READ_REG(PINB,PortMAsk);
		}
		break;
		case PC:
		{
			Data = READ_REG(PINC,PortMAsk);
		}
		break;
		case PD:
		{
			Data = READ_REG(PIND,PortMAsk);
		}
		break;
		
	}
	return Data;
	
}