#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

#define PA 0x00
#define PB 0x01
#define PC 0x02
#define PD 0x03

void DIO_InitPortDirection(uint8_t PortName,uint8_t PortDirection,uint8_t PortMask);
void DIO_WritePort(uint8_t PortName,uint8_t PortData,uint8_t PortMask);
uint8_t DIO_ReadPort(uint8_t PortName,uint8_t PortMask);



#endif /* DIO_H_ */