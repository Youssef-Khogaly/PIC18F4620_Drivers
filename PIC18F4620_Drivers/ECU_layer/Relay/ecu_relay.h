/* 
 * File:   ecu_relay.h
 * Author: yossef
 *
 * Created on February 13, 2023, 12:59 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*-----------includes-------------*/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ecu_relay_cfg.h"
/*-------------macro defines----------*/
#define RELAY_ON    0x01U
#define RELAY_OFF   0x00U
/*--------------macro-functions-----------*/

/*----------user-datatypes-----------*/
typedef struct{
    uint8_t relay_port : 3;
    uint8_t relay_pin : 3 ;
    uint8_t relay_stat : 1;
    uint8_t reserved : 1 ;
}relay_t;
/*---------interfaces-prototype-------*/
/**
 *          inisialize relay pin
 * @param relay pointer to @ref relay_t
 * @return  @ref Std_ReturnType
 *          E_OK = 1 -> function done sucessfully
 *          E_NOT = 0 - > some thing go wrong
 */
Std_ReturnType ecu_relay_inisialize(const relay_t* relay);
/**
 *       turn relay on
 * @param relay pointer to @ref relay_t
 * @return  @ref Std_ReturnType
 *          E_OK = 1 -> function done sucessfully
 *          E_NOT = 0 - > some thing go wrong
 */
Std_ReturnType ecu_relay_turn_on(const relay_t* relay);
/**
 *          turn relay off
 * @param relay pointer to @ref relay_t
 * @return  @ref Std_ReturnType
 *          E_OK = 1 -> function done sucessfully
 *          E_NOT = 0 - > some thing go wrong
 */
Std_ReturnType ecu_relay_turn_off(const relay_t* relay);
/**
 *      toggle relay
 * @param relay pointer to @ref relay_t
 * @return  @ref Std_ReturnType
 *          E_OK = 1 -> function done sucessfully
 *          E_NOT = 0 - > some thing go wrong
 */
Std_ReturnType ecu_relay_toggle(const relay_t* relay);
/**
 *          
 * @param relay pointer to @ref relay_t
 * @param ret_stat pointer to uint8  use it to return current relay status
 * @return  @ref Std_ReturnType
 *          E_OK = 1 -> function done sucessfully
 *          E_NOT = 0 - > some thing go wrong
 */
Std_ReturnType ecu_relay_read_stat(const relay_t* relay ,uint8_t* ret_stat);
#endif	/* ECU_RELAY_H */

