/*
 * LED.c
 *
 * Created: 10/16/2015 7:51:51 AM
 *  Author: mido4
 */ 
#include "LED.h"
#include "../DIO/DIO.h"
#include "LED_Cfg.h"
#include "LED_Lcfg.h"

void LED_Init()
{
	uint8_t LoopIndex;
	for (LoopIndex = 0 ; LoopIndex < LED_MAX_NUM ; LoopIndex++)
	{
		DIO_InitPortDirection(LED_ConfigData[LoopIndex].LedPort,0xFF,LED_ConfigData[LoopIndex].LedMask);
	}
}

void LED_Switch_On(uint8_t LedID)
{
	uint8_t LedVal;
	#if ACTIVE_LOW
		LedVal = 0x00;
	#else
		LedVal = 0xFF;
	#endif	
	
	DIO_WritePort(LED_ConfigData[LedID].LedPort,LedVal,LED_ConfigData[LedID].LedMask);
}

void LED_Switch_Off(uint8_t LedID)
{
	uint8_t LedVal;
	#if ACTIVE_LOW
		LedVal = 0xFF;
	#else
		LedVal = 0x00;
	#endif
	
	DIO_WritePort(LED_ConfigData[LedID].LedPort,LedVal,LED_ConfigData[LedID].LedMask);
}

uint8_t LED_State(uint8_t LedID)
{
	uint8_t LedState;
	uint8_t RetVal;
	LedState = DIO_ReadPort(LED_ConfigData[LedID].LedPort,LED_ConfigData[LedID].LedMask);
	
	#if ACTIVE_LOW
		if ( (LedState & LED_ConfigData[LedID].LedMask) == 0x00)
			RetVal = LED_ON;
		else 
			RetVal = LED_OFF;
	#else
		if ((LedState & LED_ConfigData[LedID].LedMask) != 0x00)
			RetVal = LED_ON;
		else
			RetVal = LED_OFF;
	#endif
	
	return RetVal;
}

