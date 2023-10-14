/* 
 * File:   ECU_led.h
 * Author: yossef.h
 *
 * Created on January 30, 2023, 11:49 PM
 */


/*------------Includes----------------*/
#include"ECU_led.h"














/*------------function defination--------------*/
Std_ReturnType ecu_led_inistialize(const led_t* led)
{
  Std_ReturnType ret = E_OK;
  pinConfig_t pinCfg = {
    .port = led->port_idx,
    .pinIndex = led->pin_idx,
    .direction = output,
    .logic = led->led_stat
  };
  if(!(led) || (led->port_idx > MAX_PORT_INDEX) || (led->pin_idx > MAX_PIN_INDEX) || (led->led_stat > 1))
        ret = E_NOT;
  else
      ret = gpio_pin_intialize (&pinCfg);
    
  return ret;
}
Std_ReturnType ecu_led_turn_on(const led_t* led)
{
  Std_ReturnType ret = E_OK;
  pinConfig_t pinCfg = {
    .port = led->port_idx,
    .pinIndex = led->pin_idx,
    .direction = output,
    .logic = LED_ON
  };
  direction_t dir = input;
  ret = gpio_pin_get_direction (&pinCfg , &dir);
  if(!(led) || (led->port_idx > MAX_PORT_INDEX) || (led->pin_idx > MAX_PIN_INDEX) || (led->led_stat > 1) || ( dir != output))
        ret = E_NOT;
  else
    {      
      ret = gpio_pin_write_logic (&pinCfg , high);
    }
  return ret;  
}
Std_ReturnType ecu_led_turn_off(const led_t* led)
{
  Std_ReturnType ret = E_OK;
  pinConfig_t pinCfg = {
    .port = led->port_idx,
    .pinIndex = led->pin_idx,
    .direction = output,
    .logic = LED_OFF
  };
  direction_t dir = input;
  ret = gpio_pin_get_direction (&pinCfg , &dir);
  if(!(led) || (led->port_idx > MAX_PORT_INDEX) || (led->pin_idx > MAX_PIN_INDEX) || (led->led_stat > 1) || ( dir != output))
        ret = E_NOT;
  else
    {      
      ret = gpio_pin_write_logic (&pinCfg , low);
    }
  return ret;  
  
}
Std_ReturnType ecu_led_toggle(const led_t* led)
{
  Std_ReturnType ret = E_OK;
  pinConfig_t pinCfg = {
    .port = led->port_idx,
    .pinIndex = led->pin_idx,
    .direction = output,
    .logic = led->led_stat
  };
  direction_t dir = input;
  ret = gpio_pin_get_direction (&pinCfg , &dir);
  if(!(led) || (led->port_idx > MAX_PORT_INDEX) || (led->pin_idx > MAX_PIN_INDEX) || (led->led_stat > 1) || ( dir != output))
        ret = E_NOT;
  else
    {
      ret = gpio_pin_toggle_logic (&pinCfg);
    }
  return ret;   
}

