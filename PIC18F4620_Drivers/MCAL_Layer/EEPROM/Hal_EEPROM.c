/* 
 * File:   HAL_GPIO.c
 * Author: yossef
 *
 * Created on January 30, 2023, 11:26 PM
 */
#include "Hal_EEPROM.h"

/*-----------Global-Varaibles---------*/
/*------Static Helper Function------*/

/*-------Software interfaces Def-----*/
Std_ReturnType EEPROM_readByte(uint8_t* ret_Bdata , uint16_t addr)
{
  Std_ReturnType ret = E_NOT;
  if(!ret_Bdata)
    ret = E_NOT;
  else
  {
      EEPROM_SET_H_ADD(addr);
      EEPROM_SET_LOW_ADD(addr);
      EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
      EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
      EECON1bits.RD = INITIATES_READ;\
      NOP();
      NOP();
      *ret_Bdata = EEDATA;
      ret = E_OK;
  }
  return ret;
}

Std_ReturnType EEPROM_writeByte(uint8_t Bdata , uint16_t addr){
  Std_ReturnType ret = E_NOT;
  /*Read Interrupt Status*/
    uint8_t GIE_stat = INTCONbits.GIEH;
    
    EEPROM_SET_H_ADD(addr); /*set write address high 2bit*/
    EEPROM_SET_LOW_ADD(addr);    /*set write address lower 8 bit*/
    EEDATA = Bdata; /*write data  in EEDATA reg*/
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY; /*select access eeprom memory*/
    EECON1bits.WREN = ALLOW_WRITE_CYCLE_FLASH_EEPROM ; /*allow write cycle to eeprom or flash*/
    /*Disable - Interrupt*/
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_HIGH_PRIORITY_DISABLE();
#else
    INTERRUPT_DISABLE_UNMASKED();
#endif
    /*---------*/
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1bits.WR = INITIATES_WRITE;
    while(WRITE_COMPELET != EECON1bits.WR); /* wait write to compelete*/
    EECON1bits.WREN = DISABLE_WRITE_CYCLE_FLASH_EEPROM;
    /*Restore - Interrupt stat*/
    INTCONbits.GIEH = GIE_stat;
    /*----*/
    ret = (EECON1bits.WRERR) ? E_NOT : E_OK;
    return ret;
}

/*----Helper Function Def-------*/
