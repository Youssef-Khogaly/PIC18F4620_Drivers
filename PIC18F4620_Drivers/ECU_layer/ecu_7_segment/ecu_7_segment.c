/* 
 * File:   ecu_7_segment.c
 * Author: yossef
 *
 * Created on February 16, 2023, 12:57 AM
 */
#include "ecu_7_segment.h"
/*--------Static_Fucntions---------*/
/* 9/2 = 4 , 1
 4/2 = 2 , 0
 2/2 = 1 , 0
 1/2 = 0 , 1*/
/*------------------------------------*/
Std_ReturnType ecu_seg_inisialize(const segment_t * seg){
  Std_ReturnType ret = E_OK;
  uint8_t count = 0;
  if(!(seg))
    ret = E_NOT;
  else
    {
        for(count = SEG_DECODER_A ; (count <= SEG_DECODER_D) && (ret == E_OK) ; count++)
                ret = gpio_pin_intialize (&(seg->seg_decoder_pins[count]));
    }
  return ret;
}
Std_ReturnType ecu_seg_write_number(const segment_t * seg ,uint8_t num){
  Std_ReturnType ret = E_OK;
  uint8_t count = 0;
  if(!(seg) ||  num > 9)
    ret = E_NOT;
  else
    {
      switch(seg->seg_stat)
        {
        case SEG_COMMON_ANODE:
          for(count = SEG_DECODER_A ; count <= SEG_DECODER_D && ret == E_OK ; count++)
                ret = gpio_pin_write_logic (&(seg->seg_decoder_pins[count]) , !(BIT_READ(num , count)));
          break;
        case SEG_COMMON_CATHOD:
            for(count = SEG_DECODER_A ; count <= SEG_DECODER_D && ret == E_OK ; count++)
                ret = gpio_pin_write_logic (&(seg->seg_decoder_pins[count]) , (BIT_READ(num , count)));
          break;
        default: ret = E_NOT ;
        }
    }
  return ret;
}