/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuHardFault.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : HardFault
**     Version     : Component 01.024, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2022-07-19, 17:00, # CodeGen: 782
**     Abstract    :
**          Component to simplify hard faults for ARM (Kinetis, S32K).
**     Settings    :
**          Component name                                 : McuHardFault
**     Contents    :
**         HardFaultHandler - void McuHardFault_HardFaultHandler(void);
**         Deinit           - void McuHardFault_Deinit(void);
**         Init             - void McuHardFault_Init(void);
**
** * Copyright (c) 2014-2022, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file McuHardFault.h
** @version 01.00
** @brief
**          Component to simplify hard faults for ARM (Kinetis, S32K).
*/         
/*!
**  @addtogroup McuHardFault_module McuHardFault module documentation
**  @{
*/         

/* MODULE McuHardFault. */

#include "McuHardFault.h"

#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M

/*
** ===================================================================
**     Method      :  McuHardFault_HandlerC (component HardFault)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/**
 * This is called from the HardFaultHandler with a pointer the Fault stack
 * as the parameter. We can then read the values from the stack and place them
 * into local variables for ease of reading.
 * We then read the various Fault Status and Address Registers to help decode
 * cause of the fault.
 * The function ends with a BKPT instruction to force control back into the debugger
 */
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
void McuHardFault_HandlerC(uint32_t *hardfault_args)
{
  /*lint -save  -e550 Symbol not accessed. */
  static volatile unsigned long stacked_r0;
  static volatile unsigned long stacked_r1;
  static volatile unsigned long stacked_r2;
  static volatile unsigned long stacked_r3;
  static volatile unsigned long stacked_r12;
  static volatile unsigned long stacked_lr;
  static volatile unsigned long stacked_pc;
  static volatile unsigned long stacked_psr;
  static volatile unsigned long _CFSR;
  static volatile unsigned long _HFSR;
  static volatile unsigned long _DFSR;
  static volatile unsigned long _AFSR;
  static volatile unsigned long _BFAR;
  static volatile unsigned long _MMAR;
  stacked_r0 = ((unsigned long)hardfault_args[0]);          /* http://www.asciiworld.com/-Smiley,20-.html                                   */
  stacked_r1 = ((unsigned long)hardfault_args[1]);          /*                         oooo$$$$$$$$$$$$oooo                                 */
  stacked_r2 = ((unsigned long)hardfault_args[2]);          /*                      oo$$$$$$$$$$$$$$$$$$$$$$$$o                             */
  stacked_r3 = ((unsigned long)hardfault_args[3]);          /*                    oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o         o$   $$ o$      */
  stacked_r12 = ((unsigned long)hardfault_args[4]);         /*    o $ oo        o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o       $$ $$ $$o$     */
  stacked_lr = ((unsigned long)hardfault_args[5]);          /* oo $ $ "$      o$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$o       $$$o$$o$      */
  stacked_pc = ((unsigned long)hardfault_args[6]);          /* "$$$$$$o$     o$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$o    $$$$$$$$       */
  stacked_psr = ((unsigned long)hardfault_args[7]);         /*   $$$$$$$    $$$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$       */
                                                            /*   $$$$$$$$$$$$$$$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$$$$$$  """$$$         */
  /* Configurable Fault Status Register */                  /*    "$$$""""$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     "$$$        */
  /* Consists of MMSR, BFSR and UFSR */                     /*     $$$   o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     "$$$o      */
  _CFSR = (*((volatile unsigned long *)(0xE000ED28)));      /*    o$$"   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$o     */
                                                            /*    $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" "$$$$$$ooooo$$$$o   */
  /* Hard Fault Status Register */                          /*   o$$$oooo$$$$$  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   o$$$$$$$$$$$$$$$$$  */
  _HFSR = (*((volatile unsigned long *)(0xE000ED2C)));      /*   $$$$$$$$"$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     $$$$""""""""        */
                                                            /*  """"       $$$$    "$$$$$$$$$$$$$$$$$$$$$$$$$$$$"      o$$$                 */
  /* Debug Fault Status Register */                         /*             "$$$o     """$$$$$$$$$$$$$$$$$$"$$"         $$$                  */
  _DFSR = (*((volatile unsigned long *)(0xE000ED30)));      /*               $$$o          "$$""$$$$$$""""           o$$$                   */
                                                            /*                $$$$o                                o$$$"                    */
  /* Auxiliary Fault Status Register */                     /*                 "$$$$o      o$$$$$$o"$$$$o        o$$$$                      */
  _AFSR = (*((volatile unsigned long *)(0xE000ED3C)));      /*                   "$$$$$oo     ""$$$$o$$$$$o   o$$$$""                       */
                                                            /*                      ""$$$$$oooo  "$$$o$$$$$$$$$"""                          */
                                                            /*                         ""$$$$$$$oo $$$$$$$$$$                               */
  /* Read the Fault Address Registers. */                   /*                                 """"$$$$$$$$$$$                              */
  /* These may not contain valid values. */                 /*                                     $$$$$$$$$$$$                             */
  /* Check BFARVALID/MMARVALID to see */                    /*                                      $$$$$$$$$$"                             */
  /* if they are valid values */                            /*                                       "$$$""                                 */
  /* MemManage Fault Address Register */
  _MMAR = (*((volatile unsigned long *)(0xE000ED34)));
  /* Bus Fault Address Register */
  _BFAR = (*((volatile unsigned long *)(0xE000ED38)));

#if 0 /* experimental, seems not to work properly with GDB in KDS V3.2.0 */
#ifdef __GNUC__ /* might improve stack, see https://www.element14.com/community/message/199113/l/gdb-assisted-debugging-of-hard-faults#199113 */
  __asm volatile (
      "tst lr,#4     \n" /* check which stack pointer we are using */
      "ite eq        \n"
      "mrseq r0, msp \n" /* use MSP */
      "mrsne r0, psp \n" /* use PSP */
      "mov sp, r0    \n" /* set stack pointer so GDB shows proper stack frame */
  );
#endif
#endif
  __asm("BKPT #0\n") ; /* cause the debugger to stop */
  /*lint -restore */
}

/*
** ===================================================================
**     Method      :  HardFaultHandler (component HardFault)
**
**     Description :
**         Hard Fault Handler
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
__attribute__((naked))
#if McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_RPI_PICO
void isr_hardfault(void)
#elif McuLib_CONFIG_SDK_VERSION_USED != McuLib_CONFIG_SDK_PROCESSOR_EXPERT
void HardFault_Handler(void)
#else
void McuHardFault_HardFaultHandler(void)
#endif
{
  __asm volatile (
    ".syntax unified              \n"  /* needed for the 'adds r1,#2' below */
    " movs r0,#4                  \n"  /* load bit mask into R0 */
    " mov r1, lr                  \n"  /* load link register into R1 */
    " tst r0, r1                  \n"  /* compare with bitmask */
    " beq _MSP                    \n"  /* if bitmask is set: stack pointer is in PSP. Otherwise in MSP */
    " mrs r0, psp                 \n"  /* otherwise: stack pointer is in PSP */
    " b _GetPC                    \n"  /* go to part which loads the PC */
  "_MSP:                          \n"  /* stack pointer is in MSP register */
    " mrs r0, msp                 \n"  /* load stack pointer into R0 */
  "_GetPC:                        \n"  /* find out where the hard fault happened */
    " ldr r1,[r0,#24]             \n"  /* load program counter into R1. R1 contains address of the next instruction where the hard fault happened */
#if McuHardFault_CONFIG_SETTING_SEMIHOSTING
  /* The following code checks if the hard fault is caused by a semihosting BKPT instruction which is "BKPT 0xAB" (opcode: 0xBEAB)
     The idea is taken from the MCUXpresso IDE/SDK code, so credits and kudos to the MCUXpresso IDE team! */
    " ldrh r2,[r1]                \n"  /* load opcode causing the fault */
    " ldr r3,=0xBEAB              \n"  /* load constant 0xBEAB (BKPT 0xAB) into R3" */
    " cmp r2,r3                   \n"  /* is it the BKPT 0xAB? */
    " beq _SemihostReturn         \n"  /* if yes, return from semihosting */
    " b McuHardFault_HandlerC   \n"  /* if no, dump the register values and halt the system */
  "_SemihostReturn:               \n"  /* returning from semihosting fault */
    " adds r1,#2                  \n"  /* r1 points to the semihosting BKPT instruction. Adjust the PC to skip it (2 bytes) */
    " str r1,[r0,#24]             \n"  /* store back the adjusted PC value to the interrupt stack frame */
    " movs r1,#32                 \n"  /* need to pass back a return value to emulate a successful semihosting operation. 32 is an arbitrary value */
    " str r1,[r0,#0]              \n"  /* store the return value on the stack frame */
    " bx lr                       \n"  /* return from the exception handler back to the application */
#else
    " b McuHardFault_HandlerC   \n"  /* decode more information. R0 contains pointer to stack frame */
#endif
  );
}

/*
** ===================================================================
**     Method      :  Deinit (component HardFault)
**
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuHardFault_Deinit(void)
{
#if McuHardFault_CONFIG_SETTING_DISABLE_WRITE_BUFFER
  #if McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
    SCB_ACTLR &= ~(SCB_ACTLR_DISDEFWBUF_MASK); /* write buffer bit, see https://community.nxp.com/docs/DOC-103810 */
  #elif McuLib_CONFIG_NXP_SDK_USED && McuLib_McuLib_CONFIG_CORTEX_M!=7 /* not for M7? */
    SCnSCB->ACTLR &= ~SCnSCB_ACTLR_DISDEFWBUF_Msk;
  #endif
#endif
}

/*
** ===================================================================
**     Method      :  Init (component HardFault)
**
**     Description :
**         Initializes the driver
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuHardFault_Init(void)
{
#if McuHardFault_CONFIG_SETTING_DISABLE_WRITE_BUFFER
  #if McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_PROCESSOR_EXPERT
    SCB_ACTLR |= SCB_ACTLR_DISDEFWBUF_MASK; /* write buffer bit, see https://community.nxp.com/docs/DOC-103810 */
  #elif McuLib_CONFIG_NXP_SDK_USED && McuLib_McuLib_CONFIG_CORTEX_M!=7 /* not for M7? */
    SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;
  #endif
#endif
}


#endif /* McuLib_CONFIG_CPU_IS_ARM_CORTEX_M */
/* END McuHardFault. */

/*!
** @}
*/
