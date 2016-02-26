/*
 * BTN.c
 *
 * Created: 10/9/2015 7:46:51 PM
 *  Author: mido4
 */ 

#include "BTN.h"
#include "BTN_lcfg.h"
#include "../DIO/DIO.h"

#define STATE_OPEN 0x00
#define STATE_CLOSED 0x01

static uint8_t BTN_PrevState[BTN_MAX_NUM];

void BTN_Init(void)
{
	uint8_t LoopIndex;
	uint8_t BtnMask;
	uint8_t BtnPort;
	
	for(LoopIndex = 0; LoopIndex <BTN_MAX_NUM; LoopIndex++)
	{
		BtnMask = BTN_ConfigData[LoopIndex].BtnMask;
		BtnPort = BTN_ConfigData[LoopIndex].BtnPort;
		DIO_InitPortDirection(BtnPort,0,BtnMask);
		BTN_PrevState[LoopIndex] = STATE_OPEN;
	}
}


uint8_t Btn_Read(uint8_t BtnId)
{
	uint8_t PrevState;
	uint8_t BtnPort;
	uint8_t BtnMask;
	uint8_t PinData;
	uint8_t RetVal;
	
	PrevState = BTN_PrevState[BtnId];
	BtnPort = BTN_ConfigData[BtnId].BtnPort;
	BtnMask = BTN_ConfigData[BtnId].BtnMask;
	PinData = DIO_ReadPort(BtnPort,BtnMask);
		if(PrevState == STATE_OPEN)
		{
			if(PinData == 0x00)
			{
				PrevState = STATE_OPEN;
				BTN_PrevState[BtnId] = PrevState;
				RetVal = BTN_INACTIVE;
			}
			else
			{
				PrevState = STATE_CLOSED;
				BTN_PrevState[BtnId] = PrevState;
				RetVal = BTN_ACTIVE;
			}
		}
		else
		{
			if(PinData == 0x00)
			{
				PrevState = STATE_OPEN;
				BTN_PrevState[BtnId] = PrevState;
				RetVal = BTN_INACTIVE;
			}
			else
			{
				PrevState = STATE_CLOSED;
				BTN_PrevState[BtnId] = PrevState;
				RetVal = BTN_INACTIVE;
			}			
		}
return RetVal;
}	
