/* 
 * File:   MCAL_INIT.h
 * Author: yossef
 *
 * Created on October 14, 2023, 4:13 PM
 */

#ifndef MCAL_INIT_H
#define	MCAL_INIT_H

#include "mcal_std_types.h"
#include "timer0/hal_timer0.h"
#include "timer1/hal_timer1.h"
#include "timer2/hal_timer2.h"
#include"timer3/hal_timer3.h"
#include "CCP/hal_ccp.h"
#include "EEPROM/Hal_EEPROM.h"
#include "EEPROM/Hal_EEPROM.h"
#include "usart/hal_usart.h"
#include "SPI/SPI.h"
#include "I2C/I2C.h"


Std_ReturnType mcal_init(void);

#endif	/* MCAL_INIT_H */

