/* 
 * File:   mcal_std_types.h
 * Author: yossef
 *
 * Created on January 30, 2023, 11:43 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/*----------------includes--------------------*/
#include"std_lib.h"
#include"compiler.h"

/*-----------------macros----------------------*/
#define  E_OK       ((Std_ReturnType)0x01)
#define E_NOT       ((Std_ReturnType)0x00)

#define STD_HIGH    ((uint8_t)0x01)
#define STD_LOW     ((uint8_t)0x00)

#define STD_ON      ((uint8_t)0x01)
#define STD_OFF     ((uint8_t)0x00)

/*-----------------func macro-------------------*/

/*----------------data type declarition----------*/
typedef uint8_t Std_ReturnType;

/*--structs and enums--*/


/*---------------function prototype----------------*/


#endif	/* MCAL_STD_TYPES_H */

