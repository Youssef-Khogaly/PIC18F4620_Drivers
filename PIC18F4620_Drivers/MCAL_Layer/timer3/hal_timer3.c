/* 
 * File:   hal_timer3.c
 * Author: yossef
 *
 * Created on July 14, 2023, 3:00 AM
 */
#include"hal_timer3.h"

static uint16_t timer3_preloaded = 0;
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline void timer3_interruptInit(const timer3_t* _timer);
timer3_interruptHandler_t timer3_Interrupt_callBack = NULL;
#endif
static inline void timer3_counterMode_select(const timer3_t* _timer);



Std_ReturnType timer3_init(const timer3_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
    }
  else
    {
      TIMER3_DISABLE();
      
      TIMER3_RW_MODE_SELECT(_timer->reg_rw_mode);
      
      timer3_preloaded = _timer->timer3_preloaded_val;
       TMR3H = (uint8_t)( (timer3_preloaded>>8) & 0xFF );
       TMR3L = (uint8_t)(timer3_preloaded & 0xFF);
       TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler);
     
       timer3_counterMode_select(_timer);
       
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE       
       timer3_interruptInit(_timer);
#endif       
     
       TIMER3_ENABLE();
    }
  return ret;
}
Std_ReturnType timer3_deinit(const timer3_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
    }
  else
    {
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE       
      TIMER3_INTERRUPT_DISABLE();
#endif         
      TIMER3_DISABLE();
    }
  return ret;  
}
Std_ReturnType timer3_write_val(const timer3_t* _timer , uint16_t val){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
      ret = E_NOT;
    }
  else
    {
       TMR3H = (uint8_t)( (val>>8) & 0xFF );
       TMR3L = (uint8_t)(val & 0xFF);   
    }
  return ret; 
}
Std_ReturnType timer3_read_val(const timer3_t* _timer , uint16_t* _retVal){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer || NULL == _retVal)
    {
      ret = E_NOT;
    }
  else
    {
      *_retVal = (TMR3L & 0xFF);
      *_retVal += ((((uint16_t)TMR3H) << 8) & 0xFF00);
    }
  return ret;  
}

static inline void timer3_counterMode_select(const timer3_t* _timer)
{
  if(NULL == _timer)
    return;
  else
    {
      switch(_timer->timer3_mode)
        {
        case TIMER3_TIMER_MODE_CFG:
          TIMER3_MODE_SELECT(0);
          break;
        case TIMER3_ASYNC_COUNTER_MODE_CFG:
          TIMER3_MODE_SELECT(1);
          TIMER3_ASYNC_COUNTER_ENABLE();
          break;
        case TIMER3_SYNC_COUNTER_MODE_CFG:
          TIMER3_MODE_SELECT(1);
          TIMER3_SYNC_COUNTER_ENABLE();
          break;
          
        default: return;
        }
    }
  return;
}

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static inline void timer3_interruptInit(const timer3_t* _timer){
  
  TIMER3_INTERRUPT_DISABLE();
  timer3_Interrupt_callBack = _timer->timer3_interruptHandler;
  TIMER3_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITY_FEATURE_ENABLE();
  INTERRUPT_HIGH_PRIORITY_ENABLE();
  INTERRUPT_LOW_PRIORITY_ENABLE();
  if (_timer->interrupt_pri == INTERRUPT_HIGH_PRIORITY)
    TIMER3_INTERRUPT_PRI_HIGH();
  else if (_timer->interrupt_pri == INTERRUPT_LOW_PRIORITY)
    TIMER3_INTERRUPT_PRI_LOW();
  else{/*Nothing*/}
#else
  INTERRUPT_ENABLE_UNMASKED();
  INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
  
#endif
  TIMER3_INTERRUPT_ENABLE();
  return; 
}


void TMR3_ISR(void)
{
  TIMER3_INTERRUPT_CLEAR_FLAG();
  TMR3H = (uint8_t)( (timer3_preloaded>>8) & 0xFF );
  TMR3L = (uint8_t)(timer3_preloaded & 0xFF);
  if(timer3_Interrupt_callBack)
    timer3_Interrupt_callBack();
  
  return;
}

#endif