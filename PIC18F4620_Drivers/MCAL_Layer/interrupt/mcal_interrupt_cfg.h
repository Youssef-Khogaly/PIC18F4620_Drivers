/* 
 * File:   mcal_interrupt_cfg.h
 * Author: yossef
 *
 * Created on April 5, 2023, 10:49 AM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H
/*----------includes------------*/
#include "../mcal_std_types.h"
#include"../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
/*--------------Macros---------------*/

#define INTERRUPT_OCCUR         1U
#define INTERRUPT_NOT_OCCUR     0
#define INTERRUPT_PRIORITY_ENABLE       1U
#define INTERRUPT_PRIORITY_DISABLE      0


/*--------function-Macro--------------*/



/*while IPEN =1 interrupt priority levels enable*/
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_PRIORITY_FEATURE_ENABLE() (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORITY_FEATURE_DISABLE() (RCONbits.IPEN = 0)

#define INTERRUPT_HIGH_PRIORITY_ENABLE()    (INTCONbits.GIEH = 1)
#define INTERRUPT_HIGH_PRIORITY_DISABLE()   (INTCONbits.GIEH = 0)

#define INTERRUPT_LOW_PRIORITY_ENABLE()    (INTCONbits.GIEL = 1)
#define INTERRUPT_LOW_PRIORITY_DISABLE()    (INTCONbits.GIEL = 0)

/* while IPEN = 0 - priority interrupt disable*/

#else

#define INTERRUPT_ENABLE_UNMASKED()          (INTCONbits.GIE = 1)
#define INTERRUPT_DISABLE_UNMASKED()         (INTCONbits.GIE = 0)

#define INTERRUPT_ENABLE_UNMASKED_PERIPHERALS()    (INTCONbits.PEIE = 1)
#define INTERRUPT_DISABLE_UNMASKED_PERIPHERALS()   (INTCONbits.PEIE = 0)

#endif




/*----------user-datatypes------------*/
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0 ,
            INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;
/*------------interfaces-prototype-----*/

#endif	/* MCAL_INTERRUPT_CFG_H */

