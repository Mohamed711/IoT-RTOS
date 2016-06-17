
#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define configUSE_MALLOC_FAILED_HOOK 1
/*
#ifndef configUSE_MALLOC_FAILED_HOOK
#define configUSE_MALLOC_FAILED_HOOK 0
#endif
*/
#define KitType  0  //till we know how to define the kit

#if KitType == 0 // atmega32
#define configTOTAL_HEAP_SIZE		( (size_t ) ( 1500 ))
#define portBYTE_ALIGNMENT  4 //because we want it work on 32 bit word alignment
#endif
#if KitType == 1 //tivaC
#define configTOTAL_HEAP_SIZE		( (size_t ) ( 30000 ))
#define portBYTE_ALIGNMENT  8 //because we want it work on 64 bit word alignment
#endif


/*portBYTE_ALIGNMENT defined by user but for default value portBYTE_ALIGNMENT=8  need to implement this as structure*/
#if portBYTE_ALIGNMENT == 8
#define portBYTE_ALIGNMENT_MASK ( 0x0007 )
#endif

#if portBYTE_ALIGNMENT == 4
#define portBYTE_ALIGNMENT_MASK	( 0x0003 )
#endif

#if portBYTE_ALIGNMENT == 2
#define portBYTE_ALIGNMENT_MASK	( 0x0001 )
#endif

#if portBYTE_ALIGNMENT == 1
#define portBYTE_ALIGNMENT_MASK	( 0x0000 )
#endif

#ifndef portBYTE_ALIGNMENT_MASK
#error "Invalid portBYTE_ALIGNMENT definition"
#endif



#endif /* CONFIG_H_ */