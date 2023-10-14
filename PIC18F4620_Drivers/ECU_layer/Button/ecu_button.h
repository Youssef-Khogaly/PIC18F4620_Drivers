/* 
 * File:   ecu_button.h
 * Author: yosse
 *
 * Created on February 11, 2023, 1:51 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/*----------includes----------------*/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
/*--------------macros----------------*/

/*-------------macro func--------------*/

/*--------------user data types---------*/
typedef enum{
    BUTTON_RELAISED = 0,
            BUTTON_PRESSED
}button_stat_t;

typedef enum{
    BUTTON_ACTIVE_LOW,
            BUTTON_ACTIVE_HIGH
}button_active_t;

typedef struct{
    pinConfig_t button;
    button_stat_t btn_stat;
    button_active_t button_connection;
}button_t;
/*--------interfacing prototype---------*/
Std_ReturnType button_inisialize(const button_t* btn);
Std_ReturnType button_read_stat(const button_t * btn , button_stat_t* ret_stat);
#endif	/* ECU_BUTTON_H */

