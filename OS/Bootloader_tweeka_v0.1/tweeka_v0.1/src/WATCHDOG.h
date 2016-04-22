/*
 * WATCHDOG.H
 *
 * Created: 2/2/2016 5:26:12 PM
 *  Author: Karen-pc
 */ 
#ifndef WATCHDOG_H_
#define WATCHDOG_H_
#include "StdTypes.h"
#include "WATCHDOG_CFG.h"

void WDT_Enable(u8 Timeout);
void WDT_Disable();

#endif 