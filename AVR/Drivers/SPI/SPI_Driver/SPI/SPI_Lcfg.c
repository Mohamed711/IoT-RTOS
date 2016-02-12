
#include "SPI_Lcfg.h"

const SPI_ConfigType SPI_InitConfig = 
{
	75000000UL,
	u8MODE_1,
	u8DOR_MSB,
	SPI_MASTER_EN,
	SPI_INT_EN
};


const CLK_Rate clk[7] =
{
	{F_CPU/2,4},
	{F_CPU/4,0},
	{F_CPU/8,5},
	{F_CPU/16,1},
	{F_CPU/32,6},
	{F_CPU/64,2},
	{F_CPU/128,3}
};