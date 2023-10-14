/* 
 * File:   ecu_relay.c
 * Author: yossef
 *
 * Created on February 13, 2023, 12:59 AM
 */
#include "ecu_relay.h"


#if ECU_RELAY_CONF == ECU_RELAY_CFG_ON
Std_ReturnType ecu_relay_inisialize(const relay_t* relay){
  Std_ReturnType ret_std = E_OK;
  if((!(relay)) || (relay->relay_port > MAX_PORT_INDEX) || (relay->relay_pin > MAX_PIN_INDEX))
    ret_std = E_NOT;
  else{
        pinConfig_t pincfg = {
        .port = relay->relay_port,
        .pinIndex = relay->relay_pin,
        .direction = output,
        .logic = relay->relay_stat};
      ret_std = gpio_pin_intialize (&pincfg);
    }
  return ret_std;
}
#endif

#if ECU_RELAY_CONF == ECU_RELAY_CFG_ON
Std_ReturnType ecu_relay_turn_on(const relay_t* relay){
  Std_ReturnType ret_std = E_OK;
  if((!(relay)) || (relay->relay_port > MAX_PORT_INDEX) || (relay->relay_pin > MAX_PIN_INDEX))
        ret_std = E_NOT;
  else{
        pinConfig_t pincfg = {
        .port = relay->relay_port,
        .pinIndex = relay->relay_pin,
        .direction = output,
        .logic = relay->relay_stat};
        ret_std = gpio_pin_write_logic (&pincfg , RELAY_ON);
    }
  return ret_std;
}
#endif

#if ECU_RELAY_CONF == ECU_RELAY_CFG_ON
Std_ReturnType ecu_relay_turn_off(const relay_t* relay){
  Std_ReturnType ret_std = E_OK;
  if((!(relay)) || (relay->relay_port > MAX_PORT_INDEX) || (relay->relay_pin > MAX_PIN_INDEX))
        ret_std = E_NOT;
  else{
        pinConfig_t pincfg = {
        .port = relay->relay_port,
        .pinIndex = relay->relay_pin,
        .direction = output,
        .logic = relay->relay_stat};
        ret_std = gpio_pin_write_logic (&pincfg , RELAY_OFF);
    }
  return ret_std; 
}
#endif

#if ECU_RELAY_CONF == ECU_RELAY_CFG_ON
Std_ReturnType ecu_relay_toggle(const relay_t* relay){
  Std_ReturnType ret_std = E_OK;
  if((!(relay)) || (relay->relay_port > MAX_PORT_INDEX) || (relay->relay_pin > MAX_PIN_INDEX))
        ret_std = E_NOT;
  else{
        pinConfig_t pincfg = {
        .port = relay->relay_port,
        .pinIndex = relay->relay_pin,
        .direction = output,
        .logic = relay->relay_stat};
        ret_std = gpio_pin_toggle_logic (&pincfg);
    }
  return ret_std;  
}
#endif