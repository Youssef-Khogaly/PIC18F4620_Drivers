/* 
 * File:   ecu_button.c
 * Author: yossef
 *
 * Created on February 11, 2023, 1:51 AM
 */
#include "ecu_button.h"

Std_ReturnType button_inisialize(const button_t* btn){
  Std_ReturnType ret = E_OK;
  if(!(btn) || btn->button.port > MAX_PORT_INDEX || btn->button.pinIndex > MAX_PIN_INDEX)
    ret = E_NOT;
  else
      gpio_pin_direction_intialize (&(btn->button));
      
  return ret;
}
Std_ReturnType button_read_stat(const button_t * btn , button_stat_t* btn_stat)
{
  Std_ReturnType ret = E_OK;
  direction_t dir;
  logic_t read_pin_logic = low;
  ret =  gpio_pin_get_direction (&(btn->button) , &dir);
  if(!(btn) || (btn->button.port > MAX_PORT_INDEX) || (btn->button.pinIndex > MAX_PIN_INDEX) || (dir == output))
    ret = E_NOT;
  else
    {
      ret = gpio_pin_read_logic (&(btn->button) ,  &read_pin_logic);
      if(BUTTON_ACTIVE_HIGH == btn->button_connection){
          *btn_stat = (read_pin_logic == high) ? BUTTON_PRESSED : BUTTON_RELAISED;
        }
      else if (BUTTON_ACTIVE_LOW == btn->button_connection){
          *btn_stat = (read_pin_logic == low) ? BUTTON_PRESSED : BUTTON_RELAISED;
        }
      else
        ret = E_NOT;
    }
  return ret;  
}