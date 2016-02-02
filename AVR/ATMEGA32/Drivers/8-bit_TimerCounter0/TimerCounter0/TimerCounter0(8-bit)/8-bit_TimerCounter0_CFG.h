/*
 * _8_bit_TimerCounter0_CFG.h
 *
 * Created: 1/31/2016 4:31:35 PM
 *  Author: Dell Ultrabook
 */ 


#ifndef TIMERCOUNTER0_CFG_H_
#define TIMERCOUNTER0_CFG_H_

//select prescaler value
// CS02-CS01-CS00 >  000=> Timer/counter stopped	001=>clkI/O
//					 010=> (clkI/O)/8				011=> (clkI/O)/64
//					 100=> (clkI/O)/256				101=> (clkI/O)/1024
#define CS02_VALUE 0
#define CS01_VALUE 1
#define CS00_VALUE 0

//select MODE
// WGM01-WGM00 >   00=> Normal		01=> PWM, Phase correct
//				   10=> CTC			11=> Fast PWM
#define WGM01_VALUE 1
#define WGM00_VALUE 0

#define COM01_VALUE 0
#define COM00_VALUE 0 

#endif /* TIMERCOUNTER0_CFG_H_ */