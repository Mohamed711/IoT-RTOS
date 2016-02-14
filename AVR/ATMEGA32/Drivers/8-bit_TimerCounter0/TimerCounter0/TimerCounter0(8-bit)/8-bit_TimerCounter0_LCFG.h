/*
 * _8_bit_TimerCounter0_LCFG.h
 *
 * Created: 1/31/2016 4:31:21 PM
 *  Author: Dell Ultrabook
 */ 
#ifndef TIMERCOUNTER0_LCFG_H_
#define TIMERCOUNTER0_LCFG_H_

#include "StdTypes.h"
#include "8-bit_TimerCounter0_CFG.h"

typedef struct  
{
	float u32TempFreq;
	u8 u8RegVal;
}CLK_RATE;

extern const CLK_RATE clk [PRESCALAR_NUM];

typedef struct
{
	u8 MODE_NORMAL_CTC ;
}TimerMODE;

extern const TimerMODE MODE; 

#endif /* TIMERCOUNTER0_LCFG_H_ */