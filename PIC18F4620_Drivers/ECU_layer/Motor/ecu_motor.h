/* 
 * File:   ecu_motor.h
 * Author: yossef
 *
 * Created on February 14, 2023, 5:21 PM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H
/*----includes------*/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ecu_motor_cfg.h"

/*------------Macros-----------*/
#define MOTOR_STATUS_ON     0x01U
#define MOTOR_STATUS_OFF    0x00U

/*------Macro_functions---*/

/*-------user data types----*/
typedef struct {
    pinConfig_t dc_motor[2];
}motor_t;
/*-------interfaces prototype-------*/
/**
 * @brief inisialize motor pins and status
 * @param motor pointer to constant @ref motor_t
 * @return 
 *          E_OK = 1 -> done successfully
 *          E_NOT= 0 ->  something goes wrong
 */
Std_ReturnType ecu_motor_inisialize(const motor_t * motor);
/**
 * @brief turn motor to left
 * @param motor pointer to constant @ref motor_t
 * @return 
 *          E_OK = 1 -> done successfully
 *          E_NOT= 0 ->  something goes wrong
 */
Std_ReturnType ecu_motor_turn_left(const motor_t * motor);
/**
 * @brief turn motor to right
 * @param motor pointer to constant @ref motor_t
 * @return 
 *          E_OK = 1 -> done successfully
 *          E_NOT= 0 ->  something goes wrong
 */
Std_ReturnType ecu_motor_turn_right(const motor_t * motor);
/**
 * @brief stop moving the motor
 * @param motor pointer to constant @ref motor_t
 * @return 
 *          E_OK = 1 -> done successfully
 *          E_NOT= 0 ->  something goes wrong
 */
Std_ReturnType ecu_motor_stop(const motor_t * motor);

#endif	/* ECU_MOTOR_H */

