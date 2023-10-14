/* 
 * File:   hal_timer1.h
 * Author: yossef
 *
 * Created on July 12, 2023, 5:14 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/*-------------Includes------------*/
#include "../mcal_std_types.h"
#include "../../../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../GPIO/HAL_GPIO.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
/*---------------Macros------------*/
#define TIMER1_COUNTER_MODE_CFG                 1
#define TIMER1_TIMER_MODE_CFG                   0

#define TIMER1_RW_16BIT_MODE_CFG                1
#define TIMER1_RW_8BIT_MODE_CFG                 0

#define TIMER1_OSCI_ENABLE_CFG                  1
#define TIMER1_OSCI_DISABLE_CFG                 0

#define TIMER1_SYNC_COUNTER_MODE_CFG            0
#define TIMER1_ASYNC_COUNTER_MODE_CFG           1

#define TIMER1_PRESCALER_DIV_1_CFG              0
#define TIMER1_PRESCALER_DIV_2_CFG              1
#define TIMER1_PRESCALER_DIV_4_CFG              2
#define TIMER1_PRESCALER_DIV_8_CFG              3
/*--------------Func Macro---------*/
#define TIMER1_ENABLE()                          (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()                         (T1CONbits.TMR1ON = 0)

#define TIMER1_PRESCALER_SELECT(PRESCALER_VAL)   (T1CONbits.T1CKPS = PRESCALER_VAL)

#define TIMER1_MODE_SELECT(TIMER_OR_COUNTER)     (T1CONbits.TMR1CS = TIMER_OR_COUNTER)

#define TIMER1_RW_MODE_SELECT(_8BIT_16BIT)       (T1CONbits.RD16 = _8BIT_16BIT)

#define TIMER1_OSCI_ENABLE()                      (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCI_DISABLE()                     (T1CONbits.T1OSCEN = 0)

#define TIMER1_SYNC_COUNTER_ENABLE()                (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNC_COUNTER_ENABLE()               (T1CONbits.T1SYNC = 1)

#define TIMER1_SYSTEM_CLK_STAT                      (T1CONbits.T1OSCEN)

/*----------User Data types--------*/
/* pointer to function data type*/

typedef void (*timer1_interrupt_callBack_t)(void);

typedef struct {
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    timer1_interrupt_callBack_t _CallBack_func;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg interrupt_pri;
#endif
#endif
    uint16_t timer1_preloaded_val;
    uint8_t timer1_prescaler        :2;
    uint8_t timer1_mode             :1;
    uint8_t timer1_counter_mode     :1;
    uint8_t timer1_osc_mode         :1;
    uint8_t reg_rw_mode             :1;
    uint8_t reserved                :2;
}timer1_t;

/*---------Interfaces--------------*/

Std_ReturnType timer1_init(const timer1_t* _timer);
Std_ReturnType timer1_deinit(const timer1_t* _timer);
Std_ReturnType timer1_write_val(const timer1_t* _timer , uint16_t val);
Std_ReturnType timer1_read_val(const timer1_t* _timer , uint16_t* _retVal);


#endif	/* HAL_TIMER1_H */

