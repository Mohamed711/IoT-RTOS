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

#include <stdio.h>
#include "queue.c"

Queue_t createQueueStructure();

int main(void) {
	
	int y;
Queue_t testQueue;

testQueue = createQueueStructure();

	printf("%d \n",testQueue.uxItemSize);
	

	scanf("%d",&y);


	return 0;
}

Queue_t createQueueStructure()
{
	Queue_t testQueue;
	testQueue.uxLength = 5;
	testQueue.uxItemSize = 4;

}