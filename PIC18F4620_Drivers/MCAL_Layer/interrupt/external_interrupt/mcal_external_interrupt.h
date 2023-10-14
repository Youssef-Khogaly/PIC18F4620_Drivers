/* 
 * File:   mcal_external_interrupt.h
 * Author: yossef
 *
 * Created on April 5, 2023, 10:56 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*----------includes------------*/
#include "../mcal_interrupt_cfg.h"
/*--------------Macros---------------*/
#define INTERRUPT_RISING_EDGE       1U
#define INTERRUPT_FALLING_EDGE       0
#define INTERRUPT_RBx_PULLUP_ACTIVE       0
#define INTERRUPT_RBx_PULLUP_DISABLE      1U

/*--------function-Macro--------------*/

#if INTERRUPT_EXTERNAL_INTX_FEATURE == INTERRUPT_FEATURE_ENABLE

/* int 0 section , into always high priority*/

#if INTERRUPT_INTO_FEATURE == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_INT0_ENABLE()         (INTCONbits.INT0E = 1)
#define INTERRUPT_INT0_DISABLE()         (INTCONbits.INT0E = 0)
#define INTERRUPT_INT0_CLEAR_FLAG()      (INTCONbits.INT0IF = 0)
#define INTERRUPT_INT0_RISING_EDGE()       (INTCON2bits.INTEDG0 = INTERRUPT_RISING_EDGE)
#define INTERRUPT_INT0_FALLING_EDGE()       (INTCON2bits.INTEDG0 = INTERRUPT_FALLING_EDGE)

#endif
/*------------------------------------------------*/
/* EXTERNAL INTERRUPT INT 1 SECTION*/
#if INTERRUPT_INT1_FEATURE == INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_INT1_ENABLE()         (INTCON3bits.INT1E = 1)
#define INTERRUPT_INT1_DISABLE()         (INTCON3bits.INT1E = 0)
#define INTERRUPT_INT1_CLEAR_FLAG()      (INTCON3bits.INT1IF = 0)
#define INTERRUPT_INT1_RISING_EDGE()       (INTCON2bits.INTEDG1 = INTERRUPT_RISING_EDGE)
#define INTERRUPT_INT1_FALLING_EDGE()       (INTCON2bits.INTEDG1 = INTERRUPT_FALLING_EDGE)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_INT1_PRIO_HIGH()    (INTCON3bits.INT1IP = 1)
#define INTERRUPT_INT1_PRIO_LOW()     (INTCON3bits.INT1IP = 0)

#endif

#endif
/*----------------------------------------------------*/
 /*EXTERNAL INTERRUPT INT 2 SECTION*/
#if INTERRUPT_INT2_FEATURE == INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_INT2_ENABLE()         (INTCON3bits.INT2IE = 1)
#define INTERRUPT_INT2_DISABLE()         (INTCON3bits.INT2IE = 0)
#define INTERRUPT_INT2_CLEAR_FLAG()      (INTCON3bits.INT2IF = 0)
#define INTERRUPT_INT2_RISING_EDGE()       (INTCON2bits.INTEDG2 = INTERRUPT_RISING_EDGE)
#define INTERRUPT_INT2_FALLING_EDGE()       (INTCON2bits.INTEDG2 = INTERRUPT_FALLING_EDGE)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_INT2_PRIO_HIGH()    (INTCON3bits.INT2IP = 1)
#define INTERRUPT_INT2_PRIO_LOW()     (INTCON3bits.INT2IP = 0)

#endif
#endif

#endif
/*----------------------------------------------------*/
/*--------------PORTB EXTERNAL INTERRUPT SECTION--------*/
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_ONCHANGE_ENABLE()       (INTCONbits.RBIE = 1)
#define INTERRUPT_ONCHANGE_DISABLE()       (INTCONbits.RBIE = 0)
#define INTERRUPT_ONCHANGE_CLEAR_FLAG()     (INTCONbits.RBIF = 0)

#define INTERRUPT_ONCHANGE_PULLUP_ENABLE()  (INTCON2bits.RBPU = 0)
#define INTERRUPT_ONCHANGE_PULLUP_DISABLE()  (INTCON2bits.RBPU = 1)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_ONCHANGE_PRIO_HIGH()  (INTCON2bits.RBIP = 1)
#define INTERRUPT_ONCHANGE_PRIO_LOW()  (INTCON2bits.RBIP = 0)

#endif

#endif
/*---------------------------------------------------*/

/*----------user-datatypes------------*/

// pointer to function type for interrupt handler
typedef void (*InterruptHandler_t)(void);
typedef void (* EXT_interruptHandler_t)(void);
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
typedef enum {
    INTERRUPT_INT0 = 0,
            INTERRUPT_INT1,
            INTERRUPT_INT2
}interrupt_intx_src;

typedef struct {
    EXT_interruptHandler_t  Ext_interruptHandler; /*@ref InterruptHandler_t*/
    pinConfig_t mca_pin ;
    interrupt_intx_src source;
    interrupt_priority_cfg priority;
    uint8_t edge ;
}interrupt_INTx_t;
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
typedef struct {
    EXT_interruptHandler_t Ext_Interrupt_high; /*@ref EXT_interruptHandler_t*/
    EXT_interruptHandler_t Ext_interrupt_low;/* @ref EXT_interruptHandler_t */
    pinConfig_t mca_pin ;
    interrupt_priority_cfg priority;
    uint8_t pullup_status ; 
}interrupt_RBx_t;
#endif
/*------------interfaces-prototype-----*/
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
Std_ReturnType interrupt_intx_init(const interrupt_INTx_t* interrupt_obj);
Std_ReturnType interrupt_intx_Deinit(const interrupt_INTx_t* interrupt_obj);
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t* interrupt_obj);
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t* interrupt_obj);
#endif
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

