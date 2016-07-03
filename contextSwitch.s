 AREA     ARMex, CODE, READONLY
                                ; Name this block of code ARMex
        ENTRY                   ; Mark first instruction to execute
		
contextSwitch:

	movs   r2, r0	;old
	 	;new
	;mrs    r0, msp                    ;get stack pointer from user mode */
	stmea  r2!,{r4-r11}               ; save regs */
	sub r2, r2, #4                  ;r0
	sub r2, r2, #12				;r1-r3
	stmea  r2!, {r12}
	sub r2, r2, #4			;lr
	;stmea  r2!, {?}		;pc

	;str    r2, [r0]                   ; write r0 to pdc->sp */
	
	movs   r0, r1                 ; load tcb->sp to register 1 */
	ldmia  r0!, {r4-r11}              ; restore other registers */
	add r0, r0, #4
	add r0, r0, #12
	ldmia  r0!, {r12}
	ldmia  r0!, {lr}	;process kill
	ldmia  r0!, {pc}	;psp
	;msr psp, r1                   ; restore user mode SP to PSP reg */
	bx     pc                        ; load exception return value to PC,
	                                           ; causes end of exception*/
        END                     ; Mark end of file