/* 
 * File:   ecu_7_segment.h
 * Author: yossef
 *
 * Created on February 16, 2023, 12:57 AM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H
/*------includes-----------*/
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "cfg_7_segment.h"


/*----------macros----------*/
#define SEG_DECODER_A   0
#define SEG_DECODER_B   1
#define SEG_DECODER_C   2
#define SEG_DECODER_D   3

/*-------macro Functions-----*/

/*--------user Data types-------*/
typedef enum {
    SEG_COMMON_ANODE,
            SEG_COMMON_CATHOD
}segment_type_t;

typedef struct{
    pinConfig_t seg_decoder_pins[4];
    segment_type_t seg_stat;
}segment_t;
/*--------interfaces prototype---*/
Std_ReturnType ecu_seg_inisialize(const segment_t * seg);
Std_ReturnType ecu_seg_write_number(const segment_t * seg , uint8_t num);
#endif	/* ECU_7_SEGMENT_H */

