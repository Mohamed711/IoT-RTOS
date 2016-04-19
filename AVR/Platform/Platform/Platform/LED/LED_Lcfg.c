/*
 * LED_Lcfg.c
 *
 * Created: 10/16/2015 7:52:57 AM
 *  Author: mido4
 */ 
#include "LED_Lcfg.h"
#include "../DIO/DIO.h"

LED_ConfigType LED_ConfigData[LED_MAX_NUM] = 
{
	{
		PD,
		0x20
	},
	{
		PD,
		0x40
	},
	{
		PD,
		0x80
	}
	
};