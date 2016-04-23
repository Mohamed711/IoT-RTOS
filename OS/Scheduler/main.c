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

int main(void)
{
	readylist= newqueue();
	suspendedlist=newqueue();
	//insert(processCreate(fady,200,4,"f"),readylist,4);
	//insert(processCreate(fady2,200,2,"f2"),readylist,2);
	//insert(processCreate(fady2,200,3,"f3"),readylist,3);
	//insert(processCreate(fady2,200,5,"f4"),readylist,5);
	processSetReady(processCreate(fady,200,2,"f"));
	processSetReady(processCreate(fady2,200,4,"f2"));
	processSetReady(processCreate(fady2,200,3,"f3"));
	processSetReady(processCreate(fady2,200,5,"f4"));
	processSuspendAll();
	processResumeAll();
	
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
	processResume(2);
	
}	
void fady2(void)
{
	DDRB=0xff;
	PORTB^=0xff;
	_delay_ms(500);
	
	processSuspend(2);
}