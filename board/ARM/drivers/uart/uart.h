
#ifndef UART_H_
#define UART_H_

#include <stdbool.h>
#include <stdint.h>

/*****************************************************************************
*
* If building with a C++ compiler, make all of the definitions in this header
* have a C binding.
*
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
*
* Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
* as the ui32IntFlags parameter, and returned from UARTIntStatus.
*
*****************************************************************************/
#define UART_INT_DMATX          0x20000     /* DMA TX interrupt*/
#define UART_INT_DMARX          0x10000     /* DMA RX interrupt*/
#define UART_INT_9BIT           0x1000      /* 9-bit address match interrupt*/
#define UART_INT_OE             0x400       /* Overrun Error Interrupt Mask*/
#define UART_INT_BE             0x200       /* Break Error Interrupt Mask*/
#define UART_INT_PE             0x100       /* Parity Error Interrupt Mask*/
#define UART_INT_FE             0x080       /* Framing Error Interrupt Mask*/
#define UART_INT_RT             0x040       /* Receive Timeout Interrupt Mask*/
#define UART_INT_TX             0x020       /* Transmit Interrupt Mask*/
#define UART_INT_RX             0x010       /* Receive Interrupt Mask */
#define UART_INT_DSR            0x008       /* DSR Modem Interrupt Mask*/
#define UART_INT_DCD            0x004       /* DCD Modem Interrupt Mask*/
#define UART_INT_CTS            0x002       /*CTS Modem Interrupt Mask*/
#define UART_INT_RI             0x001       /* RI Modem Interrupt Mask*/

/*****************************************************************************
*
* Values that can be passed to UARTConfigSetExpClk as the ui32Config parameter
* and returned by UARTConfigGetExpClk in the pui32Config parameter.
* Additionally, the UART_CONFIG_PAR_* subset can be passed to
* UARTParityModeSet as the ui32Parity parameter, and are returned by
* UARTParityModeGet.
*
*****************************************************************************/
#define UART_CONFIG_WLEN_MASK   0x00000060  /* Mask for extracting word length*/
#define UART_CONFIG_WLEN_8      0x00000060  /* 8 bit data*/
#define UART_CONFIG_WLEN_7      0x00000040  /* 7 bit data*/
#define UART_CONFIG_WLEN_6      0x00000020  /* 6 bit data*/
#define UART_CONFIG_WLEN_5      0x00000000  /* 5 bit data*/
#define UART_CONFIG_STOP_MASK   0x00000008  /* Mask for extracting stop bits*/
#define UART_CONFIG_STOP_ONE    0x00000000  /* One stop bit*/
#define UART_CONFIG_STOP_TWO    0x00000008  /* Two stop bits*/
#define UART_CONFIG_PAR_MASK    0x00000086  /* Mask for extracting parity*/
#define UART_CONFIG_PAR_NONE    0x00000000  /* No parity*/
#define UART_CONFIG_PAR_EVEN    0x00000006  /* Even parity*/
#define UART_CONFIG_PAR_ODD     0x00000002  /* Odd parity*/
#define UART_CONFIG_PAR_ONE     0x00000082  /* Parity bit is one*/
#define UART_CONFIG_PAR_ZERO    0x00000086  /* Parity bit is zero*/

/*****************************************************************************
*
* Values that can be passed to UARTFIFOLevelSet as the ui32TxLevel parameter
* and returned by UARTFIFOLevelGet in the pui32TxLevel.
*
*****************************************************************************/
#define UART_FIFO_TX1_8         0x00000000  /* Transmit interrupt at 1/8 Full*/
#define UART_FIFO_TX2_8         0x00000001  /* Transmit interrupt at 1/4 Full*/
#define UART_FIFO_TX4_8         0x00000002  /* Transmit interrupt at 1/2 Full*/
#define UART_FIFO_TX6_8         0x00000003  /* Transmit interrupt at 3/4 Full*/
#define UART_FIFO_TX7_8         0x00000004  /* Transmit interrupt at 7/8 Full*/

/*****************************************************************************
*
* Values that can be passed to UARTFIFOLevelSet as the ui32RxLevel parameter
* and returned by UARTFIFOLevelGet in the pui32RxLevel.
*
*****************************************************************************/
#define UART_FIFO_RX1_8         0x00000000  /* Receive interrupt at 1/8 Full*/
#define UART_FIFO_RX2_8         0x00000008  /* Receive interrupt at 1/4 Full*/
#define UART_FIFO_RX4_8         0x00000010  /* Receive interrupt at 1/2 Full*/
#define UART_FIFO_RX6_8         0x00000018  /* Receive interrupt at 3/4 Full*/
#define UART_FIFO_RX7_8         0x00000020  /* Receive interrupt at 7/8 Full*/

/*****************************************************************************
*
* Values that can be passed to UARTDMAEnable() and UARTDMADisable().
*
*****************************************************************************/
#define UART_DMA_ERR_RXSTOP     0x00000004  /* Stop DMA receive if UART error*/
#define UART_DMA_TX             0x00000002  /* Enable DMA for transmit*/
#define UART_DMA_RX             0x00000001  /* Enable DMA for receive*/

/*****************************************************************************
*
* Values returned from UARTRxErrorGet().
*
*****************************************************************************/
#define UART_RXERROR_OVERRUN    0x00000008
#define UART_RXERROR_BREAK      0x00000004
#define UART_RXERROR_PARITY     0x00000002
#define UART_RXERROR_FRAMING    0x00000001

/*****************************************************************************
*
* Values that can be passed to UARTHandshakeOutputsSet() or returned from
* UARTHandshakeOutputGet().
*
*****************************************************************************/
#define UART_OUTPUT_RTS         0x00000800
#define UART_OUTPUT_DTR         0x00000400

/*****************************************************************************
*
* Values that can be returned from UARTHandshakeInputsGet().
*
*****************************************************************************/
#define UART_INPUT_RI           0x00000100
#define UART_INPUT_DCD          0x00000004
#define UART_INPUT_DSR          0x00000002
#define UART_INPUT_CTS          0x00000001

/*****************************************************************************
*
* Values that can be passed to UARTFlowControl() or returned from
* UARTFlowControlGet().
*
*****************************************************************************/
#define UART_FLOWCONTROL_TX     0x00008000
#define UART_FLOWCONTROL_RX     0x00004000
#define UART_FLOWCONTROL_NONE   0x00000000

/*****************************************************************************
* Values that can be passed to UARTTxIntModeSet() or returned from
* UARTTxIntModeGet().
*
*****************************************************************************/
#define UART_TXINT_MODE_FIFO    0x00000000
#define UART_TXINT_MODE_EOT     0x00000010

/*****************************************************************************
* Values that can be passed to UARTClockSourceSet() or returned from
* UARTClockSourceGet().
*
*****************************************************************************/
#define UART_CLOCK_SYSTEM       0x00000000
#define UART_CLOCK_PIOSC        0x00000005

/******************************************************************************
*
* API Function prototypes
*
*****************************************************************************/
extern void uartParityModeSet(uint32_t ui32Base, uint32_t ui32Parity);
extern uint32_t UARTParityModeGet(uint32_t ui32Base);
extern void uartFIFOLevelSet(uint32_t ui32Base, uint32_t ui32TxLevel,
                             uint32_t ui32RxLevel);
extern void uartFIFOLevelGet(uint32_t ui32Base, uint32_t *pui32TxLevel,
                             uint32_t *pui32RxLevel);
extern void uartConfigSetExpClk(uint32_t ui32Base, uint32_t ui32UARTClk,
                                uint32_t ui32Baud, uint32_t ui32Config);
extern void uartConfigGetExpClk(uint32_t ui32Base, uint32_t ui32UARTClk,
                                uint32_t *pui32Baud, uint32_t *pui32Config);
extern void uartEnable(uint32_t ui32Base);
extern void uartDisable(uint32_t ui32Base);
extern void uartFIFOEnable(uint32_t ui32Base);
extern void uartFIFODisable(uint32_t ui32Base);
extern void uartEnableSIR(uint32_t ui32Base, bool bLowPower);
extern void uartDisableSIR(uint32_t ui32Base);
extern bool uartCharsAvail(uint32_t ui32Base);
extern bool uartSpaceAvail(uint32_t ui32Base);
extern int32_t uartCharGetNonBlocking(uint32_t ui32Base);
extern int32_t uartCharGet(uint32_t ui32Base);
extern bool uartCharPutNonBlocking(uint32_t ui32Base, unsigned char ucData);
extern void  uartCharPut(uint32_t ui32Base, unsigned char ucData);
extern void uartBreakCtl(uint32_t ui32Base, bool bBreakState);
extern bool uartBusy(uint32_t ui32Base);
extern void uartIntRegister(uint32_t ui32Base, void (*pfnHandler)(void));
extern void uartIntUnregister(uint32_t ui32Base);
extern void uartIntEnable(uint32_t ui32Base, uint32_t ui32IntFlags);
extern void uartIntDisable(uint32_t ui32Base, uint32_t ui32IntFlags);
extern uint32_t uartIntStatus(uint32_t ui32Base, bool bMasked);
extern void uartIntClear(uint32_t ui32Base, uint32_t ui32IntFlags);
extern void uartDMAEnable(uint32_t ui32Base, uint32_t ui32DMAFlags);
extern void uartDMADisable(uint32_t ui32Base, uint32_t ui32DMAFlags);
extern uint32_t uartRxErrorGet(uint32_t ui32Base);
extern void uartRxErrorClear(uint32_t ui32Base);
extern void uartSmartCardEnable(uint32_t ui32Base);
extern void uartSmartCardDisable(uint32_t ui32Base);
extern void uartModemControlSet(uint32_t ui32Base, uint32_t ui32Control);
extern void uartModemControlClear(uint32_t ui32Base, uint32_t ui32Control);
extern uint32_t uartModemControlGet(uint32_t ui32Base);
extern uint32_t uartModemStatusGet(uint32_t ui32Base);
extern void uartFlowControlSet(uint32_t ui32Base, uint32_t ui32Mode);
extern uint32_t uartFlowControlGet(uint32_t ui32Base);
extern void uartTxIntModeSet(uint32_t ui32Base, uint32_t ui32Mode);
extern uint32_t uartTxIntModeGet(uint32_t ui32Base);
extern void uartClockSourceSet(uint32_t ui32Base, uint32_t ui32Source);
extern uint32_t uartClockSourceGet(uint32_t ui32Base);
extern void uart9BitEnable(uint32_t ui32Base);
extern void uart9BitDisable(uint32_t ui32Base);
extern void uart9BitAddrSet(uint32_t ui32Base, uint8_t ui8Addr,
                            uint8_t ui8Mask);
extern void uart9BitAddrSend(uint32_t ui32Base, uint8_t ui8Addr);
extern void uartLoopbackEnable(uint32_t ui32Base);
extern int32_t uartReceive(uint32_t ui32Base);

/*****************************************************************************
*
* Mark the end of the C bindings section for C++ compilers.
*
*****************************************************************************/
#ifdef __cplusplus
}
#endif





#endif /* UART_H_ */
