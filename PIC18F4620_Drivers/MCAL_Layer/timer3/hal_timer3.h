/* 
 * File:   hal_timer3.h
 * Author: yossef
 *
 * Created on July 14, 2023, 3:00 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*-------------Includes------------*/
#include "../mcal_std_types.h"
#include "../../../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../GPIO/HAL_GPIO.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
/*---------------Macros------------*/
#define TIMER3_ASYNC_COUNTER_MODE_CFG                1
#define TIMER3_SYNC_COUNTER_MODE_CFG                 2
#define TIMER3_TIMER_MODE_CFG                        0

#define TIMER3_RW_16BIT_MODE_CFG                    1
#define TIMER3_RW_8BIT_MODE_CFG                     0

#define TIMER3_PRESCALER_DIV_1_CFG                  0
#define TIMER3_PRESCALER_DIV_2_CFG                  1
#define TIMER3_PRESCALER_DIV_4_CFG                  2
#define TIMER3_PRESCALER_DIV_8_CFG                  3

/*--------------Func Macro---------*/
#define TIMER3_ENABLE()                             (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()                            (T3CONbits.TMR3ON = 0)

#define TIMER3_PRESCALER_SELECT(PRESCALER_VAL)      (T3CONbits.T3CKPS = PRESCALER_VAL)

#define TIMER3_MODE_SELECT(TIMER_OR_COUNTER)        (T3CONbits.TMR3CS = TIMER_OR_COUNTER)

#define TIMER3_RW_MODE_SELECT(_8BIT_16BIT)          (T3CONbits.RD16 = _8BIT_16BIT)

#define TIMER3_SYNC_COUNTER_ENABLE()                (T3CONbits.T3SYNC = 0)
#define TIMER3_ASYNC_COUNTER_ENABLE()               (T3CONbits.T3SYNC = 1)


/*----------User Data types--------*/
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
typedef void (*timer3_interruptHandler_t)(void);
#endif

typedef struct {
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    timer3_interruptHandler_t timer3_interruptHandler;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg interrupt_pri;
#endif
#endif
    uint16_t timer3_preloaded_val;
    uint8_t timer3_prescaler        :2;
    uint8_t timer3_mode             :2;
    uint8_t reg_rw_mode             :1;
    uint8_t reserved                :3;
}timer3_t;


/*---------Interfaces--------------*/

/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType timer3_init(const timer3_t* _timer);
Std_ReturnType timer3_deinit(const timer3_t* _timer);
Std_ReturnType timer3_write_val(const timer3_t* _timer , uint16_t val);
Std_ReturnType timer3_read_val(const timer3_t* _timer , uint16_t* _retVal);

#endif	/* HAL_TIMER3_H */

