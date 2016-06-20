#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdbool.h>
 
#define PA 0x00
#define PB 0x01
#define PC 0x02
#define PD 0x03

void GPIO_InitPortDirection(uint8_t PortName,uint8_t PortDirection,uint8_t PortMask);
void GPIO_WritePort(uint8_t PortName,uint8_t PortData,uint8_t PortMask);
uint8_t GPIO_ReadPort(uint8_t PortName,uint8_t PortMask);


#endif /* GPIO_H_ */