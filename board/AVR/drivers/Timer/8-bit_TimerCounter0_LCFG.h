/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *****************************************************************************/
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