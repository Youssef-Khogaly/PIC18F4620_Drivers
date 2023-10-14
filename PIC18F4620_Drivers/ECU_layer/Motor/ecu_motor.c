/* 
 * File:   ecu_motor.c
 * Author: yossef
 *
 * Created on February 14, 2023, 5:21 PM
 */
#include "ecu_motor.h"

Std_ReturnType ecu_motor_inisialize(const motor_t * motor){
  Std_ReturnType ret = E_OK;
  if(!(motor) || (motor->dc_motor[0].port > MAX_PORT_INDEX)|| (motor->dc_motor[1].pinIndex > MAX_PIN_INDEX))
    ret = E_NOT;
  else{         
      ret = gpio_pin_intialize (&(motor->dc_motor[0]));
      ret = gpio_pin_intialize (&(motor->dc_motor[1]));
    }
  return ret;
}
Std_ReturnType ecu_motor_turn_left(const motor_t * motor)
{
  Std_ReturnType ret = E_OK;
  if(!(motor))
    ret = E_NOT;
  else{ 
      ret = gpio_pin_write_logic (&(motor->dc_motor[0]) , low);
      ret = gpio_pin_write_logic (&(motor->dc_motor[1]) , high);
    }
    return ret;
}
Std_ReturnType ecu_motor_turn_right(const motor_t * motor){
  Std_ReturnType ret = E_OK;
  if(!(motor))
    ret = E_NOT;
  else{ 
      ret = gpio_pin_write_logic (&(motor->dc_motor[0]) , high);
      ret = gpio_pin_write_logic (&(motor->dc_motor[1]) , low);      
    }
    return ret;  
}
Std_ReturnType ecu_motor_stop(const motor_t * motor)
{
  Std_ReturnType ret = E_OK;
  if(!(motor) || (motor->dc_motor[0].port > MAX_PORT_INDEX)|| (motor->dc_motor[1].pinIndex > MAX_PIN_INDEX))
    ret = E_NOT;
  else{ 
        ret = gpio_pin_write_logic (&(motor->dc_motor[0]) , high);
        ret = gpio_pin_write_logic (&(motor->dc_motor[1]) , high);
    }
    return ret;  
}
