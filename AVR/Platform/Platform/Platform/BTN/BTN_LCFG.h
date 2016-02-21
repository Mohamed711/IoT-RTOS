/*
 * BTN_lcfg.h
 *
 * Created: 10/10/2015 4:24:55 PM
 *  Author: mido4
 */ 


#ifndef BTN_LCFG_H_
#define BTN_LCFG_H_

#include <stdint.h>
#include "BTN_Cfg.h"

typedef struct
{
	uint8_t BtnPort;
	uint8_t BtnMask;
}BTN_ConfigType;
	
extern BTN_ConfigType BTN_ConfigData[BTN_MAX_NUM];



#endif /* BTN_LCFG_H_ */