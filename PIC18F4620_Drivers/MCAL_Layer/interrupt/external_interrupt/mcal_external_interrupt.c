/* 
 * File:   mcal_external_interrupt.c
 * Author: yossef
 *
 * Created on April 5, 2023, 10:56 AM
 */
#include "mcal_external_interrupt.h"

/*------------------------------*/
// pointer to call back functions 
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
static InterruptHandler_t INT0_InterruptHandler = NULL;
static InterruptHandler_t INT1_InterruptHandler = NULL;
static InterruptHandler_t INT2_InterruptHandler = NULL;
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
static InterruptHandler_t RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler_t RB4_InterruptHandler_LOW = NULL;

static InterruptHandler_t RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler_t RB5_InterruptHandler_LOW = NULL;

static InterruptHandler_t RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler_t RB6_InterruptHandler_LOW = NULL;

static InterruptHandler_t RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler_t RB7_InterruptHandler_LOW = NULL;
#endif
/*-----------helper functions ---------------*/
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_intx_enable(const interrupt_INTx_t* interrupt_obj);
static Std_ReturnType interrupt_intx_disable(const interrupt_INTx_t* interrupt_obj);
static Std_ReturnType interrupt_intx_priority_init(const interrupt_INTx_t* interrupt_obj);
static Std_ReturnType interrupt_intx_edge_init(const interrupt_INTx_t* interrupt_obj);
static Std_ReturnType interrupt_intx_pin_init(const interrupt_INTx_t* interrupt_obj);
static Std_ReturnType interrupt_intx_clear_flag(const interrupt_INTx_t* interrupt_obj);
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t* interrupt_obj);
static Std_ReturnType interrupt_RBx_disable(const interrupt_RBx_t* interrupt_obj);
static Std_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t* interrupt_obj);
static Std_ReturnType interrupt_RBx_pullup_init(const interrupt_RBx_t* interrupt_obj);
static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t* interrupt_obj);
static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t* interrupt_obj);
#endif

/*------- interrupt handler helper functoins-------*/
// set the call back function address in the pointer
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INTx_SetInterruptHandler(const interrupt_INTx_t* interrupt_obj);

#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType RBx_SetInterruptHandler(const interrupt_RBx_t* interrupt_obj);
#endif
/*------------------------*/
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
void INTO_ISR(void){
  /*------clear flag--------*/
  INTERRUPT_INT0_CLEAR_FLAG();
  /*----Code-------*/
  /*-----Call back function*/
  if(INT0_InterruptHandler)
        INT0_InterruptHandler();
    return;
}
void INT1_ISR(void){
  /*------clear flag--------*/
  INTERRUPT_INT1_CLEAR_FLAG();
  /*----Code-------*/
  /*-----Call back function*/
  if(INT1_InterruptHandler)
        INT1_InterruptHandler();
    return;
}
void INT2_ISR(void){
  /*------clear flag--------*/
  INTERRUPT_INT2_CLEAR_FLAG();
  /*----Code-------*/
  /*-----Call back function*/
  if(INT2_InterruptHandler)
        INT2_InterruptHandler();
    return;
}
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
void RB4_ISR(uint8_t RB4_src){
  
  /*---clear flag---*/
  INTERRUPT_ONCHANGE_CLEAR_FLAG();
  /*code*/
  
  /*call back function*/
  if(1 == RB4_src)
    {
  if(RB4_InterruptHandler_HIGH)
    RB4_InterruptHandler_HIGH();      
    }
  else if (0 == RB4_src)
    {
  if(RB4_InterruptHandler_LOW)
    RB4_InterruptHandler_LOW();      
    }
  else {/*no thing*/}
  return;
}
void RB5_ISR(uint8_t RB5_src){
  
  /*---clear flag---*/
  INTERRUPT_ONCHANGE_CLEAR_FLAG();
  /*code*/
  
  /*call back function*/
  if(1 == RB5_src)
    {
  if(RB5_InterruptHandler_HIGH)
    RB5_InterruptHandler_HIGH();      
    }
  else if (0 == RB5_src)
    {
  if(RB5_InterruptHandler_LOW)
    RB5_InterruptHandler_LOW();      
    }
  else {/*no thing*/}
  return;
}
void RB6_ISR(uint8_t RB6_src){
  
  /*---clear flag---*/
  INTERRUPT_ONCHANGE_CLEAR_FLAG();
  /*code*/
  
  /*call back function*/
  if(1 == RB6_src)
    {
  if(RB6_InterruptHandler_HIGH)
    RB6_InterruptHandler_HIGH();      
    }
  else if (0 == RB6_src)
    {
  if(RB6_InterruptHandler_LOW)
    RB6_InterruptHandler_LOW();      
    }
  else {/*no thing*/}
  return;
}
void RB7_ISR(uint8_t RB7_src){
  
  /*---clear flag---*/
  INTERRUPT_ONCHANGE_CLEAR_FLAG();
  /*code*/
  
  /*call back function*/
  if(1 == RB7_src)
    {
  if(RB7_InterruptHandler_HIGH)
    RB7_InterruptHandler_HIGH();      
    }
  else if (0 == RB7_src)
    {
  if(RB7_InterruptHandler_LOW)
    RB7_InterruptHandler_LOW();      
    }
  else {/*no thing*/}
  return;
}
#endif
/*-----------------------------*/
/**
 * 
 * @param interrupt_obj const pointer to @ref interrupt_INTx_t
 * @return Std_ReturnType
 * E_OK - > 1 if done sucessfully
 * E_NOT -> 0 if function fail
 */
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
Std_ReturnType interrupt_intx_init(const interrupt_INTx_t* interrupt_obj){
    Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = interrupt_intx_disable(interrupt_obj);
      ret = interrupt_intx_clear_flag(interrupt_obj);
      ret = interrupt_intx_edge_init(interrupt_obj);
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
      ret = interrupt_intx_priority_init(interrupt_obj);
#endif
      ret = interrupt_intx_pin_init(interrupt_obj);
      /* call back function*/
      ret = INTx_SetInterruptHandler(interrupt_obj);
      ret = interrupt_intx_enable(interrupt_obj);      
    }
  return ret;
}

/**
 * 
 * @param interrupt_obj const pointer to @ref interrupt_INTx_t
 * @return Std_ReturnType
 * E_OK - > 1 if done sucessfully
 * E_NOT -> 0 if function fail
 */
Std_ReturnType interrupt_intx_Deinit(const interrupt_INTx_t* interrupt_obj){
    Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = interrupt_intx_disable(interrupt_obj);
    }
  return ret;
}
#endif
/**
 * 
 * @param interrupt_obj const pointer to @ref interrupt_INTx_t
 * @return Std_ReturnType
 * E_OK - > 1 if done sucessfully
 * E_NOT -> 0 if function fail
 */
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t* interrupt_obj){
   Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = interrupt_RBx_disable(interrupt_obj);
      ret = interrupt_RBx_clear_flag(interrupt_obj);
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
      ret = interrupt_RBx_priority_init(interrupt_obj);
#endif
      ret = interrupt_RBx_pullup_init(interrupt_obj);
      ret = interrupt_RBx_pin_init(interrupt_obj);
      ret = RBx_SetInterruptHandler(interrupt_obj);
      ret = interrupt_RBx_enable(interrupt_obj);
    }
  return ret;
}

/**
 * 
 * @param interrupt_obj const pointer to @ref interrupt_INTx_t
 * @return Std_ReturnType
 * E_OK - > 1 if done sucessfully
 * E_NOT -> 0 if function fail
 */
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t* interrupt_obj){
    Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = interrupt_RBx_disable(interrupt_obj);
    }
  return ret;
}
#endif
/*---------helper function def ---------*/
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_intx_enable(const interrupt_INTx_t* interrupt_obj){
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
      ret = E_NOT;
  else{
      ret = E_OK;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
      INTERRUPT_PRIORITY_FEATURE_ENABLE();
      if(interrupt_obj->priority == INTERRUPT_HIGH_PRIORITY)
        INTERRUPT_HIGH_PRIORITY_ENABLE();
      else
        INTERRUPT_LOW_PRIORITY_ENABLE();

#else
      INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
      INTERRUPT_ENABLE_UNMASKED();
#endif
      switch (interrupt_obj->source)
        {
        case INTERRUPT_INT0 : INTERRUPT_INT0_ENABLE() ; break;
        case INTERRUPT_INT1 : INTERRUPT_INT1_ENABLE() ; break;
        case INTERRUPT_INT2 : INTERRUPT_INT2_ENABLE() ; break;
        default: ret = E_NOT;
        }
    }
  return ret;
}
static Std_ReturnType interrupt_intx_disable(const interrupt_INTx_t* interrupt_obj){
   Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
        ret = E_OK;
        switch (interrupt_obj->source)
        {
        case INTERRUPT_INT0: INTERRUPT_INT0_DISABLE() ; break;
        case INTERRUPT_INT1: INTERRUPT_INT1_DISABLE() ; break;
        case INTERRUPT_INT2: INTERRUPT_INT2_DISABLE() ; break;
        default: ret = E_NOT;
        }
    }
  return ret;
}

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_intx_priority_init(const interrupt_INTx_t* interrupt_obj){
  Std_ReturnType  ret = E_NOT;
  if(!(interrupt_obj) || (interrupt_obj->source == INTERRUPT_INT0))
    ret = E_NOT;
  else{
      ret = E_OK;
      switch (interrupt_obj->priority){
        case INTERRUPT_HIGH_PRIORITY:
          
          switch(interrupt_obj->source){
            case INTERRUPT_INT1:
              INTERRUPT_INT1_PRIO_HIGH();
              break;
            case INTERRUPT_INT2:
              INTERRUPT_INT2_PRIO_HIGH();
              break;
              
            default: ret= E_NOT;
            }
          break;
          case INTERRUPT_LOW_PRIORITY:
            
            switch(interrupt_obj->source){
                
            case INTERRUPT_INT1:
              INTERRUPT_INT1_PRIO_LOW();
              break;
            case INTERRUPT_INT2:
              INTERRUPT_INT2_PRIO_LOW();
              break;
              default: ret = E_NOT;
              }
            break;
          
        default: ret = E_NOT ;
        }
    }
  return ret;
}
#endif

static Std_ReturnType interrupt_intx_edge_init(const interrupt_INTx_t* interrupt_obj){
   Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = E_OK;
      switch(interrupt_obj->source){
        case INTERRUPT_INT0:
          switch(interrupt_obj->edge){
            case INTERRUPT_RISING_EDGE:
              INTERRUPT_INT0_RISING_EDGE();
              break;
            case INTERRUPT_FALLING_EDGE:
              INTERRUPT_INT0_FALLING_EDGE();
              break;
            default: ret = E_NOT;
            }
          break;
        case INTERRUPT_INT1:
            switch(interrupt_obj->edge){
            case INTERRUPT_RISING_EDGE:
              INTERRUPT_INT1_RISING_EDGE();
              break;
            case INTERRUPT_FALLING_EDGE:
              INTERRUPT_INT1_FALLING_EDGE();
              break;
              default: ret = E_NOT;
            }
          break;
        case INTERRUPT_INT2:
            switch(interrupt_obj->edge){
            case INTERRUPT_RISING_EDGE:
              INTERRUPT_INT2_RISING_EDGE();
              break;
            case INTERRUPT_FALLING_EDGE:
              INTERRUPT_INT2_FALLING_EDGE();
              break;
              default: ret = E_NOT;
            }
          break;
        default: ret = E_NOT;
        }
    }
  return ret;
}
static Std_ReturnType interrupt_intx_pin_init(const interrupt_INTx_t* interrupt_obj){
   Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = gpio_pin_direction_intialize (&(interrupt_obj->mca_pin));
    }
  return ret;
}

static Std_ReturnType interrupt_intx_clear_flag(const interrupt_INTx_t* interrupt_obj){
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
      ret = E_NOT;
  else{
      ret = E_OK;      
      switch (interrupt_obj->source)
        {
        case INTERRUPT_INT0 : INTERRUPT_INT0_CLEAR_FLAG() ; break;
        case INTERRUPT_INT1 : INTERRUPT_INT1_CLEAR_FLAG() ; break;
        case INTERRUPT_INT2 : INTERRUPT_INT2_CLEAR_FLAG() ; break;
        default: ret = E_NOT;
        }
    }
  return ret; 
}
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t* interrupt_obj){
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = E_OK;
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
      INTERRUPT_PRIORITY_FEATURE_ENABLE();
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        INTERRUPT_LOW_PRIORITY_ENABLE();

#else
    INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
    INTERRUPT_ENABLE_UNMASKED();

#endif
      INTERRUPT_ONCHANGE_ENABLE();
    }
  return ret;
}

static Std_ReturnType interrupt_RBx_disable(const interrupt_RBx_t* interrupt_obj){
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = E_OK;
      INTERRUPT_ONCHANGE_DISABLE();
    }
  return ret;  
}
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t* interrupt_obj){
    Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = E_OK;
      switch(interrupt_obj->priority){
        case INTERRUPT_LOW_PRIORITY:
          INTERRUPT_ONCHANGE_PRIO_LOW();
          break;
        case INTERRUPT_HIGH_PRIORITY:
          INTERRUPT_ONCHANGE_PRIO_HIGH();
          break;
        default: ret = E_NOT;
        }
    }
  return ret; 
}
#endif
static Std_ReturnType interrupt_RBx_pullup_init(const interrupt_RBx_t* interrupt_obj){
    Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = E_OK;
      switch(interrupt_obj->pullup_status){
        case INTERRUPT_RBx_PULLUP_ACTIVE:
          INTERRUPT_ONCHANGE_PULLUP_ENABLE();
          break;
        case INTERRUPT_RBx_PULLUP_DISABLE:
          INTERRUPT_ONCHANGE_PULLUP_DISABLE();
          break;
        default: ret = E_NOT;
        }
    }
  return ret;   
}
static Std_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t* interrupt_obj){
    Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = gpio_pin_direction_intialize (&(interrupt_obj->mca_pin));
    }
    
    return ret;
}

static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t* interrupt_obj){
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
    ret = E_NOT;
  else{
      ret = E_OK;
      INTERRUPT_ONCHANGE_CLEAR_FLAG();
    }
  return ret;
}
#endif
/*--------interrupt handler functions-----------*/
#if INTERRUPT_EXTERNAL_INTX_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
  Std_ReturnType ret = E_NOT;
  if(NULL == InterruptHandler)
    ret = E_NOT;
  else{
      INT0_InterruptHandler = InterruptHandler;
    }
  return ret;
}
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT;
  if(NULL == InterruptHandler)
    ret = E_NOT;
  else{
      INT1_InterruptHandler = InterruptHandler;
    }
  return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT;
  if(NULL == InterruptHandler)
    ret = E_NOT;
  else{
      INT2_InterruptHandler = InterruptHandler;
    }
  return ret;
}

static Std_ReturnType INTx_SetInterruptHandler(const interrupt_INTx_t* interrupt_obj){
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj))
      ret = E_NOT;
  else{   
      switch (interrupt_obj->source)
        {
        case INTERRUPT_INT0 :
          ret =  INT0_SetInterruptHandler(interrupt_obj->Ext_interruptHandler);
          break;
        case INTERRUPT_INT1 :
          ret =  INT1_SetInterruptHandler(interrupt_obj->Ext_interruptHandler);
          break;
        case INTERRUPT_INT2 :
          ret =  INT2_SetInterruptHandler(interrupt_obj->Ext_interruptHandler);
          break;
        default: ret = E_NOT;
        }
    }
  return ret; 
}
#endif
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE  == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType RBx_SetInterruptHandler(const interrupt_RBx_t* interrupt_obj)
{
  Std_ReturnType ret = E_NOT;
  if(!(interrupt_obj) ||( interrupt_obj->mca_pin.port != PORTB_INDEX))
      ret = E_NOT;
  else{   
      switch (interrupt_obj->mca_pin.pinIndex)
        {
        case pin4 :
          RB4_InterruptHandler_HIGH = interrupt_obj->Ext_Interrupt_high;
          RB4_InterruptHandler_LOW = interrupt_obj->Ext_interrupt_low;
          break;
        case pin5:
          RB5_InterruptHandler_HIGH = interrupt_obj->Ext_Interrupt_high;
          RB5_InterruptHandler_LOW = interrupt_obj->Ext_interrupt_low;
          break;
        case pin6 :
          RB6_InterruptHandler_HIGH = interrupt_obj->Ext_Interrupt_high;
          RB6_InterruptHandler_LOW = interrupt_obj->Ext_interrupt_low;
          break;
        case pin7:
          RB7_InterruptHandler_HIGH = interrupt_obj->Ext_Interrupt_high;
          RB7_InterruptHandler_LOW = interrupt_obj->Ext_interrupt_low;
          break;
        default: ret = E_NOT;
        }
    }
  return ret;   
}
#endif