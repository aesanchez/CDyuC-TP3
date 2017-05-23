/*
** ###################################################################
**     This code is generated by the Device Initialization Tool.
**     It is overwritten during code generation.
**     USER MODIFICATION ARE PRESERVED ONLY INSIDE INTERRUPT SERVICE ROUTINES
**     OR EXPLICITLY MARKED SECTIONS
**
**     Project   : DeviceInitialization
**     Processor : MC9S08SH8CFK
**     Version   : Component 01.001, Driver 01.08, CPU db: 3.00.018
**     Datasheet : MC9S08SH8 Rev. 3 6/2008
**     Date/Time : 2017-05-23, 05:56, # CodeGen: 1
**     Abstract  :
**         This module contains device initialization code 
**         for selected on-chip peripherals.
**     Contents  :
**         Function "MCU_init" initializes selected peripherals
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################
*/

/* MODULE MCUinit */

#include <mc9s08sh8.h>                 /* I/O map for MC9S08SH8CFK */
#include "MCUinit.h"

/* Standard ANSI C types */
#ifndef int8_t
typedef signed char int8_t;
#endif
#ifndef int16_t
typedef signed int int16_t;
#endif
#ifndef int32_t
typedef signed long int int32_t;
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int uint16_t;
#endif
#ifndef uint32_t
typedef unsigned long int uint32_t;
#endif

/* User declarations and definitions */
/*   Code, declarations and definitions here will be preserved during code generation */
#include "play.h"

/* End of user declarations and definitions */


/*
** ===================================================================
**     Method      :  MCU_init (component MC9S08SH8_24)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/
void MCU_init(void)
{
  /* ### MC9S08SH8_24 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /* Common initialization of the write once registers */
  /* SOPT1: COPT=0,STOPE=0,IICPS=0,BKGDPE=1,RSTPE=0 */
  SOPT1 = 0x02U;                                      
  /* SPMSC1: LVWF=0,LVWACK=0,LVWIE=0,LVDRE=1,LVDSE=1,LVDE=1,BGBE=0 */
  SPMSC1 = 0x1CU;                                      
  /* SPMSC2: LVDV=0,LVWV=0,PPDF=0,PPDACK=0,PPDC=0 */
  SPMSC2 = 0x00U;                                      
  /*  System clock initialization */
  /*lint -save  -e923 Disable MISRA rule (11.3) checking. */
  if (*(unsigned char*far)0xFFAFU != 0xFFU) { /* Test if the device trim value is stored on the specified address */
    ICSTRM = *(unsigned char*far)0xFFAFU; /* Initialize ICSTRM register from a non volatile memory */
    ICSSC = *(unsigned char*far)0xFFAEU; /* Initialize ICSSC register from a non volatile memory */
  }
  /*lint -restore Enable MISRA rule (11.3) checking. */
  /* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=0,IREFSTEN=0 */
  ICSC1 = 0x04U;                       /* Initialization of the ICS control register 1 */
  /* ICSC2: BDIV=1,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  ICSC2 = 0x40U;                       /* Initialization of the ICS control register 2 */
  while(ICSSC_IREFST == 0U) {          /* Wait until the source of reference clock is internal clock */
  }
  /* GNGC: GNGPS7=0,GNGPS6=0,GNGPS5=0,GNGPS4=0,GNGPS3=0,GNGPS2=0,GNGPS1=0,GNGEN=0 */
  GNGC = 0x00U;                                      
  /* Common initialization of the CPU registers */
  /* PTASE: PTASE4=0,PTASE3=0,PTASE2=0,PTASE1=0,PTASE0=0 */
  PTASE &= (unsigned char)~(unsigned char)0x1FU;                     
  /* PTBSE: PTBSE7=0,PTBSE6=0,PTBSE5=0,PTBSE4=0,PTBSE3=0,PTBSE2=0,PTBSE1=0,PTBSE0=0 */
  PTBSE = 0x00U;                                      
  /* PTCSE: PTCSE3=0,PTCSE2=0,PTCSE1=0,PTCSE0=0 */
  PTCSE &= (unsigned char)~(unsigned char)0x0FU;                     
  /* PTADS: PTADS4=0,PTADS3=0,PTADS2=0,PTADS1=0,PTADS0=0 */
  PTADS = 0x00U;                                      
  /* PTBDS: PTBDS7=0,PTBDS6=0,PTBDS5=0,PTBDS4=0,PTBDS3=0,PTBDS2=0,PTBDS1=0,PTBDS0=0 */
  PTBDS = 0x00U;                                      
  /* PTCDS: PTCDS3=0,PTCDS2=0,PTCDS1=0,PTCDS0=0 */
  PTCDS = 0x00U;                                      
  /* ### */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm CLI;                             /* Enable interrupts */
  /*lint -restore Enable MISRA rule (1.1) checking. */

} /*MCU_init*/


/*lint -save  -e765 Disable MISRA rule (8.10) checking. */
/*lint -restore Enable MISRA rule (8.10) checking. */

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
/* Initialization of the CPU registers in FLASH */
/* NVPROT: FPS7=1,FPS6=1,FPS5=1,FPS4=1,FPS3=1,FPS2=1,FPS1=1,FPDIS=1 */
static const unsigned char NVPROT_INIT @0x0000FFBDU = 0xFFU;
/* NVOPT: KEYEN=0,FNORED=1,SEC01=1,SEC00=0 */
static const unsigned char NVOPT_INIT @0x0000FFBFU = 0x7EU;
/*lint -restore Enable MISRA rule (1.1) checking. */



extern near void _Startup(void);

/* Interrupt vector table */
#ifndef UNASSIGNED_ISR
  #define UNASSIGNED_ISR ((void(*near const)(void)) 0xFFFF) /* unassigned interrupt service routine */
#endif

/*lint -save  -e923 Disable MISRA rule (11.3) checking. */
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static void (* near const _vect[])(void) @0xFFC0 = { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
         UNASSIGNED_ISR,               /* Int.no. 31 VReserved31 (at FFC0)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 30 Vacmp (at FFC2)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 29 VReserved29 (at FFC4)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 28 VReserved28 (at FFC6)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 27 VReserved27 (at FFC8)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 26 Vmtim (at FFCA)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 25 Vrtc (at FFCC)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 24 Viic (at FFCE)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 23 Vadc (at FFD0)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 22 VReserved22 (at FFD2)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 21 Vportb (at FFD4)                Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 20 Vporta (at FFD6)                Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 19 VReserved19 (at FFD8)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 18 Vscitx (at FFDA)                Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 17 Vscirx (at FFDC)                Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 16 Vscierr (at FFDE)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 15 Vspi (at FFE0)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 14 Vtpm2ovf (at FFE2)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 13 Vtpm2ch1 (at FFE4)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 12 Vtpm2ch0 (at FFE6)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 11 Vtpm1ovf (at FFE8)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 10 VReserved10 (at FFEA)           Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  9 VReserved9 (at FFEC)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  8 VReserved8 (at FFEE)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  7 VReserved7 (at FFF0)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  6 Vtpm1ch1 (at FFF2)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  5 Vtpm1ch0 (at FFF4)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  4 VReserved4 (at FFF6)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  3 Vlvd (at FFF8)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  2 Virq (at FFFA)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  1 Vswi (at FFFC)                  Unassigned */
         _Startup                      /* Int.no.  0 Vreset (at FFFE)                Reset vector */
};
/*lint -restore Enable MISRA rule (11.3) checking. */





/*
** ===================================================================
**     Interrupt handler : isrVtpm1ch0
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void isrVtpm1ch0(void)
{
  /* Write your interrupt code here ... */
	Tpm1CH0_Handler();
	TPM1C0SC_CH0F = 0;  // clear interrupt flag
}
/* end of isrVtpm1ch0 */


/*
** ===================================================================
**     Interrupt handler : isrVtpm1ch1
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void isrVtpm1ch1(void)
{
  /* Write your interrupt code here ... */
	Tpm1CH1_Handler();
	TPM1C1SC_CH1F = 0; // clear interrupt flag

}
/* end of isrVtpm1ch1 */


/*lint -save  -e765 Disable MISRA rule (8.10) checking. */
/*
** ===================================================================
**     Interrupt handler : isrVtpm1ovf
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void isrVtpm1ovf(void)
{
  /* Write your interrupt code here ... */

}
/* end of isrVtpm1ovf */

/* END MCUinit */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
