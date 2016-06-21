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
#ifndef STD_H_
#define STD_H_
#include <stdint.h>
#include <stdbool.h>

typedef int32_t pid32;
typedef uint16_t pri16;
typedef uint32_t sid32;
typedef uint32_t umsg32;
typedef bool bool8;
typedef	uint32_t intmask;

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef uint16_t qid16;


typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef bool sysCall;

#define OK 1
#define SYSERR -1
#define TIMEOUT 0

#endif

