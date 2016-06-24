#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "std.h"
#include "Process.h"
#include "Initialize.h"
#include "queue.h"
void LED4()
{
	while(1)
	{
		
		
		char c[]="P4 task";
		DDRD = 0xFF;
		PORTD ^= 0xFF;
		_delay_ms(1000);

	}
	

}

void LED1()
{
	pid32 pidLED4= processCreate(LED4, 100, 7, "P4");//blue
	insert(pidLED4, readylist, proctab[pidLED4].prprio);
	while(1)
	{
	char c[]="P1 task";
	DDRA = 0xFF;
	PORTA = 0xFF;
	//_delay_ms(1000);
	PORTA = 0x00;
	
//processTerminate(1);
	}	
	//processTerminate(1);

}

void LED2()
{
	while(1)
	{
	DDRB = 0xFF;
	PORTB = 0xFF;
	_delay_ms(1000);
	PORTB = 0x00;
	processTerminate(2);
	}	
	//processTerminate(2);
	
}

void LED3()
{
	while(1)
	{
		
	char c[]="P3 task";
	DDRC = 0xFF;
	PORTC = 0xFF;
	_delay_ms(1000);
	PORTC = 0x00;
processTerminate(3);
	}	
	//processTerminate(3);
	
}


volatile uint16_t *saddr;
void main(void) {

	readylist = newqueue();
	suspendedlist = newqueue();
	proctab[0].processFunction = main;
	proctab[0].prstate = PR_CURR;
	proctab[0].prprio = 0;
	strncpy(proctab[0].prname, "prnull", 7);
	proctab[0].prstklen = 100;
	proctab[0].prstkbase = pvPortMalloc(100)+proctab[0].prstklen;
	saddr=proctab[0].prstkbase;

proctab[0].prstkptr = (uint16_t *)InitialiseStack(saddr,main);
	currpid = NULLPROC;
	
	pid32 pidLED1= processCreate(LED1, 100, 1, "P1");//blue
	pid32 pidLED2= processCreate(LED2, 100, 5, "P2");	//red
	pid32 pidLED3= processCreate(LED3, 100, 2, "P3");	//purple

	insert(pidLED1, readylist, proctab[pidLED1].prprio);
	insert(pidLED2, readylist, proctab[pidLED2].prprio);
	insert(pidLED3, readylist, proctab[pidLED3].prprio);
	
		
	clkinit();
	while(1);
	//{
		////keep calling current process function.
		//void(*pf)(void);
		//pf = proctab[currpid].processFunction;
		//pf();
	//}
}