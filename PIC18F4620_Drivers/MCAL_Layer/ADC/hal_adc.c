
/* 
 * File:   hal_adc.c
 * Author: yossef
 *
 * Created on May 4, 2023, 3:48 AM
 */
#include "hal_adc.h"

/*Global Variable*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static ADC_INTERRUPT_HANDLER_t ADC_INTERRUPT_HANDLER = NULL;
#endif
/*************/
/*Helper function*/

static inline void adc_input_channel_port_conf(uint8_t channel);
/************/


/**
 * @brief  Initialize the ADC
 * @Precondition non
 * @param _adc
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */

Std_ReturnType adc_init(const adc_conf_t* _adc){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc)){
      return ret;
    }
  else{
      ret = E_OK;
      /*Disable A/D*/
      ADC_FEATURE_DISABLE();
      /*configure The acquisition time*/
      ADC_ACQUISITION_TIME_SELECT(_adc->acquisition_time);
      /*configure conversion clock*/
      ADC_CONV_CLOCK_SELECT(_adc->conversion_clock);
      /*configure adc default channel*/
      ADC_SELECT_CHANNEL(_adc->default_channel);
      adc_input_channel_port_conf (_adc->default_channel);
      /*configure the interrupt*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      ADC_INTERRUPT_DISABLE();
      
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
      INTERRUPT_PRIORITY_FEATURE_ENABLE();
      INTERRUPT_HIGH_PRIORITY_ENABLE();
      INTERRUPT_LOW_PRIORITY_ENABLE();
      switch(_adc->priority){
                case INTERRUPT_HIGH_PRIORITY:
                  ADC_INTERRUPT_PRI_HIGH();
  
                  break;
                case INTERRUPT_LOW_PRIORITY:
                    ADC_INTERRUPT_PRI_LOW();
                  break;
                default : ret = E_NOT;
        }
#else
    INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
    INTERRUPT_ENABLE_UNMASKED();
#endif
      ADC_INTERRUPT_HANDLER = _adc->adc_callBack_func;
      ADC_INTERRUPT_CLEAR_FLAG();
      ADC_INTERRUPT_ENABLE();

#endif

      
      /*configure result format*/
       ADC_RESULT_FORMAT_SELECT(_adc->result_format);
      /*configure the voltage ref*/
       switch(_adc->Voltage_ref){
         case ADC_VOLTAGE_REF_ENABLE:
           ADC_VREF_ENABLE();
           break;
           case ADC_VOLTAGE_REF_DISABLE:
           ADC_VREF_DISABLE();
           break;
         default: ret &= E_NOT;
         }
      /*Enable A/D*/
      ADC_FEATURE_ENABLE(); 
      ret &= E_OK;
    }
  return ret;
}
/*
 * 
 * @param _adc
 *
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */
Std_ReturnType adc_Deinit(const adc_conf_t* _adc){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc)){
      return ret;
    }
  else{
      /*Disable A/D*/
      ADC_FEATURE_DISABLE();
      /*Disable A/D the interrupt*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      ADC_INTERRUPT_DISABLE();
#endif
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      
#endif
      ret = E_OK;
    }
  return ret; 
}
/**
 * 
 * @param _adc const pointer to @ref adc_conf_t
 * @param channel - > A/D channel 
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */
Std_ReturnType adc_select_channel(const adc_conf_t* _adc , uint8_t channel){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc)){
      return ret;
    }
  else{
      
      ADC_SELECT_CHANNEL(channel);
      adc_input_channel_port_conf(channel);
      ret = E_OK;
    }
  return ret;  
}
/**
 * 
 * @param _adc const pointer to @ref adc_conf_t
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */
Std_ReturnType adc_start_conversion(const adc_conf_t* _adc){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc) || ( ADC_CONV_INPROGESS == ADC_CHECK_STATUS())){
      return ret;
    }
  else{
      ADC_START_CONV();
      ret = E_OK;
    }
  return ret;  
}
/**
 * 
 * @param _adc const pointer to @ref adc_conf_t
 * @param conv_stat pointer to uint8_t to return value
 *        ADC_CONV_INPROGESS -> 1 conversion in progress
 *        ADC_DONE -> 0 conversion done A/D in idle stat
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */
Std_ReturnType adc_IsConversionDone(const adc_conf_t* _adc , uint8_t* conv_stat){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc) || (NULL == conv_stat)){
      return ret;
    }
  else{
      *conv_stat  = (uint8_t)(ADC_CHECK_STATUS());
      
      ret = E_OK;
    }
  return ret;  
}
/**
 * 
 * @param _adc const pointer to @ref adc_conf_t
 * @param ConvResult pointer to @ref adc_result_t
 *        to return conversion result
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */
Std_ReturnType adc_GetResult(const adc_conf_t* _adc ,adc_result_t* ConvResult){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc) || (NULL == ConvResult)){
      return ret;
    }
  else{
      switch(_adc->result_format){
        case ADC_RESULT_RIGHT:
          *ConvResult = (adc_result_t)(ADRESL & 0xFF);
          *ConvResult += (adc_result_t)((ADRESH << 8) & 0x300 );
          ret = E_OK;
          break;
        case ADC_RESULT_LEFT:
          *ConvResult = (adc_result_t)((ADRESL>>6) & 0x03);
          *ConvResult += ((adc_result_t)((ADRESH << 2)) & 0x3FC);
          ret = E_OK;
          break;
        default: ret = E_NOT;
    }
      ret &= E_OK;
    }
  return ret;    
}
/**
 * @brief this function select adc channel and start A/D conversion and return result in pointer
 * @note This function blocking the code untill A/D end conversion
 * @param _adc const pointer to @ref adc_conf_t
 * @param ConvResult pointer to @ref adc_result_t
 *        to return conversion result
 * @param channel - > A/D channel 
 * @return @ref Std_ReturnType
 *         E_OK 1 -> function done successfully
 *         E_NOT 0 - > function fail
 */
Std_ReturnType adc_GetConversion_Blocking(const adc_conf_t* _adc ,adc_result_t* ConvResult , uint8_t adc_channel){
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc) || (NULL == ConvResult)){
      return ret;
    }
  else{
      ret = adc_select_channel(_adc ,adc_channel);
      ret &= adc_start_conversion(_adc);
      // wait ADC to end conv
      while(ADC_CONV_INPROGESS == ADC_CHECK_STATUS());
      ret &= adc_GetResult(_adc , ConvResult);
    }
  return ret;     
}
#if ADC_INTERRUPT_FEATURE ==  INTERRUPT_FEATURE_ENABLE
Std_ReturnType adc_StartConversion_Interrupt(const adc_conf_t* _adc , uint8_t adc_channel)
{
  Std_ReturnType ret = E_NOT;
  if((NULL == _adc)){
      return ret;
    }
  else
    {
      ret = adc_select_channel(_adc ,adc_channel);
      ret &= adc_start_conversion(_adc);      
    }
  return ret;
}
#endif
/******ADC ISR FUNCTION*/
#if ADC_INTERRUPT_FEATURE ==  INTERRUPT_FEATURE_ENABLE
void ADC_ISR(void){
  ADC_INTERRUPT_CLEAR_FLAG();
  if(NULL != ADC_INTERRUPT_HANDLER)
      ADC_INTERRUPT_HANDLER();
  else
    {/*NoThing*/}
  return;
}
#endif
/*--------------*/

static inline void adc_input_channel_port_conf(uint8_t channel)
{
      switch(channel){
        case ADC_CHANNEL_0:
          BIT_SET(TRISA , _TRISA_RA0_POSN);
          ADC_AN0_ANALOG();
          break;
        case ADC_CHANNEL_1:
          BIT_SET(TRISA , _TRISA_RA1_POSN);
          ADC_AN1_ANALOG();
          break;
        case ADC_CHANNEL_2:
          BIT_SET(TRISA , _TRISA_RA2_POSN);
          ADC_AN2_ANALOG();
          break;
        case ADC_CHANNEL_3:
          BIT_SET(TRISA , _TRISA_RA3_POSN);
          ADC_AN3_ANALOG();
          break;
        case ADC_CHANNEL_4:
          BIT_SET(TRISA , _TRISA_RA5_POSN);
          ADC_AN4_ANALOG();
          break;
        case ADC_CHANNEL_5:
          BIT_SET(TRISE , _TRISE_RE0_POSN);
          ADC_AN5_ANALOG();
          break;
        case ADC_CHANNEL_6:
          BIT_SET(TRISE , _TRISE_RE1_POSN);
          ADC_AN6_ANALOG();
          break;
          BIT_SET(TRISE , _TRISE_RE2_POSN);
        case ADC_CHANNEL_7:
          BIT_SET(TRISE , _TRISE_RE2_POSN);
          ADC_AN7_ANALOG();
          break;
        case ADC_CHANNEL_8:
          BIT_SET(TRISB , _TRISB_RB2_POSN);
          ADC_AN8_ANALOG();
          break;
        case ADC_CHANNEL_9:
          BIT_SET(TRISB , _TRISB_RB3_POSN);
          ADC_AN9_ANALOG();
          break;
        case ADC_CHANNEL_10:
          BIT_SET(TRISB , _TRISB_RB1_POSN);
          ADC_AN10_ANALOG();
          break;
        case ADC_CHANNEL_11:
          BIT_SET(TRISB , _TRISB_RB4_POSN);
          ADC_AN11_ANALOG();
          break;
        case ADC_CHANNEL_12:
          BIT_SET(TRISB , _TRISB_RB0_POSN);
          ADC_AN12_ANALOG();
          break;
        default: /* no thing */;
        } 
      return;
}
