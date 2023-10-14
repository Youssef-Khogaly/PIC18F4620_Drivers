/* 
 * File:   hal_ccp1.h
 * Author: yossef
 *
 * Created on July 20, 2023, 3:51 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*-------------Includes------------*/
#include "hal_ccp_cfg.h"
#include "../../../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
#include "../GPIO/HAL_GPIO.h"

/*---------------Macros------------*/
#define CCP_DISABLE                                    ((uint8_t)0x00)

/*------ Capture Mode------*/
#define CCP_CAPTURE_MODE_FALLING_EDGE                  ((uint8_t)0X04)
#define CCP_CAPTURE_MODE_RISING_EDGE                   ((uint8_t)0X05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE                 ((uint8_t)0X06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE                ((uint8_t)0X07)

#define CCP_CAPTURE_OCCURED                            ((uint8_t)0x01)     
#define CCP_CAPTURE_NOT_OCCURED                        ((uint8_t)0x00)
/*----- Compare Mode------*/
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH               ((uint8_t)0X02)
#define CCP_COMPARE_MODE_SET_HIGH                      ((uint8_t)0X08)
#define CCP_COMPARE_MODE_SET_LOW                       ((uint8_t)0X09)
#define CCP_COMPARE_MODE_GEN_INTERRUPT                 ((uint8_t)0X0A)
#define CCP_COMPARE_MODE_GEN_EVENT                     ((uint8_t)0X0B)

#define CCP_COMPARE_OCCURED                            ((uint8_t)0x01)     
#define CCP_COMPARE_NOT_OCCURED                        ((uint8_t)0x00)


            //prescaler
#define CCP_TIMER2_PRESCALER_DIV_1_CFG       1
#define CCP_TIMER2_PRESCALER_DIV_4_CFG       4
#define CCP_TIMER2_PRESCALER_DIV_16_CFG      16

            //postscaler
#define CCP_TIMER2_POSTSCALER_DIV_1_CFG       1
#define CCP_TIMER2_POSTSCALER_DIV_2_CFG       2
#define CCP_TIMER2_POSTSCALER_DIV_3_CFG       3
#define CCP_TIMER2_POSTSCALER_DIV_4_CFG       4
#define CCP_TIMER2_POSTSCALER_DIV_5_CFG       5
#define CCP_TIMER2_POSTSCALER_DIV_6_CFG       6
#define CCP_TIMER2_POSTSCALER_DIV_7_CFG       7
#define CCP_TIMER2_POSTSCALER_DIV_8_CFG       8
#define CCP_TIMER2_POSTSCALER_DIV_9_CFG       9
#define CCP_TIMER2_POSTSCALER_DIV_10_CFG      10
#define CCP_TIMER2_POSTSCALER_DIV_11_CFG      11
#define CCP_TIMER2_POSTSCALER_DIV_12_CFG      12
#define CCP_TIMER2_POSTSCALER_DIV_13_CFG      13
#define CCP_TIMER2_POSTSCALER_DIV_14_CFG      14
#define CCP_TIMER2_POSTSCALER_DIV_15_CFG      15
#define CCP_TIMER2_POSTSCALER_DIV_16_CFG      16


/* PWM Mode*/
#define CCP_PWM_MODE                                   ((uint8_t)0X0C)



/*--------------Func Macro---------*/

#define CCP1_MODE_SELECT(_MODE)     (CCP1CONbits.CCP1M = _MODE)
#define CCP2_MODE_SELECT(_MODE)     (CCP2CONbits.CCP2M = _MODE)

/*----------User Data types--------*/
typedef enum{
    CCP_CAPTURE_MODE_SELECT,
            CCP_COMPARE_MODE_SELECT,
            CCP_PWM_MODE_SELECT
}ccp_mode_t;

typedef enum {
    ccp1_inist,
            ccp2_inist
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3    
}ccp_capture_timer_t;

typedef void(*CCP_InterruptHandler_t)(void);


typedef union{
    struct{
        uint8_t ccpr_low;
        uint8_t ccpr_high;  
    };
    struct{
        uint16_t ccpr_16Bit;
    };
}ccp_ccpr_reg_t;

typedef struct {
    CCP_InterruptHandler_t CCP_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg interrupt_pri;
#endif
    
#if (CCP_CFG_PWM_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED) || (CCP_CFG_PWM_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED)
    uint32_t pwm_freq;
    uint8_t timer2_PostScaler  :4;
    uint8_t timer2_PreScaler   :2;
#endif

#if (CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED) || (CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED) || (CCP_CFG_COMPARE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED) || (CCP_CFG_COMPARE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED)
    ccp_capture_timer_t ccp_capture_timer;
#endif
    ccp_inst_t ccp_inist;
    pinConfig_t ccp_pin;
    ccp_mode_t ccp_mode;
    uint8_t ccp_ModeVariant : 4;
    uint8_t reserved : 4;
}ccp_t;

/*---------Interfaces--------------*/

Std_ReturnType ccp_init(const ccp_t* _ccpObj);
        
Std_ReturnType ccp_Deinit(const ccp_t* _ccpObj);

#if CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED
Std_ReturnType ccp_check_CaptureDataReady(const ccp_t* _ccpObj , uint8_t* capture_stat);
Std_ReturnType ccp_CaptureMode_ReadVal(const ccp_t* _ccpObj , uint16_t* capture_val);

#endif

#if CCP_CFG_COMPARE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_COMPARE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED
Std_ReturnType ccp_check_Compare_Ocuured(const ccp_t* _ccpObj , uint8_t* compare_stat);
Std_ReturnType ccp_CompareMode_SetVal(const ccp_t* _ccpObj , uint16_t compare_Val);

#endif

#if CCP_CFG_PWM_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_PWM_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED
Std_ReturnType ccp_PWM_SetDuty(const ccp_t* _ccpObj , const uint8_t _duty);
Std_ReturnType ccp_PWM_Start(const ccp_t* _ccpObj);
Std_ReturnType ccp_PWM_Stop(const ccp_t* _ccpObj);
#endif


#endif	/* HAL_CCP1_H */

