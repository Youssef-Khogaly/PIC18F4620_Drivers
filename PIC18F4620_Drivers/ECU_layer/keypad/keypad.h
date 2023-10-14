/* 
 * File:   keypad.h
 * Author: yosse
 *
 * Created on February 21, 2023, 11:42 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/*---------- Includes -----------*/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
/*--------- Macro Declarition ---*/
#define ECU_KEYPAD_ROWS     4
#define ECU_KEYPAD_COL      4
/*------- Macro functions --------*/

/*---------- Data types ----------*/
typedef struct{
    pinConfig_t keypad_rows_pins[ECU_KEYPAD_ROWS];
    pinConfig_t keypad_col_pins[ECU_KEYPAD_COL];
}keypad_t;
/*-------- interfaces prototypes ---*/
Std_ReturnType ecu_keypad_inisialize(const keypad_t* _keypad);
Std_ReturnType ecu_keypad_scan_value(const keypad_t* _keypad , uint8_t* value);

#endif	/* KEYPAD_H */

