/*
 * BTN.c
 *
 * Created: 04/09/2015 10:48:21 ص
 *  Author: hossam
 */ 
#include "DIO.h"
#include "RTOS_Headers.h"
#include "BTN.h"

#define MEELY 0x00
#define MORE 0x01
#define STATE_MACHINE_TYPE MEELY

#define STAT_OPEN 0x00
#define STAT_CLOSED 0x01
#define STAT_RisingEdge 0x02
#define STAT_FallingEdge 0x03 // this is extra state to handle when you get you hands off the button (for more stability).
static uint8_t BtnState; // this is uint8_t so it holds the state of max 4 buttons (2bits for each) you can use u16 and u32 for more buttons
static uint8_t getIndex(uint8_t mask) // it takes the mask of the button and return its index
{
	uint8_t index=0;
	uint8_t temp=mask;
	while(temp !=0x01)
	{
		temp=temp>>1;
		index++;
	}
	return index;
}	
void BTN_Init(uint8_t portname,uint8_t btnMask) // it takes the port name and the button mask
{
uint8_t i=getIndex(btnMask);
DIO_InitPortDirection(portname,0x00,btnMask);
BtnState &=~(0x3<<(i*2)); // clearing the button 2 bits
BtnState |=(STAT_OPEN<<(i*2)); // writing on the button 2 bits only
}

uint8_t BTN_Read(uint8_t portname,uint8_t btnMask)
{
	uint8_t PinVal;
	uint8_t BtnVal;
uint8_t i=getIndex(btnMask);
	PinVal = DIO_ReadPort(portname,btnMask);
	switch((BtnState>>i*2)&0x03) //shifting the button 2 bits to be the least 2 bits so that we can compare with our states
	{
		case STAT_OPEN:
		{
			
			if(PinVal==0)
			{
				BtnState &=~(0x3<<(i*2));
					BtnState |=(STAT_OPEN<<(i*2));
			}
		
			else
			{
				BtnState &=~(0x3<<(i*2));
				BtnState |=(STAT_RisingEdge<<(i*2));
			}
			
			BtnVal=BTN_INACTIVE;	
		}
		break;
		case STAT_CLOSED:
		{
			if(PinVal==0)
			{
				BtnState &=~(0x3<<(i*2));
				BtnState |=(STAT_FallingEdge<<(i*2));
			}
			
			else
			{
				BtnState &=~(0x3<<(i*2));
				BtnState |=(STAT_CLOSED<<(i*2));
			}
		
			BtnVal=BTN_INACTIVE;
		}
		break;
		case STAT_RisingEdge:
		{
			
			if(PinVal==0)
			{
				BtnState &=~(0x3<<(i*2));
				BtnState |=(STAT_OPEN<<(i*2));
			}
			
			else
			{
				BtnState &=~(0x3<<(i*2));
					BtnState |=(STAT_CLOSED<<(i*2));
			}
		
			BtnVal=BTN_ACTIVE;
		}
		break;
		case STAT_FallingEdge:
		{
			
			if(PinVal==0)
			{
				BtnState &=~(0x3<<(i*2));
				BtnState |=(STAT_OPEN<<(i*2));
			}				
				
			else
			{
				BtnState &=~(0x3<<(i*2));
				BtnState |=(STAT_CLOSED<<(i*2));
			}
			
			BtnVal=BTN_INACTIVE;
		}
		break;
		
	}
	return BtnVal;
}