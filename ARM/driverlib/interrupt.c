//*****************************************************************************
//
// interrupt.c - Driver for the NVIC Interrupt Controller.
//
// Copyright (c) 2005-2015 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// This is part of revision 2.1.2.111 of the Tiva Peripheral Driver Library.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup interrupt_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "../inc/hw_ints.h"
#include "../inc/hw_nvic.h"
#include "../inc/hw_types.h"
//#include "cpu.h"
#include "debug.h"
#include "interrupt.h"

//*****************************************************************************
//
// This is a mapping between priority grouping encodings and the number of
// preemption priority bits.
//
//*****************************************************************************
static const uint32_t g_pui32Priority[] =
{
    NVIC_APINT_PRIGROUP_0_8, NVIC_APINT_PRIGROUP_1_7, NVIC_APINT_PRIGROUP_2_6,
    NVIC_APINT_PRIGROUP_3_5, NVIC_APINT_PRIGROUP_4_4, NVIC_APINT_PRIGROUP_5_3,
    NVIC_APINT_PRIGROUP_6_2, NVIC_APINT_PRIGROUP_7_1
};

//*****************************************************************************
//
// This is a mapping between interrupt number and the register that contains
// the priority encoding for that interrupt.
//
//*****************************************************************************
static const uint32_t g_pui32Regs[] =
{
    0, NVIC_SYS_PRI1, NVIC_SYS_PRI2, NVIC_SYS_PRI3, NVIC_PRI0, NVIC_PRI1,
    NVIC_PRI2, NVIC_PRI3, NVIC_PRI4, NVIC_PRI5, NVIC_PRI6, NVIC_PRI7,
    NVIC_PRI8, NVIC_PRI9, NVIC_PRI10, NVIC_PRI11, NVIC_PRI12, NVIC_PRI13,
    NVIC_PRI14, NVIC_PRI15, NVIC_PRI16, NVIC_PRI17, NVIC_PRI18, NVIC_PRI19,
    NVIC_PRI20, NVIC_PRI21, NVIC_PRI22, NVIC_PRI23, NVIC_PRI24, NVIC_PRI25,
    NVIC_PRI26, NVIC_PRI27, NVIC_PRI28, NVIC_PRI29, NVIC_PRI30, NVIC_PRI31,
    NVIC_PRI32, NVIC_PRI33, NVIC_PRI34
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt enable for that
// interrupt.
//
//*****************************************************************************
static const uint32_t g_pui32EnRegs[] =
{
    NVIC_EN0, NVIC_EN1, NVIC_EN2, NVIC_EN3, NVIC_EN4
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt disable for that
// interrupt.
//
//*****************************************************************************
static const uint32_t g_pui32Dii16Regs[] =
{
    NVIC_DIS0, NVIC_DIS1, NVIC_DIS2, NVIC_DIS3, NVIC_DIS4
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt pend for that interrupt.
//
//*****************************************************************************
static const uint32_t g_pui32PendRegs[] =
{
    NVIC_PEND0, NVIC_PEND1, NVIC_PEND2, NVIC_PEND3, NVIC_PEND4
};

//*****************************************************************************
//
// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt unpend for that
// interrupt.
//
//*****************************************************************************
static const uint32_t g_pui32UnpendRegs[] =
{
    NVIC_UNPEND0, NVIC_UNPEND1, NVIC_UNPEND2, NVIC_UNPEND3, NVIC_UNPEND4
};

//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler for all interrupts.  It simply loops
//! forever so that the system state is preserved for observation by a
//! debugger.  Since interrupts must be disabled before unregistering the
//! corresponding handler, this should never be called during normal operation.
//!
//! \return None.
//
//*****************************************************************************
static void
_IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// The processor vector table.
//
// This contains a list of the handlers for the various interrupt sources in
// the system.  The layout of this list is defined by the hardware; assertion
// of an interrupt causes the processor to start executing directly at the
// address given in the corresponding location in this list.
//
//*****************************************************************************
//
// Set the size of the vector table to the largest number of interrupts of
// any device
//
#undef NUM_INTERRUPTS
#define NUM_INTERRUPTS                          155
#if defined(ewarm)
#pragma data_alignment=1024
static __no_init void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void) @ "VTABLE";
#elif defined(sourcerygxx)
static __attribute__((section(".cs3.region-head.ram")))
void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void) __attribute__ ((aligned(1024)));
#elif defined(ccs) || defined(DOXYGEN)
#pragma DATA_ALIGN(g_pfnRAMVectors, 1024)
#pragma DATA_SECTION(g_pfnRAMVectors, ".vtable")
void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void);
#else
static __attribute__((section("vtable")))
void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void) __attribute__((aligned(1024)));
#endif



//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//!
//! \param ui32Interrupt specifies the interrupt in question.
//! \param pfnHandler is a pointer to the function to be called.
//!
//! This function is used to specify the handler function to be called when the
//! given interrupt is asserted to the processor.  The \e ui32Interrupt
//! parameter must be one of the valid \b INT_* values listed in Peripheral
//! Driver Library User's Guide and defined in the inc/hw_ints.h header file.
//! When the interrupt occurs, if it is enabled (via IntEnable()), the handler
//! function is called in interrupt context.  Because the handler function can
//! preempt other code, care must be taken to protect memory or peripherals
//! that are accessed by the handler and other non-handler code.
//!
//! \note The use of this function (directly or indirectly via a peripheral
//! driver interrupt register function) moves the interrupt vector table from
//! flash to SRAM.  Therefore, care must be taken when linking the application
//! to ensure that the SRAM vector table is located at the beginning of SRAM;
//! otherwise the NVIC does not look in the correct portion of memory for the
//! vector table (it requires the vector table be on a 1 kB memory alignment).
//! Normally, the SRAM vector table is so placed via the use of linker scripts.
//! See the discussion of compile-time versus run-time interrupt handler
//! registration in the introduction to this chapter.
//!
//! \b Example: Set the UART 0 interrupt handler.
//!
//! \verbatim
//!
//! //
//! // UART 0 interrupt handler.
//! //
//! void
//! UART0Handler(void)
//! {
//!     //
//!     // Handle interrupt.
//!     //
//! }
//!
//! //
//! // Set the UART 0 interrupt handler.
//! //
//! IntRegister(INT_UART0, UART0Handler);
//!
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
IntRegister(uint32_t ui32Interrupt, void (*pfnHandler)(void))
{
    uint32_t ui32Idx, ui32Value;

    //
    // Check the arguments.
    //
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    //
    // Make sure that the RAM vector table is correctly aligned.
    //
    ASSERT(((uint32_t)g_pfnRAMVectors & 0x000003ff) == 0);

    //
    // See if the RAM vector table has been initialized.
    //
    if(HWREG(NVIC_VTABLE) != (uint32_t)g_pfnRAMVectors)
    {
        //
        // Copy the vector table from the beginning of FLASH to the RAM vector
        // table.
        //
        ui32Value = HWREG(NVIC_VTABLE);
        for(ui32Idx = 0; ui32Idx < NUM_INTERRUPTS; ui32Idx++)
        {
            g_pfnRAMVectors[ui32Idx] = (void (*)(void))HWREG((ui32Idx * 4) +
                                                             ui32Value);
        }

        //
        // Point the NVIC at the RAM vector table.
        //
        HWREG(NVIC_VTABLE) = (uint32_t)g_pfnRAMVectors;
    }

    //
    // Save the interrupt handler.
    //
    g_pfnRAMVectors[ui32Interrupt] = pfnHandler;
}

//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! \param ui32Interrupt specifies the interrupt in question.
//!
//! This function is used to indicate that no handler is called when the
//! given interrupt is asserted to the processor.  The \e ui32Interrupt
//! parameter must be one of the valid \b INT_* values listed in Peripheral
//! Driver Library User's Guide and defined in the inc/hw_ints.h header file.
//! The interrupt source is automatically disabled (via IntDisable()) if
//! necessary.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \b Example: Reset the UART 0 interrupt handler to the default handler.
//!
//! \verbatim
//! //
//! // Reset the UART 0 interrupt handler to the default handler.
//! //
//! IntUnregister(INT_UART0);
//!
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
IntUnregister(uint32_t ui32Interrupt)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    //
    // Reset the interrupt handler.
    //
    g_pfnRAMVectors[ui32Interrupt] = _IntDefaultHandler;
}



//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param ui32Interrupt specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  The
//! \e ui32Interrupt parameter must be one of the valid \b INT_* values listed
//! in Peripheral Driver Library User's Guide and defined in the inc/hw_ints.h
//! header file. Other enables for the interrupt (such as at the peripheral
//! level) are unaffected by this function.
//!
//! \b Example: Enable the UART 0 interrupt.
//!
//! \verbatim
//! //
//! // Enable the UART 0 interrupt in the interrupt controller.
//! //
//! IntEnable(INT_UART0);
//!
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
IntEnable(uint32_t ui32Interrupt)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    //
    // Determine the interrupt to enable.
    //
    if(ui32Interrupt == FAULT_MPU)
    {
        //
        // Enable the MemManage interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_MEM;
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
        //
        // Enable the bus fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_BUS;
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
        //
        // Enable the usage fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_USAGE;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        //
        // Enable the System Tick interrupt.
        //
        HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
    }
    else if(ui32Interrupt >= 16)
    {
        //
        // Enable the general interrupt.
        //
        HWREG(g_pui32EnRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param ui32Interrupt specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  The
//! \e ui32Interrupt parameter must be one of the valid \b INT_* values listed
//! in Peripheral Driver Library User's Guide and defined in the inc/hw_ints.h
//! header file.  Other enables for the interrupt (such as at the peripheral
//! level) are unaffected by this function.
//!
//! \b Example: Disable the UART 0 interrupt.
//!
//! \verbatim
//! //
//! // Disable the UART 0 interrupt in the interrupt controller.
//! //
//! IntDisable(INT_UART0);
//!
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
IntDisable(uint32_t ui32Interrupt)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    //
    // Determine the interrupt to disable.
    //
    if(ui32Interrupt == FAULT_MPU)
    {
        //
        // Disable the MemManage interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_MEM);
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
        //
        // Disable the bus fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_BUS);
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
        //
        // Disable the usage fault interrupt.
        //
        HWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_USAGE);
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        //
        // Disable the System Tick interrupt.
        //
        HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);
    }
    else if(ui32Interrupt >= 16)
    {
        //
        // Disable the general interrupt.
        //
        HWREG(g_pui32Dii16Regs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
