/*
 * contextSwitch.c
 *
 * Created: 7/3/2016 8:26:00 AM
 *  Author: fady
 */ 
#include "Process.h"
#include "queue.h"
#include "contextSwitch.h"
#include "../RTOS.h"
volatile uint16_t tempAddress;
volatile uint16_t savedAddress;
extern struct procent proctab[NPROC];		  /* table of processes */
void Scheduler_contextSwitch()
{
		#ifdef AVR
		
		SaveMainStakpointer();
		savedAddress=(TempPointer_H<<8)|(TempPointer_L);
		
		tempAddress=proctab[0].Regstkptr;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		SetMainStakpointer();
		
		saveContext();
		proctab[0].Regstkptr=(TempPointer_H<<8)|(TempPointer_L);
		
		tempAddress=proctab[currpid].Regstkptr;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		SetMainStakpointer();
		
		restoreContext();
		proctab[currpid].Regstkptr=(TempPointer_H<<8)|(TempPointer_L);
		tempAddress=proctab[currpid].prstkptr;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		SetMainStakpointer();
		
		tempAddress=proctab[currpid].returnValue;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		jumptoPC();
		
		
		
		tempAddress=proctab[0].Regstkptr;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		SetMainStakpointer();
		
		restoreContext();
		proctab[0].Regstkptr=(TempPointer_H<<8)|(TempPointer_L);
		TempPointer_L=savedAddress;
		TempPointer_H=savedAddress>>8;
		SetMainStakpointer();
		
		#endif
	
}