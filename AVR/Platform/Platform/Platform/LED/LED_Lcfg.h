/*
 * LED_Lcfg.h
 *
 * Created: 10/16/2015 7:53:15 AM
 *  Author: mido4
 */ 


#ifndef LED_LCFG_H_
#define LED_LCFG_H_

#include <stdint.h>
#include "LED_Cfg.h"

typedef struct  
{
	uint8_t LedPort;
	uint8_t LedMask;
}LED_ConfigType;

extern LED_ConfigType LED_ConfigData[LED_MAX_NUM];

#endif /* LED_LCFG_H_ */