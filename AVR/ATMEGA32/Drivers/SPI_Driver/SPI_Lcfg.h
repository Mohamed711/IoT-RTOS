
#ifndef SPI_LCFG_H_
#define SPI_LCFG_H_

#include "SPI_Config.h"


#define F_CPU 8000000UL

typedef struct
{
	uint32_t u32TempFreq;
	uint8_t u8RegVal;
}CLK_Rate;

typedef struct
{
	uint32_t u32MaxFreq;
	uint8_t u8Mode;
	uint8_t u8DataOrder;
	//uint8_t u8Master_OR_SLAVE;
	//uint8_t ENABLE_INTERRUPT_OR_NOT;
}SPI_ConfigType;

extern const SPI_ConfigType SPI_InitConfig;
extern const CLK_Rate clk[PRESCALAR_NUM];



#endif /* SPI_LCFG_H_ */