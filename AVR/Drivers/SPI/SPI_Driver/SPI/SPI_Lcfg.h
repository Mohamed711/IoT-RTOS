/*
 * SPI_Lcfg.h
 *
 * Created: 2/10/2016 4:27:35 AM
 *  Author: ZIKO
 */ 


#ifndef SPI_LCFG_H_
#define SPI_LCFG_H_

#include "StdTypes.h"
#include "SPI_Config.h"

typedef struct
{
	u32 u32TempFreq;
	u8 u8RegVal;
}CLK_Rate;

typedef struct
{
	u32 u32MaxFreq;
	u8 u8Mode;
	u8 u8DataOrder;
	u8 u8Master_OR_SLAVE;
	u8 ENABLE_INTERRUPT_OR_NOT;
}SPI_ConfigType;

extern const SPI_ConfigType SPI_InitConfig;
extern const CLK_Rate clk[PRESCALAR_NUM];



#endif /* SPI_LCFG_H_ */