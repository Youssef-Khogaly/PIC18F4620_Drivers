/* 
 * File:   hal_timer0.c
 * Author: yossef
 *
 * Created on July 11, 2023, 12:56 AM
 */
#include "hal_timer0.h"
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static timer0_interrupt_callBack_t _timer0_interrupt_handler = NULL;

#endif
static volatile uint16_t timer0_preload = 0;

Std_ReturnType timer0_init(const timer0_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
      return ret;
    }
  else
    {
      TIMER0_DISABLE();
      
      switch(_timer->timer0_register_size)
        {
        case TIMER0_8BIT_MODE_CFG:
          TIMER0_8BIT_REG_ENABLE();
          break;
        case TIMER0_16BIT_MODE_CFG:
          TIMER0_16BIT_REG_ENABLE();
          break;
        default: ret = E_NOT;
        }
      
      switch(_timer->timer0_mode)
      {
        case TIMER0_COUNTER_MODE_CFG:
          TIMER0_COUNTER_MODE_ENABLE();
          TIMER0_SOURCE_EDGE_SELECT(_timer->counter_source_edge);
          break;
          
        case TIMER0_TIMER_MODE_CFG:
          TIMER0_TIMER_MODE_ENABLE();
          break;
          
        default: ret = E_NOT;
      }
      
      switch(_timer->prescaler_stat)
        {
        case TIMER0_PRESCALER_DISABLE_CFG:
          TIMER0_PRESCALER_DISABLE();
          break;
        case TIMER0_PRESCALER_ENABLE_CFG:
          TIMER0_PRESCALER_SELECT(_timer->prescaler_val);
          TIMER0_PRESCALER_ENABLE();
          break;
        default: ret = E_NOT;
        }
      
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      TIMER0_INTERRUPT_DISABLE();
      TIMER0_INTERRUPT_CLEAR_FLAG();
      _timer0_interrupt_handler = _timer->_CallBack_func;
      
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
      INTERRUPT_PRIORITY_FEATURE_ENABLE();
      INTERRUPT_HIGH_PRIORITY_ENABLE();
      INTERRUPT_LOW_PRIORITY_ENABLE();
      
      switch(_timer->interrupt_pri)
        {
        case INTERRUPT_HIGH_PRIORITY:
          TIMER0_INTERRUPT_PRI_HIGH();
          break;
        case INTERRUPT_LOW_PRIORITY:
          TIMER0_INTERRUPT_PRI_LOW();
          break;
        default: ret = E_NOT;
        }     
#else
    INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();  
    INTERRUPT_ENABLE_UNMASKED();
#endif
    
    TIMER0_INTERRUPT_ENABLE();

#endif
      
        TMR0H = (uint8_t)((_timer->Preloaded_val)>>8);
        TMR0L = (uint8_t)(_timer->Preloaded_val & 0xFF);
        timer0_preload = _timer->Preloaded_val;
        
        TIMER0_ENABLE();
    }
  
  return ret;
}

Std_ReturnType timer0_deinit(const timer0_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
      return ret;
    }
  else
    {
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      TIMER0_INTERRUPT_DISABLE();
#endif
      TIMER0_DISABLE();
    }
  return ret;  
}

Std_ReturnType timer0_write_val(const timer0_t* _timer , uint16_t val){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
      return ret;
    }
  else
    {
        TMR0H = (uint8_t)((val)>>8);
        TMR0L = (uint8_t)(val & 0xFF);      
    }
  return ret;  
}
Std_ReturnType timer0_read_val(const timer0_t* _timer , uint16_t* _ret){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer || NULL == _ret)
    {
      ret = E_NOT;
      return ret;
    }
  else
    {
      *_ret = TMR0L;
      *_ret += ((uint16_t)(TMR0H << 8)& 0xFF00);
    }
  return ret;  
}

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TMR0_ISR(void)
{
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = (uint8_t)((timer0_preload)>>8);
    TMR0L = (uint8_t)(timer0_preload & 0xFF);  
  if(_timer0_interrupt_handler)
    {
      _timer0_interrupt_handler();
    }
  else
    {/*Nothing*/}
  return;
}
#endif