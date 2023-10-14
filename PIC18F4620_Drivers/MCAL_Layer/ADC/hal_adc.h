/* 
 * File:   hal_adc.h
 * Author: yossef
 *
 * Created on May 4, 2023, 3:48 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/*-------Includes---------*/
#include "hal_adc_cfg.h"
#include "../mcal_std_types.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
#include"../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../GPIO/HAL_GPIO.h"
/*-----Macro----*/

/*
 * @brief ADC Channels select
 */
#define ADC_CHANNEL_0    0
#define ADC_CHANNEL_1    1
#define ADC_CHANNEL_2    2
#define ADC_CHANNEL_3    3
#define ADC_CHANNEL_4    4
#define ADC_CHANNEL_5    5
#define ADC_CHANNEL_6    6
#define ADC_CHANNEL_7    7
#define ADC_CHANNEL_8    8
#define ADC_CHANNEL_9    9
#define ADC_CHANNEL_10   10
#define ADC_CHANNEL_11   11
#define ADC_CHANNEL_12   12
/***************************/

#define ADC_CONV_INPROGESS      1
#define ADC_DONE                0

#define ADC_RESULT_RIGHT        1
#define ADC_RESULT_LEFT         0

#define ADC_VOLTAGE_REF_ENABLE      1
#define ADC_VOLTAGE_REF_DISABLE     0

/*-----Macro Functions-------*/

/*
 * @brief select the adc channel  
 * example -> ADC_SELECT_CHANNEL(ADC_CHANNEL_0)
 */
#define ADC_SELECT_CHANNEL(ADC_CHANNEL)     (ADCON0bits.CHS = ADC_CHANNEL)

#define ADC_START_CONV()        (ADCON0bits.GO = ADC_CONV_INPROGESS)

/*
   @brief  Check ADC Status 
 * @ret ADC_CONV_INPROGESS -> 1
 *      ADC_DONE - > 0
 */
#define ADC_CHECK_STATUS()      (ADCON0bits.GODONE)

#define ADC_FEATURE_ENABLE()    (ADCON0bits.ADON = 1)
#define ADC_FEATURE_DISABLE()   (ADCON0bits.ADON = 0)

/*
 *@brief select AN2 and AN3 as a Voltage ref for the adc
 * 
 */

#define ADC_VREF_ENABLE()       do{\
                                 ADCON1bits.VCFG0 = 1;\
                                 ADCON1bits.VCFG1 = 1;\
                                }while(0)

/*
 *@brief select VDD and VSS as a Voltage ref for the adc
 * 
 */                                     
#define ADC_VREF_DISABLE()      do{\
                                 ADCON1bits.VCFG0 = 0;\
                                 ADCON1bits.VCFG1 = 0;\
                                }while(0)

/*
 * @brief Select Port configration for ADC
 * @note ->  if u chose AN1 to be analog then AN0 AND AN1 are analog
 *          example ADC_AN2_ANALOG() - > this mean  AN0 and AN1 and AN2 are analog 
 *          and AN3 to AN12 are Digital
 */
#define ADC_ALL_ANALOG()    (ADCON1bits.PCFG = 0x00)
#define ADC_ALL_DIGITAL()   (ADCON1bits.PCFG = 0x0F)
                                     
#define ADC_AN0_ANALOG()    (ADCON1bits.PCFG = 0x0E)
#define ADC_AN1_ANALOG()    (ADCON1bits.PCFG = 0x0D)
#define ADC_AN2_ANALOG()    (ADCON1bits.PCFG = 0x0C)
#define ADC_AN3_ANALOG()    (ADCON1bits.PCFG = 0x0B)
#define ADC_AN4_ANALOG()    (ADCON1bits.PCFG = 0x0A)
#define ADC_AN5_ANALOG()    (ADCON1bits.PCFG = 0x09)
#define ADC_AN6_ANALOG()    (ADCON1bits.PCFG = 0x08)
#define ADC_AN7_ANALOG()    (ADCON1bits.PCFG = 0x07)
#define ADC_AN8_ANALOG()    (ADCON1bits.PCFG = 0x06)
#define ADC_AN9_ANALOG()    (ADCON1bits.PCFG = 0x05)
#define ADC_AN10_ANALOG()    (ADCON1bits.PCFG = 0x04)
#define ADC_AN11_ANALOG()    (ADCON1bits.PCFG = 0x03)
#define ADC_AN12_ANALOG()    (ADCON1bits.PCFG = 0x02)
                                    
#define ADC_RESULT_FORMAT_SELECT(_FORMAT)       (ADCON2bits.ADFM = _FORMAT)

                                    
#define ADC_CONV_CLOCK_SELECT(_CONF)    (ADCON2bits.ADCS = _CONF)
                                    
#define ADC_ACQUISITION_TIME_SELECT(_TIME)  (ADCON2bits.ACQT = _TIME)                                    
/*-----user data types------*/

/*pointer to ADC call back function*/                                    
typedef void(*ADC_INTERRUPT_HANDLER_t)(void);

                                
                                
                                
/*
 *  @brief A/D Acquisition Time select
 *  @note Acquisition Time is the time require for The ADC to capture input voltage during sampling
 */
typedef enum{
    ADC_0_TDA = 0,
            ADC_2_TDA,
            ADC_4_TDA,
            ADC_6_TDA,
            ADC_8_TDA,
            ADC_12_TDA,
            ADC_16_TDA,
            ADC_20_TDA,
}adc_acquisition_time_t;

/*
 *  @brief A/D Conversion clock 
 * 
 *  @note if A/D FRC clock  is selected  a delay of one  intsruction cycle 
 *        is added before A/D clock start 
 */
typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
            ADC_CONVERSION_CLOCK_FOSC_DIV_8,
            ADC_CONVERSION_CLOCK_FOSC_DIV_32,
            ADC_CONVERSION_CLOCK_FRC,
            ADC_CONVERSION_CLOCK_FOSC_DIV_4,
            ADC_CONVERSION_CLOCK_FOSC_DIV_16,
            ADC_CONVERSION_CLOCK_FOSC_DIV_64,
            
}adc_conversion_clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    ADC_INTERRUPT_HANDLER_t adc_callBack_func;
    interrupt_priority_cfg priority;
#endif
    adc_conversion_clock_t conversion_clock; /* @ref adc_conversion_clock_t */
    adc_acquisition_time_t acquisition_time; /* @ref adc_acquisition_time_t */
    uint8_t default_channel : 4;
    uint8_t Voltage_ref : 1;
    uint8_t result_format : 1 ;
    uint8_t adc_reserved : 2;
}adc_conf_t;

typedef uint16_t   adc_result_t;
/*--------Interfaces prototypes----*/

Std_ReturnType adc_init(const adc_conf_t* _adc);
Std_ReturnType adc_Deinit(const adc_conf_t* _adc);
Std_ReturnType adc_select_channel(const adc_conf_t* _adc , uint8_t channel);
Std_ReturnType adc_start_conversion(const adc_conf_t* _adc);
Std_ReturnType adc_IsConversionDone(const adc_conf_t* _adc , uint8_t* conv_stat);
Std_ReturnType adc_GetResult(const adc_conf_t* _adc ,adc_result_t* ConvResult);
Std_ReturnType adc_GetConversion_Blocking(const adc_conf_t* _adc ,adc_result_t* ConvResult , uint8_t adc_channel);
#if ADC_INTERRUPT_FEATURE ==  INTERRUPT_FEATURE_ENABLE
Std_ReturnType adc_StartConversion_Interrupt(const adc_conf_t* _adc , uint8_t adc_channel);
#endif










#endif	/* HAL_ADC_H */

