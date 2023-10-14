/* 
 * File:   ECU_led.h
 * Author: yossef
 *
 * Created on January 30, 2023, 11:49 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*-----------includes---------------*/
#include"../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ecu_led_cfg.h"

/*-----------Macros-------------*/

/*--------funcMacro-------------*/

/*-------userDataType-----------*/
typedef enum{
    LED_OFF,
            LED_ON
}led_stat_t;
typedef struct{
    uint8_t port_idx :3 ;
    uint8_t pin_idx : 3 ;
    uint8_t led_stat : 1; // default status
    uint8_t reserved : 1 ;
}led_t; 


/*----------FunctionDec--------------*/
/**
 * inistialize pin direction to output and set default led stat
 * @param led pointer to ledConfirgration @ref led_t
 * @return E_OK if done successfully
 */
Std_ReturnType ecu_led_inistialize(const led_t* led);
/**
 * turn led on
 * @param led pointer to led configration @ref led_t
 * @return E_OK if done successfully
 */
Std_ReturnType ecu_led_turn_on(const led_t* led);
/**
 * turn led off
 * @param led pointer to led configration @ref led_t
 * @return E_OK if done successfully
 */
Std_ReturnType ecu_led_turn_off(const led_t* led);
/**
 * toggle the led
 * @param led pointer to led configration @ref led_t
 * @return E_OK if done successfully
 */
Std_ReturnType ecu_led_toggle(const led_t* led);

#endif	/* ECU_LED_H */

