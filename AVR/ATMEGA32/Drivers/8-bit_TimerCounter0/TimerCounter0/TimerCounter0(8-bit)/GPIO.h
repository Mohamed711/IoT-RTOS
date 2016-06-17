#ifndef GPIO_H_
#define GPIO_H_

#include "StdTypes.h"

#define PA 0x00
#define PB 0x01
#define PC 0x02
#define PD 0x03

void GPIO_InitPortDirection(u8 PortName,u8 PortDirection,u8 PortMask);
void GPIO_WritePort(u8 PortName,u8 PortData,u8 PortMask);
u8 GPIO_ReadPort(u8 PortName,u8 PortMask);



#endif /* GPIO_H_ */