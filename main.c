

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "OS/Scheduler/Process.h"
#include "OS/Scheduler/queue.h"
#include "OS/Scheduler/realTimeClock.h"
#include "OS/Scheduler/Initialize.h"
#include "OS/Scheduler/nullProcess.h"


#include <avr/io.h>
#include <util/delay.h>

	extern uint32_t prcount;
	extern qid16 readylist;
	extern qid16 suspendedlist;
	extern qid16 sleepq;
	extern struct procent proctab[NPROC];	
	
	
//void set_MSP(uint32_t x)
//{
	//__set_MSP(x);
//}
//
//uint32_t getControl()
//{
	//return __get_CONTROL();
//}
//uint32_t get_MSP()
//{
	//return __get_MSP();
//}
//void set_PSP(uint32_t x)
//{
	//__set_PSP(x);
//}
	
void LED1()
{
	char c[]="P1 task";
	DDRA = 0xFF;
	while(1)
	{
		
		PORTA ^= 0xFF;
		_delay_ms(100);
	

		//	Scheduler_processTerminate(1);
	}
	//Scheduler_processTerminate(1);

}
void fady()
{
		DDRD = 0xFF;
		PORTD = 0xff;
		
		_delay_ms(200);
		PORTD = 0x00;
		uint8_t i=0;
		for(i=0;i<100;i++)
		{
			
		}
}
void LED2()
{
	
		DDRB = 0xFF;
		PORTB = 0xff;
	
	_delay_ms(200);
		PORTB = 0x00;
		
//		Scheduler_sleepms(200);
		fady();
		DDRB = 0xFF;
		PORTB = 0xff;
		
		_delay_ms(200);
		PORTB = 0x00;
	Scheduler_processTerminate(2);
}

void LED3()
{
		char c[]="P3 task";
		DDRC = 0xFF;
	
		PORTC = 0xff;
		_delay_ms(200);
		PORTC = 0x00;
	
	Scheduler_processTerminate(3);
}


int main(void) {
	

	prcount=0;
	readylist = newqueue();
	suspendedlist = newqueue();
	sleepq = newqueue();
	
	Scheduler_initializenullProcess();

	pid32 pidLED1= Scheduler_processCreate(LED1, 100, 5, "P1");//green
	pid32 pidLED2= Scheduler_processCreate(LED2, 100, 10, "P2");	//orange
	pid32 pidLED3= Scheduler_processCreate(LED3, 100, 7, "P3");	//red

	Scheduler_insertd(pidLED1, sleepq, 2000);
	Scheduler_insertd(pidLED2, sleepq, 3000);
	insert(pidLED3, readylist, proctab[pidLED3].prprio);
	insert(0, readylist, 0);
	currpid=0;
	Scheduler_nullProc();
	//Timer_New(clkhandler, 500);
	return 0;
}
