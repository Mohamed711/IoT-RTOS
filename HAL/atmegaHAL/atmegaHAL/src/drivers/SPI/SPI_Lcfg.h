
#ifndef SPI_LCFG_H_
#define SPI_LCFG_H_

#include "SPI_Config.h"


#define F_CPU 8000000UL

typedef struct
{
	uint32_t u32TempFreq;
	uint8_t u8RegVal;
}SPI_CLK_Rate;

extern const SPI_CLK_Rate spi_clk[PRESCALAR_NUM];



#endif /* SPI_LCFG_H_ */