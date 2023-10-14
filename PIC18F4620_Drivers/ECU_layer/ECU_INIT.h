/* 
 * File:   ECU_INIT.h
 * Author: yosse
 *
 * Created on February 22, 2023, 11:40 PM
 */

#ifndef ECU_INIT_H
#define	ECU_INIT_H

/*-------INCLUDES---------------------*/
#include "../MCAL_Layer/MCAL_INIT.h"
#include "led/ECU_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "Motor/ecu_motor.h"
#include "ecu_7_segment/ecu_7_segment.h"
#include "keypad/keypad.h"
#include "lcd/lcd.h"

/*----------MACRO Declraition----------------*/

/*-------Macro Functions ---------------------*/

/*-------user Data types ---------------------*/

/*----------functions prototype----------*/
Std_ReturnType app_inisialize(void);

#endif	/* ECU_INIT_H */

