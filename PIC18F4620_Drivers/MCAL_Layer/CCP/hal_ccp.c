/* 
 * File:   hal_ccp.c
 * Author: yossef
 *
 * Created on July 20, 2023, 3:51 AM
 */


#include"hal_ccp.h"




#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static  CCP_InterruptHandler_t global_ccp1_InterruptHandler = NULL;
static void inline ccp1_interrupt_init(const ccp_t* _ccpObj);

#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static CCP_InterruptHandler_t global_ccp2_InterruptHandler = NULL;
static void inline ccp2_interrupt_init(const ccp_t* _ccpObj);

#endif

static Std_ReturnType ccp1_init(const ccp_t* _ccpObj);
static Std_ReturnType ccp2_init(const ccp_t* _ccpObj);


Std_ReturnType ccp_init(const ccp_t* _ccpObj){
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    {
      ret = E_NOT;
    }
  else
    {
      switch(_ccpObj->ccp_inist)
        {
        case ccp1_inist:
          ret = ccp1_init (_ccpObj);
          break;
        case ccp2_inist:
          ret = ccp2_init (_ccpObj);
          break;
        default: ret = E_NOT;
        }
    }
  return ret;
}

        

Std_ReturnType ccp_Deinit(const ccp_t* _ccpObj){
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    {
      ret = E_NOT;
    }
  else
    {
    switch(_ccpObj->ccp_inist)
      {
      case ccp1_inist:
        CCP1_MODE_SELECT(CCP_DISABLE);
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_DISABLE();
#endif
        break;
      case ccp2_inist:
        CCP2_MODE_SELECT(CCP_DISABLE);
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_DISABLE();
#endif
        break;
      default: ret = E_NOT;
      }
    

      
    }
  return ret;  
}


#if CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED

Std_ReturnType ccp_check_CaptureDataReady(const ccp_t* _ccpObj , uint8_t* capture_stat){
  Std_ReturnType ret = E_OK;
  if(NULL == capture_stat)
    {
      ret = E_NOT;
    }
  else
    {
      
      switch(_ccpObj->ccp_inist)
        {
        case ccp1_inist:
            if( CCP_CAPTURE_OCCURED == PIR1bits.CCP1IF)
              {
                PIR1bits.CCP1IF = 0;
                *capture_stat = CCP_CAPTURE_OCCURED;
              }
            else
              {
                *capture_stat = CCP_CAPTURE_NOT_OCCURED;
              }
            break;
        case ccp2_inist:
            if( CCP_CAPTURE_OCCURED == PIR2bits.CCP2IF)
              {
                PIR2bits.CCP2IF = 0;
                *capture_stat = CCP_CAPTURE_OCCURED;
              }
            else
              {
                *capture_stat = CCP_CAPTURE_NOT_OCCURED;
              }
            break;
        default: ret = E_NOT;
        }
    }
  return ret;  
}
Std_ReturnType ccp_CaptureMode_ReadVal(const ccp_t* _ccpObj , uint16_t* capture_val){
  Std_ReturnType ret = E_OK;
  if(NULL == capture_val)
    {
      ret = E_NOT;
    }
  else
    {
      switch(_ccpObj->ccp_inist)
        {
        case ccp1_inist:
          *capture_val = CCPR1;
            break;
        case ccp2_inist:
          *capture_val = CCPR2;
            break;
        default: ret = E_NOT;
        } 
    }
    return ret;   
}

#endif

#if CCP_CFG_COMPARE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_COMPARE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED

Std_ReturnType ccp_check_Compare_Ocuured(const ccp_t* _ccpObj , uint8_t* compare_stat){
  Std_ReturnType ret = E_OK;
  if(NULL == compare_stat)
    {
      ret = E_NOT;
    }
  else
    {
      
      switch (_ccpObj->ccp_inist)
        {
        case ccp1_inist:
            if( CCP_COMPARE_OCCURED == PIR1bits.CCP1IF)
              {
                PIR1bits.CCP1IF = 0;
                *compare_stat = CCP_COMPARE_OCCURED;
              }
            else
              *compare_stat = CCP_COMPARE_NOT_OCCURED;
          break;
          
        case ccp2_inist:
            if( CCP_COMPARE_OCCURED == PIR2bits.CCP2IF)
              {
                PIR2bits.CCP2IF = 0;
                *compare_stat = CCP_COMPARE_OCCURED;
              }
            else
              *compare_stat = CCP_COMPARE_NOT_OCCURED;
          break;
          
        default: ret = E_NOT;
        }
    }
  return ret;   
}

Std_ReturnType ccp_CompareMode_SetVal(const ccp_t* _ccpObj , uint16_t compare_Val){
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    {
      ret = E_NOT;
    }
  else
    {
      
      switch (_ccpObj->ccp_inist)
        {
        case ccp1_inist:
            CCPR1 = compare_Val;
          break;
          
        case ccp2_inist:
            CCPR2 = compare_Val;
          break;
          
        default: ret = E_NOT;
        }
    }
  return ret;
}

#endif

#if CCP_CFG_PWM_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_PWM_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED

Std_ReturnType ccp_PWM_SetDuty(const ccp_t* _ccpObj , const uint8_t _duty){
  Std_ReturnType ret = E_OK;
  uint16_t l_duty_temp = 0;
  if(0 > _duty || 100 < _duty || NULL == _ccpObj)
    {
      ret = E_NOT;
    }
  else
    {
      if (ccp1_inist == _ccpObj->ccp_inist)
        {
            l_duty_temp = (uint16_t)((PR2 +1) * (_duty / 100.0) * 4);
            CCP1CONbits.DC1B = (uint8_t)(l_duty_temp & 0x03);
            CCPR1L = (uint8_t)(l_duty_temp >> 2);
            ret = E_OK;
        }
      else if (ccp2_inist == _ccpObj->ccp_inist)
        {
            l_duty_temp = (uint16_t)((PR2 +1) * (_duty / 100.0) * 4);
            CCP2CONbits.DC2B = (uint8_t)(l_duty_temp & 0x03);
            CCPR2L = (uint8_t)(l_duty_temp >> 2);
            ret = E_OK;          
        }
      else
        ret = E_NOT;
    }
  return ret;  
}

Std_ReturnType ccp_PWM_Start(const ccp_t* _ccpObj){
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    ret = E_NOT;
  else
    {
      if (ccp1_inist == _ccpObj->ccp_inist)
        {
          CCP1_MODE_SELECT(CCP_PWM_MODE);
        }
      else if (ccp2_inist == _ccpObj->ccp_inist)
        {
          CCP2_MODE_SELECT(CCP_PWM_MODE);
        }
      else
        ret = E_NOT;
    }
  return ret;  
}

Std_ReturnType ccp_PWM_Stop(const ccp_t* _ccpObj){
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    ret = E_NOT;
  else
    {
      if (ccp1_inist == _ccpObj->ccp_inist)
        {
          CCP1_MODE_SELECT(CCP_DISABLE);
        }
      else if (ccp2_inist == _ccpObj->ccp_inist)
        {
          CCP2_MODE_SELECT(CCP_DISABLE);
        }
      else
        ret = E_NOT;
    }
  return ret; 
}

#endif

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void inline ccp1_interrupt_init(const ccp_t* _ccpObj){
  
  CCP1_INTERRUPT_DISABLE();
  CCP1_INTERRUPT_CLEAR_FLAG();
  global_ccp1_InterruptHandler = _ccpObj->CCP_InterruptHandler;
  
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITY_FEATURE_ENABLE();
  INTERRUPT_HIGH_PRIORITY_ENABLE();
  INTERRUPT_LOW_PRIORITY_ENABLE();
  switch(_ccpObj->interrupt_pri)
    {
    case INTERRUPT_HIGH_PRIORITY:
      CCP1_INTERRUPT_PRI_HIGH();
      break;
      
    case INTERRUPT_LOW_PRIORITY:
      CCP1_INTERRUPT_PRI_LOW();      
      break;
    default :/*nothing*/ ;
              
    }
  
#else
  INTERRUPT_ENABLE_UNMASKED();
  INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
#endif
  
  CCP1_INTERRUPT_ENABLE();
  
  return;
}

#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void inline ccp2_interrupt_init(const ccp_t* _ccpObj){
  
  CCP2_INTERRUPT_DISABLE();
  CCP2_INTERRUPT_CLEAR_FLAG();
  global_ccp2_InterruptHandler = _ccpObj->CCP_InterruptHandler;
  
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITY_FEATURE_ENABLE();
  INTERRUPT_HIGH_PRIORITY_ENABLE();
  INTERRUPT_LOW_PRIORITY_ENABLE();
  switch(_ccpObj->interrupt_pri)
    {
    case INTERRUPT_HIGH_PRIORITY:
      CCP2_INTERRUPT_PRI_HIGH();
      break;
      
    case INTERRUPT_LOW_PRIORITY:
      CCP2_INTERRUPT_PRI_LOW();      
      break;
    default :/*nothing*/ ;
              
    }
  
#else
  INTERRUPT_ENABLE_UNMASKED();
  INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
#endif
  
  CCP2_INTERRUPT_ENABLE();
  
  return;
}

#endif

static Std_ReturnType ccp1_init(const ccp_t* _ccpObj)
{
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    {
      ret = E_NOT;
    }
  else
    {
      
      CCP1_MODE_SELECT(CCP_DISABLE);

      if (CCP_CAPTURE_MODE_SELECT == _ccpObj->ccp_mode)
        {
#if CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED || CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED
          switch (_ccpObj->ccp_ModeVariant)
            {
            case CCP_CAPTURE_MODE_FALLING_EDGE:
              CCP1_MODE_SELECT(CCP_CAPTURE_MODE_FALLING_EDGE);
              /* Select timer*/
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_CAPTURE_MODE_RISING_EDGE:
              CCP1_MODE_SELECT(CCP_CAPTURE_MODE_RISING_EDGE);
              /* Select timer*/
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
              CCP1_MODE_SELECT(CCP_CAPTURE_MODE_4_RISING_EDGE);
              /* Select timer*/
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
              CCP1_MODE_SELECT(CCP_CAPTURE_MODE_16_RISING_EDGE);
              /* Select timer*/
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);  
              break;
            default: ret =  E_NOT;
            }
#endif
        }
#if(CCP_CFG_COMPARE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED) || (CCP_CFG_COMPARE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED)
      else if (CCP_COMPARE_MODE_SELECT == _ccpObj->ccp_mode)
        {
          switch (_ccpObj->ccp_ModeVariant)
            {
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
              CCP1_MODE_SELECT(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_COMPARE_MODE_SET_HIGH:
              CCP1_MODE_SELECT(CCP_COMPARE_MODE_SET_HIGH);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_COMPARE_MODE_SET_LOW:
              CCP1_MODE_SELECT(CCP_COMPARE_MODE_SET_LOW);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_COMPARE_MODE_GEN_INTERRUPT:
              CCP1_MODE_SELECT(CCP_COMPARE_MODE_GEN_INTERRUPT);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
            case CCP_COMPARE_MODE_GEN_EVENT:
              CCP1_MODE_SELECT(CCP_COMPARE_MODE_GEN_EVENT);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
            default: ret = E_NOT;
            }          
        }
#endif
      
#if CCP_CFG_PWM_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED ||  CCP_CFG_PWM_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED
      else if (CCP_PWM_MODE_SELECT == _ccpObj->ccp_mode)
        {
          switch (_ccpObj->ccp_ModeVariant)
            {
            case CCP_PWM_MODE:
              CCP1_MODE_SELECT(CCP_PWM_MODE);
              break;
            default: ret = E_NOT;
            }
          // init pwm freq
          PR2 = (uint8_t)( ( _XTAL_FREQ / (_ccpObj->pwm_freq * 4.0 *_ccpObj->timer2_PostScaler * _ccpObj->timer2_PreScaler ) ) - 1);
          
        }
#endif
      else { /* nothing*/ }
      
      ret &= gpio_pin_intialize (&(_ccpObj->ccp_pin));
      
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      ccp1_interrupt_init(_ccpObj);
#endif
    }
  return ret;
}
  

static Std_ReturnType ccp2_init(const ccp_t* _ccpObj)
{
  Std_ReturnType ret = E_OK;
  if(NULL == _ccpObj)
    {
      ret = E_NOT;
    }
  else
    {
      
      CCP2_MODE_SELECT(CCP_DISABLE);
      ret &= gpio_pin_intialize (&(_ccpObj->ccp_pin));
      if (CCP_CAPTURE_MODE_SELECT == _ccpObj->ccp_mode)
        {
#if CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED || CCP_CFG_CAPTURE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED
          switch (_ccpObj->ccp_ModeVariant)
            {
            case CCP_CAPTURE_MODE_FALLING_EDGE:
              CCP2_MODE_SELECT(CCP_CAPTURE_MODE_FALLING_EDGE);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_CAPTURE_MODE_RISING_EDGE:
              CCP2_MODE_SELECT(CCP_CAPTURE_MODE_RISING_EDGE);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
              CCP2_MODE_SELECT(CCP_CAPTURE_MODE_4_RISING_EDGE);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
              CCP2_MODE_SELECT(CCP_CAPTURE_MODE_16_RISING_EDGE);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
            default: ret =  E_NOT;
            }
#endif
        }
#if(CCP_CFG_COMPARE_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED) || (CCP_CFG_COMPARE_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED)
      else if (CCP_COMPARE_MODE_SELECT == _ccpObj->ccp_mode)
        {
          switch (_ccpObj->ccp_ModeVariant)
            {
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
              CCP2_MODE_SELECT(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_COMPARE_MODE_SET_HIGH:
              CCP2_MODE_SELECT(CCP_COMPARE_MODE_SET_HIGH);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_COMPARE_MODE_SET_LOW:
              CCP2_MODE_SELECT(CCP_COMPARE_MODE_SET_LOW);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
              
            case CCP_COMPARE_MODE_GEN_INTERRUPT:
              CCP2_MODE_SELECT(CCP_COMPARE_MODE_GEN_INTERRUPT);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
            case CCP_COMPARE_MODE_GEN_EVENT:
              CCP2_MODE_SELECT(CCP_COMPARE_MODE_GEN_EVENT);
              T3CONbits.T3CCP1 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer ,(uint8_t)0);
              T3CONbits.T3CCP2 = BIT_READ((uint8_t)_ccpObj->ccp_capture_timer,(uint8_t)1);
              break;
            default: ret = E_NOT;
            }          
        }
#endif
      
#if CCP_CFG_PWM_MODE_SELECTED ==  CCP1_CFG_MODE_SELECTED || CCP_CFG_PWM_MODE_SELECTED ==  CCP2_CFG_MODE_SELECTED
      else if (CCP_PWM_MODE_SELECT == _ccpObj->ccp_mode)
        {
          switch (_ccpObj->ccp_ModeVariant)
            {
            case CCP_PWM_MODE:
              CCP2_MODE_SELECT(CCP_PWM_MODE);
              break;
            default: ret = E_NOT;
            }
          // init pwm freq
          PR2 = (uint8_t)( ( _XTAL_FREQ / (_ccpObj->pwm_freq * 4.0 *_ccpObj->timer2_PostScaler * _ccpObj->timer2_PreScaler ) ) - 1);
          
        }
#endif
      else { /* nothing*/ }
      
      
      
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
      ccp2_interrupt_init(_ccpObj);
#endif
    }
  return ret;
}


#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void CCP1_ISR(void)
{
  CCP1_INTERRUPT_CLEAR_FLAG();
  if(global_ccp1_InterruptHandler)
    {
       global_ccp1_InterruptHandler();
    }
  else { /* nothing*/}
  return;
}

#endif
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void CCP2_ISR(void)
{
  CCP2_INTERRUPT_CLEAR_FLAG();
  if(global_ccp2_InterruptHandler)
    {
       global_ccp2_InterruptHandler();
    }
  else { /* nothing*/}
  return;
}

#endif