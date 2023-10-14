/* 
 * File:   hal_timer0.h
 * Author: yossef
 *
 * Created on July 11, 2023, 12:56 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*-------------Includes------------*/
#include "../mcal_std_types.h"
#include "../../../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../GPIO/HAL_GPIO.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"

/*---------------Macros------------*/

#define TIMER0_PRESCALER_ENABLE_CFG     1
#define TIMER0_PRESCALER_DISABLE_CFG    0

#define TIMER0_RISING_EDGE_CFG          0
#define TIMER0_FALING_EDGE_CFG          1

#define TIMER0_COUNTER_MODE_CFG         1
#define TIMER0_TIMER_MODE_CFG           0

#define TIMER0_8BIT_MODE_CFG             1
#define TIMER0_16BIT_MODE_CFG            0
/*--------------Func Macro---------*/

#define TIMER0_PRESCALER_ENABLE()   (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA = 1)
#define TIMER0_PRESCALER_SELECT(PRESCALER)  (T0CONbits.T0PS = PRESCALER)


#define TIMER0_ENABLE()              (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()              (T0CONbits.TMR0ON = 0)

#define TIMER0_SOURCE_EDGE_SELECT(SOURCE_EDGE)  (T0CONbits.T0SE = SOURCE_EDGE)

#define TIMER0_TIMER_MODE_ENABLE()      (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()    (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REG_ENABLE()        (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REG_ENABLE()       (T0CONbits.T08BIT = 0)

/*----------User Data types--------*/
typedef void (*timer0_interrupt_callBack_t)(void);

typedef enum{
            TIMER0_PRESCALER_DIV_2 = 0,
            TIMER0_PRESCALER_DIV_4,
            TIMER0_PRESCALER_DIV_8,
            TIMER0_PRESCALER_DIV_16,
            TIMER0_PRESCALER_DIV_32,
            TIMER0_PRESCALER_DIV_64,
            TIMER0_PRESCALER_DIV_128,
            TIMER0_PRESCALER_DIV_256,
}timer0_prescaler_t;


typedef struct{
    uint16_t Preloaded_val;
    uint8_t prescaler_stat : 1;
    timer0_prescaler_t prescaler_val;
    uint8_t timer0_mode : 1 ;
    uint8_t counter_source_edge : 1;
    uint8_t timer0_register_size : 1;
    uint8_t reserved :4;
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    timer0_interrupt_callBack_t _CallBack_func;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg interrupt_pri;
#endif
#endif
}timer0_t;


/*---------Interfaces--------------*/
Std_ReturnType timer0_init(const timer0_t* _timer);
Std_ReturnType timer0_deinit(const timer0_t* _timer);
Std_ReturnType timer0_write_val(const timer0_t* _timer , uint16_t val);
Std_ReturnType timer0_read_val(const timer0_t* _timer , uint16_t* _ret);

#endif	/* HAL_TIMER0_H */

