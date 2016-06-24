

#ifndef INIT_H_
#define INIT_H_

#include <stdint.h>
#include <stdbool.h>

extern void initialize(uint32_t ui32Base);
void uartSend(uint32_t ui32Base, unsigned char ucData);
int32_t uartReceive(uint32_t ui32Base);

#endif /* INIT_H_ */
