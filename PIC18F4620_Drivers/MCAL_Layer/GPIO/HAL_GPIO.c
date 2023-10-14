/* 
 * File:   HAL_GPIO.c
 * Author: yossef 
 *
 * Created on January 30, 2023, 11:26 PM
 */
/*---------------includes---------------*/
#include"HAL_GPIO.h"

/*-------------REGEISTERS----------------*/
/* PORTS ADDRESSES*/
/*@ref to port status reg*/
volatile uint8_t* port_reg[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/*@ref to data latch reg (read and write logic)*/
volatile uint8_t* lat_reg[] = {&LATA,&LATB,&LATC,&LATD,&LATE};
/*@ref to data direction reg (input/output)*/
volatile uint8_t* tris_reg[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};






/*--------------------------functions def----------------------------*/
/*-----------pins------------------------ */
Std_ReturnType gpio_pin_direction_intialize( const pinConfig_t* pinCon){
    Std_ReturnType ret = E_OK;
    if(!(pinCon) || (pinCon->port > MAX_PORT_INDEX) || (pinCon->pinIndex > MAX_PIN_INDEX))
    {
        ret = E_NOT;
    }
    else
    {
        switch (pinCon->direction){
                case output:
                  BIT_CLEAR(*tris_reg[pinCon->port], pinCon->pinIndex);
                 break;
                case input:
                  BIT_SET(*tris_reg[pinCon->port], pinCon->pinIndex);
                break;
                default: ret = E_NOT;
          }
    }
    return ret;
}
Std_ReturnType gpio_pin_get_direction(const pinConfig_t* pinCon ,direction_t* dir_status){
    Std_ReturnType ret = E_NOT;
    if(!(pinCon) || !(dir_status)|| (pinCon->port > MAX_PORT_INDEX) || (pinCon->pinIndex > MAX_PIN_INDEX))
    {
        ret = E_OK;
    }
    else
    {
      *dir_status = BIT_READ(*tris_reg[pinCon->port],pinCon->pinIndex);
    }
    return ret;
}
Std_ReturnType gpio_pin_write_logic(const pinConfig_t* pinCon ,logic_t logic){
    Std_ReturnType ret = E_OK;
    if(!(pinCon) || (pinCon->port > MAX_PORT_INDEX) || (pinCon->pinIndex > MAX_PIN_INDEX))
    {
        ret = E_NOT;
    }
    else
    {
        switch (logic){
          case low:
            BIT_CLEAR(*lat_reg[pinCon->port] , pinCon->pinIndex);
            break;
          case high:
            BIT_SET(*lat_reg[pinCon->port] , pinCon->pinIndex);
            break;
          default: ret = E_NOT;
          }
    }
    return ret;
}
Std_ReturnType gpio_pin_read_logic(const pinConfig_t* pinCon ,logic_t* ret_logic){
    Std_ReturnType ret = E_NOT;
    if(!(pinCon) || !(ret_logic)  || (pinCon->port > MAX_PORT_INDEX) || ( pinCon->pinIndex > MAX_PIN_INDEX))
    {
        ret = E_OK;
    }
    else
    {
        *ret_logic = BIT_READ(*port_reg[pinCon->port] , pinCon->pinIndex);
    }
    return ret;
}
Std_ReturnType gpio_pin_toggle_logic( pinConfig_t* pinCon){
    Std_ReturnType ret = E_NOT;
    if(!(pinCon) || (pinCon->port > MAX_PORT_INDEX ) || pinCon->pinIndex > MAX_PIN_INDEX)
    {
        ret = E_OK;
    }
    else
    {
        BIT_TOGGLE(*lat_reg[pinCon->port] , pinCon->pinIndex);
    }
    return ret;
}

Std_ReturnType gpio_pin_intialize( const pinConfig_t* pinCon)
{
  Std_ReturnType ret = E_OK;
  if(!(pinCon) || pinCon->port > MAX_PORT_INDEX || pinCon->pinIndex > MAX_PIN_INDEX)
    {
      ret = E_NOT;
    }
  else
    {
      ret = gpio_pin_direction_intialize (pinCon);
      ret = gpio_pin_write_logic (pinCon , pinCon->logic);
    }
  return ret;
}
/*-------------port------------------------*/
Std_ReturnType gpio_port_direction_intialize( const PortIndex_t port , uint8_t dir){
  Std_ReturnType ret = E_OK;
  if(port> MAX_PORT_INDEX)
    {
      ret = E_NOT;
    }
  else
      *tris_reg[port] = dir;
  return ret;
}
Std_ReturnType gpio_port_get_direction_stat(const PortIndex_t port , uint8_t* dir_status){
    Std_ReturnType ret = E_OK;
    if(port > MAX_PORT_INDEX)
      {
        ret = E_NOT;
      }
    else
        *dir_status = *tris_reg[port];
    
    return ret;
    
}
Std_ReturnType gpio_port_write_logic(const PortIndex_t port ,uint8_t logic){
    Std_ReturnType ret = E_OK;
    if(port > MAX_PORT_INDEX)
      ret = E_NOT;
    else
      *lat_reg[port] = logic;
    return ret;
}
Std_ReturnType gpio_port_read_logic(const PortIndex_t port ,uint8_t *ret_logic){
    Std_ReturnType ret = E_OK;
    if(port > MAX_PORT_INDEX || !(ret_logic))
      ret = E_NOT;
    else
      *ret_logic = *lat_reg[port];
    return ret;
}
Std_ReturnType gpio_port_toggle_logic(const PortIndex_t port){
    Std_ReturnType ret = E_OK;
    if(port > MAX_PORT_INDEX)
      ret = E_NOT;
    else
      PORT_TOGGLE(*lat_reg[port]);
    return ret;
}




