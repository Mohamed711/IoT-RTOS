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
#define CS02_VALUE 1
#define CS01_VALUE 0
#define CS00_VALUE 1

//select MODE
// WGM01-WGM00 >   00=> Normal		01=> PWM, Phase correct
//				   10=> CTC			11=> Fast PWM
#define WGM01_VALUE 1
#define WGM00_VALUE 0

#define COM01_VALUE 0
#define COM00_VALUE 0


// interrupt macros for attaching user functions to timer interrupts
// use these with timerAttach( intNum, function )
#define TIMER0OVERFLOW_INT              0
#define TIMER1OVERFLOW_INT              1
#define TIMER1OUTCOMPAREA_INT           2
#define TIMER1OUTCOMPAREB_INT           3
#define TIMER1INPUTCAPTURE_INT          4
#define TIMER2OVERFLOW_INT              5
#define TIMER2OUTCOMPARE_INT            6
#ifdef OCR0     // for processors that support output compare on Timer0
#define TIMER0OUTCOMPARE_INT            7
#define TIMER_NUM_INTERRUPTS            8
#else
#define TIMER_NUM_INTERRUPTS            7
#endif
 

#endif /* TIMERCOUNTER0_CFG_H_ */