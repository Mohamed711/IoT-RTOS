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

#ifndef STRUCTURE_PARAMS_H_
#define STRUCTURE_PARAMS_H_


#define _GET_NTH_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) \
  SET_ARGUMENT ## N ## _(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)
#define COUNT_VARARGS(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)


#define SET_ARGUMENT0_(...)		
#define SET_ARGUMENT1_(X,...)		__TEMP_VAR__.X;
#define SET_ARGUMENT2_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT1_(__VA_ARGS__)  
#define SET_ARGUMENT3_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT2_(__VA_ARGS__)  
#define SET_ARGUMENT4_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT3_(__VA_ARGS__)  
#define SET_ARGUMENT5_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT4_(__VA_ARGS__)  
#define SET_ARGUMENT6_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT5_(__VA_ARGS__)  
#define SET_ARGUMENT7_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT6_(__VA_ARGS__)  
#define SET_ARGUMENT8_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT7_(__VA_ARGS__)  
#define SET_ARGUMENT9_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT8_(__VA_ARGS__)  
#define SET_ARGUMENT10_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT9_(__VA_ARGS__)  
#define SET_ARGUMENT11_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT10_(__VA_ARGS__)  
#define SET_ARGUMENT12_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT11_(__VA_ARGS__)  
#define SET_ARGUMENT13_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT12_(__VA_ARGS__)  
#define SET_ARGUMENT14_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT13_(__VA_ARGS__)  
#define SET_ARGUMENT15_(X,...) 		__TEMP_VAR__.X; SET_ARGUMENT14_(__VA_ARGS__)  

#endif /* STRUCTURE_PARAMS_H_ */
