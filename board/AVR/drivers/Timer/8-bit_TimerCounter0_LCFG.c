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
#include "8-bit_TimerCounter0_LCFG.h"
#define F_CPU 8000000UL
const CLK_RATE1ms clk1ms [5] =
{
{(F_CPU)*0.001,1}, /*F_CPU , Value of CS00-CS01-CS02*/
{(F_CPU/8)*0.001,2},
{(F_CPU/64)*0.001,3},
{(F_CPU/256)*0.001,4},
{(F_CPU/1024)*0.001,5},
};


const TimerMODE MODE = 
{
	u8_MODE_CTC,
};