/* 
 * File:   Hal_EEPROM.h
 * Author: yossef
 *
 * Created on April 14, 2023, 7:33 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*includes*/
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"
#include "../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
/*---------*/
/*Macro-Def*/
#define ACCESS_FLASH_PROGRAM_MEMORY     1
#define ACCESS_DATA_EEPROM_MEMORY       0
#define ACCESS_CONF_REG                 1
#define ACCESS_FLASH_EEPROM_MEMORY      0
#define ALLOW_WRITE_CYCLE_FLASH_EEPROM      1
#define DISABLE_WRITE_CYCLE_FLASH_EEPROM    0
#define INITIATES_WRITE       1
#define WRITE_COMPELET        0
#define INITIATES_READ        1




/*-------*/
/*Macro-Func*/
#define EEPROM_SET_H_ADD(ADD)           (EEADRH = (uint8_t)((ADD>>8)&0x03))
#define EEPROM_SET_LOW_ADD(ADD)         (EEADR = (uint8_t)(ADD & 0xFF))


/*---------*/
/*User-DataTypes*/

/*---------*/
/*Software interfaces prototype*/
Std_ReturnType EEPROM_writeByte(uint8_t Bdata , uint16_t addr);
Std_ReturnType EEPROM_readByte(uint8_t* ret_Bdata , uint16_t addr);
#endif	/* HAL_EEPROM_H */

