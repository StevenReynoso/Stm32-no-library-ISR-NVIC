
/* === Cortex-M4 Startup Assembly ===
   Initializes the MCU at boot:
   - Defines interrupt vector table
   - Copies initialized data from FLASH to SRAM (.data)
   - Zeros uninitialized memory (.bss)
   - Jumps to main()
*/

.syntax unified                                 /* Use unified ARM syntax */
.cpu cortex-m4                                  /* Target Cortex-M4 CPU */
.thumb                                          /* Use Thumb instruction set */

/* === Interrupt Vector Table ===
   Placed in its own section in FLASH.
   First word: initial stack pointer
   Second word: address of Reset_Handler
   Remaining: ISR addresses or infinite loops
*/
.section .isr_vector, "a", %progbits
.global _vector_table
.type _vector_table, %object
.size _vector_table, . - _vector_table

_vector_table:
    .word _estack
    .word Reset_Handler
    .word NMI
    .word Hard_Fault
    .word Mem_Manage
    .word Bus_Fault
    .word Usage_Fault
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVCall
    .word Debug_Monitor
    .word 0
    .word PendSV
    .word Systick
    .word 0          // IRQ0: WWDG
    .word 0          // IRQ1: PVD
    .word 0          // IRQ2: TAMP_STAMP
    .word 0          // IRQ3: RTC_WKUP
    .word 0          // IRQ4: FLASH
    .word 0          // IRQ5: RCC
    .word 0          // IRQ6: EXTI0
    .word 0          // IRQ7: EXTI1
    .word 0          // IRQ8: EXTI2
    .word 0          // IRQ9: EXTI3
    .word 0          // IRQ10: EXTI4
    .word 0          // IRQ11: DMA1_Stream0
    .word 0          // IRQ12: DMA1_Stream1
    .word 0          // IRQ13: DMA1_Stream2
    .word 0          // IRQ14: DMA1_Stream3
    .word 0          // IRQ15: DMA1_Stream4
    .word 0          // IRQ16: DMA1_Stream5
    .word 0          // IRQ17: DMA1_Stream6
    .word 0          // IRQ18: ADC
    .word 0          // IRQ19: CAN1_TX
    .word 0          // IRQ20: CAN1_RX0
    .word 0          // IRQ21: CAN1_RX1
    .word 0          // IRQ22: CAN1_SCE
    .word EXTI9_5_IRQHandler  // IRQ23


.section .text                                  /* Start of program code */
.global Reset_Handler
.type Reset_Handler, %function

/* === Reset Handler ===
   Runs after power-on or reset:
   - Copies .data section from FLASH to SRAM
   - Zeros .bss section in SRAM
   - Jumps to main()
*/
Reset_Handler:
    ldr r0, =_sdata                             /* Start of .data in SRAM */
    ldr r1, =_etext                             /* End of .text in FLASH (start of .data in FLASH) */
    ldr r2, =_edata                             /* End of .data in SRAM */
                    
.data_copy:                 
    cmp r0, r2                                  /* If r0 < r2, copy from FLASH to SRAM */
    ittt lt                 
    ldrlt r3, [r1], #4                  
    strlt r3, [r0], #4                  
    blt .data_copy                  
                    
    ldr r0, =_sbss                              /* Start of .bss in SRAM */
    ldr r1, =_ebss                              /* End of .bss in SRAM */
    movs r2, #0                                 /* Clear value = 0 */
                    
.bss_clear:                 
    cmp r0, r1                                  /* If r0 < r1, clear memory */
    it lt                   
    strlt r2, [r0], #4                  
    blt .bss_clear                  
                    
    bl main                                     /* Jump to main() */
                    
infinite_loop:                  
    b infinite_loop                             /* Trap if main returns */

/* === Default Interrupt Handlers ===
   Weak aliases that point to infinite loop
   Can be overridden in user code
*/
.weak NMI, Hard_Fault, Mem_Manage, Bus_Fault, Usage_Fault, SVCall, Debug_Monitor, PendSV, Systick, EXTI9_5_IRQHandler
.thumb_set NMI,           infinite_loop
.thumb_set Hard_Fault,    infinite_loop
.thumb_set Mem_Manage,    infinite_loop
.thumb_set Bus_Fault,     infinite_loop
.thumb_set Usage_Fault,   infinite_loop
.thumb_set SVCall,        infinite_loop
.thumb_set Debug_Monitor, infinite_loop
.thumb_set PendSV,        infinite_loop
.thumb_set Systick,       infinite_loop

/* EXTI9_5_IRQHandler is implemented in C, so do not alias it */

