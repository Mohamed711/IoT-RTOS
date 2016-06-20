
#ifndef TIMERCOUNTER0_LCFG_H_
#define TIMERCOUNTER0_LCFG_H_

#include <stdint.h>
#include <stdbool.h>
#include "8-bit_TimerCounter0_CFG.h"

typedef struct
{
	uint32_t TempFreq;
	uint8_t  RegVal;
}CLK_RATE1ms;

extern const CLK_RATE1ms clk1ms [PRESCALAR_NUM];


typedef struct
{
	uint8_t MODE_NORMAL_CTC ;
}TimerMODE;

extern const TimerMODE MODE; 



#endif /* TIMERCOUNTER0_LCFG_H_ */