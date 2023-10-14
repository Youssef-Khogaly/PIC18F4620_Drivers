/* 
 * File:   hal_timer2.h
 * Author: yossef
 *
 * Created on July 14, 2023, 2:59 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*-------------Includes------------*/
#include "../mcal_std_types.h"
#include "../../../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../GPIO/HAL_GPIO.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"

/*---------------Macros------------*/

            //prescaler
#define TIMER2_PRESCALER_DIV_1_CFG       0
#define TIMER2_PRESCALER_DIV_4_CFG       1
#define TIMER2_PRESCALER_DIV_16_CFG      2

            //postscaler
#define TIMER2_POSTSCALER_DIV_1_CFG       0
#define TIMER2_POSTSCALER_DIV_2_CFG       1
#define TIMER2_POSTSCALER_DIV_3_CFG       2
#define TIMER2_POSTSCALER_DIV_4_CFG       3
#define TIMER2_POSTSCALER_DIV_5_CFG       4
#define TIMER2_POSTSCALER_DIV_6_CFG       5
#define TIMER2_POSTSCALER_DIV_7_CFG       6
#define TIMER2_POSTSCALER_DIV_8_CFG       7
#define TIMER2_POSTSCALER_DIV_9_CFG       8
#define TIMER2_POSTSCALER_DIV_10_CFG      9
#define TIMER2_POSTSCALER_DIV_11_CFG      10
#define TIMER2_POSTSCALER_DIV_12_CFG      11
#define TIMER2_POSTSCALER_DIV_13_CFG      12
#define TIMER2_POSTSCALER_DIV_14_CFG      13
#define TIMER2_POSTSCALER_DIV_15_CFG      14
#define TIMER2_POSTSCALER_DIV_16_CFG      15

/*--------------Func Macro---------*/

#define TIMER2_ENABLE()     (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE()    (T2CONbits.TMR2ON = 0)

#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)      ( T2CONbits.TOUTPS = _POSTSCALER_ )

#define TIMER2_PRESCALER_SELECT(_PRESCALER_)        ( T2CONbits.T2CKPS = _PRESCALER_ )

/*----------User Data types--------*/
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
typedef void (*timer2_interruptHandler_t)(void);
#endif

typedef struct{
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    timer2_interruptHandler_t InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg interrupt_pri;
#endif
#endif
    uint8_t Preloaded_val;
    uint8_t PostScaler  :4;
    uint8_t PreScaler   :2;
    uint8_t reserved    :2;
    
}timer2_t;
/*---------Interfaces--------------*/


Std_ReturnType timer2_init(const timer2_t* _timer);
Std_ReturnType timer2_deinit(const timer2_t* _timer);
Std_ReturnType timer2_write_val(const timer2_t* _timer , uint8_t val);
Std_ReturnType timer2_read_val(const timer2_t* _timer , uint8_t* _retVal);

#endif	/* HAL_TIMER2_H */

