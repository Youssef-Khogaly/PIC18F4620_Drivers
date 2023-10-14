/* 
 * File:   hal_timer2.c
 * Author: yossef
 *
 * Created on July 14, 2023, 3:00 AM
 */
#include "hal_timer2.h"



#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline void timer2_interrupt_conf (const timer2_t* _timer);
static timer2_interruptHandler_t _timer2_interruptHandler = NULL;
#endif

static volatile uint8_t timer2_preloaded = 0;


Std_ReturnType timer2_init(const timer2_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
    }
  else
    {
      TIMER2_DISABLE();
      TIMER2_PRESCALER_SELECT(_timer->PreScaler);
      TIMER2_POSTSCALER_SELECT(_timer->PostScaler);
      timer2_preloaded = _timer->Preloaded_val;
      TMR2 = timer2_preloaded;
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      timer2_interrupt_conf(_timer);
#endif
      TIMER2_ENABLE();
    }
  return ret;
}
Std_ReturnType timer2_deinit(const timer2_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
    }
  else
    {
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      TIMER2_INTERRUPT_DISABLE();
#endif
      TIMER2_DISABLE();
    }
  return ret; 
}
Std_ReturnType timer2_write_val(const timer2_t* _timer , uint8_t val){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
    }
  else
    {
      TMR2 = val;
    }
  return ret;  
}
Std_ReturnType timer2_read_val(const timer2_t* _timer , uint8_t* _retVal){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer || NULL == _retVal)
    {
      ret = E_NOT;
    }
  else
    {
      *_retVal = TMR2;
    }
  return ret; 
}




static inline void timer2_interrupt_conf (const timer2_t* _timer)
{
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  TIMER2_INTERRUPT_DISABLE();
  TIMER2_INTERRUPT_CLEAR_FLAG();
  _timer2_interruptHandler = _timer->InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
  
      INTERRUPT_PRIORITY_FEATURE_ENABLE();
      INTERRUPT_HIGH_PRIORITY_ENABLE();
      INTERRUPT_LOW_PRIORITY_ENABLE();
      
      switch(_timer->interrupt_pri)
        {
        case INTERRUPT_HIGH_PRIORITY:
          TIMER2_INTERRUPT_PRI_HIGH();
          break;
        case INTERRUPT_LOW_PRIORITY:
          TIMER2_INTERRUPT_PRI_LOW();
          break;
        }
      
#else
    INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();  
    INTERRUPT_ENABLE_UNMASKED();   
#endif 
    TIMER2_INTERRUPT_ENABLE();  
#endif
      return;
}



#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TMR2_ISR(void)
{
  TIMER2_INTERRUPT_CLEAR_FLAG();
  TMR2 = timer2_preloaded;
  if(NULL != _timer2_interruptHandler)
    {
      _timer2_interruptHandler();
    }
  else{
      /*nothing*/
    }
  return;
}
#endif