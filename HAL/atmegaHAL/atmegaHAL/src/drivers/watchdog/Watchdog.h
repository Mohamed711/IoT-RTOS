/*
 * WATCHDOG.H
 *
 * Created: 2/2/2016 5:26:12 PM
 *  Author: Karen-pc
 */ 
#ifndef WATCHDOG_H_
#define WATCHDOG_H_
#include <stdint.h>
#include <stdbool.h>

void watchdogInit(void);
void watchdogEnable(uint8_t Timeout);
void watchdogReset();
void watchdogDisable();

#endif 