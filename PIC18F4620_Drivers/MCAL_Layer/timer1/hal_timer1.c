/* 
 * File:   hal_timer1.h
 * Author: yossef
 *
 * Created on July 12, 2023, 5:14 AM
 */
#include "hal_timer1.h"

static uint16_t preloaded_val = 0;
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static timer1_interrupt_callBack_t timer1_interruptHandler = NULL;  

static inline void timer1_interrupt_init(const timer1_t* _timer);

#endif

static inline void timer1_counter_mode_select(const timer1_t* _timer);

Std_ReturnType timer1_init(const timer1_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
        ret = E_NOT;
        return ret;
    }
  else
    {
        TIMER1_DISABLE();
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        timer1_interrupt_init(_timer);
#endif
        
        TIMER1_MODE_SELECT(_timer->timer1_mode);
        
        // select if sync or Async mode if timer in counterMode 
        if(_timer->timer1_mode == TIMER1_COUNTER_MODE_CFG)
          {
            timer1_counter_mode_select(_timer);
          }
        
        //select R/W mode
         TIMER1_RW_MODE_SELECT(_timer->reg_rw_mode);
         
         // enable or disable timer1 osc
         switch(_timer->timer1_osc_mode)
           {
           case TIMER1_OSCI_ENABLE_CFG :
                TIMER1_OSCI_ENABLE();
                break;
             
            case TIMER1_OSCI_DISABLE_CFG :
                TIMER1_OSCI_DISABLE();
                break;
           default: /*ignore*/ ;
           }
            //slecet prescaler
         
         TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler);
            //write preloaded_val
         
         preloaded_val =  _timer->timer1_preloaded_val;
          TMR1H = (uint8_t)( (preloaded_val>>8) & 0xFF );
          TMR1L = (uint8_t)(preloaded_val & 0xFF);
          
         TIMER1_ENABLE();
    }
  
  return ret;
}

Std_ReturnType timer1_deinit(const timer1_t* _timer){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
        ret = E_NOT;
        return ret;
    }
  else
    {
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      TIMER1_INTERRUPT_DISABLE();
#endif
      TIMER1_DISABLE();      
    }
  return ret;  
}

Std_ReturnType timer1_write_val(const timer1_t* _timer , uint16_t val){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer)
    {
        ret = E_NOT;
        return ret;
    }
  else
    {
          TMR1H = (uint8_t)( (val>>8) & 0xFF );
          TMR1L = (uint8_t)(val & 0xFF);
    }
  return ret;  
}

Std_ReturnType timer1_read_val(const timer1_t* _timer , uint16_t* _retVal){
  Std_ReturnType ret = E_OK;
  if(NULL == _timer || NULL == _retVal)
    {
        ret = E_NOT;
        return ret;
    }
  else
    {
          *_retVal = TMR1L;
          *_retVal +=  (((uint16_t)TMR1H << 8) & 0xFF00);  
        
    }
  return ret;  
}

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline void timer1_interrupt_init(const timer1_t* _timer)
{

        TIMER1_INTERRUPT_DISABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        timer1_interruptHandler = _timer->_CallBack_func;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_FEATURE_ENABLE();
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        INTERRUPT_LOW_PRIORITY_ENABLE();
        switch(_timer->interrupt_pri)
          {
          case INTERRUPT_HIGH_PRIORITY:
            TIMER1_INTERRUPT_PRI_HIGH();
            break;
          case INTERRUPT_LOW_PRIORITY:
            TIMER1_INTERRUPT_PRI_LOW();
            break;
          default: ;
          }
#else
        INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
        INTERRUPT_ENABLE_UNMASKED();
        
        
#endif
        TIMER1_INTERRUPT_ENABLE();

        return;
}
#endif
static inline void timer1_counter_mode_select(const timer1_t* _timer)
{
            switch(_timer->timer1_counter_mode)
              {
              case TIMER1_SYNC_COUNTER_MODE_CFG:
                    TIMER1_SYNC_COUNTER_ENABLE();
                    break;
              case TIMER1_ASYNC_COUNTER_MODE_CFG:
                    TIMER1_ASYNC_COUNTER_ENABLE();
                    break;
              default: ;
              }
}

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TMR1_ISR(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (uint8_t)((preloaded_val)>>8);
    TMR1L = (uint8_t)(preloaded_val & 0xFF);  
  if(timer1_interruptHandler)
    {
      timer1_interruptHandler();
    }
  else
    {/*Nothing*/}
  return;
}
#endif