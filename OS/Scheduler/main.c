/*
 * main.c
 *
 * Created: 4/19/2016 1:35:07 PM
 *  Author: fady
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "headers.h"
void fady();
void fady2(void);
void fady3(void);
void fady4(void);
int main(void)
{
	readylist= newqueue();
	suspendedlist=newqueue();
	/* 
	This is test for using suspend and resume All
	P4 with prio 5 change led state on port D
	P2 with prio 4 change led state on port B
	P3 with prio 3 change led state on port C
	P1 with prio 2 change led state on port A
	each process suspend it self so that the lower priority task can get scheduled and finally
	the least priority task resume them all so the highest priority process returns to be working
	again
	*/ 
	processSetReady(processCreate(fady,200,2,"P1"));
	processSetReady(processCreate(fady2,200,4,"P2"));
	processSetReady(processCreate(fady3,200,3,"P3"));
	processSetReady(processCreate(fady4,200,5,"P4")); 
	//processSuspendAll();
	//processResumeAll();
	
    while(1)
    {
		void (*pf) (void) ; 
		reSched();
		pf = proctab[currpid].processFunction;
		pf();
        //TODO:: Please write your application code 
    }
}
void fady(void)
{
	DDRA=0xff;
	PORTA^=0xff;
	_delay_ms(1000);
	processResumeAll();
}	
void fady2(void)
{
	DDRB=0xff;
	PORTB^=0xff;
	_delay_ms(500);
	
	processSuspend(2);
}
void fady3(void)
{
	DDRC=0xff;
	PORTC^=0xff;
	_delay_ms(500);
	
	processSuspend(3);
}
void fady4(void)
{
	DDRD=0xff;
	PORTD^=0xff;
	_delay_ms(500);
	
	processSuspend(4);
}