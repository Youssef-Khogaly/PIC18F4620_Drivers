/* 
 * File:   HAL_GPIO.h
 * Author: yosse
 *
 * Created on January 30, 2023, 11:26 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/*--------------incudes------------------*/
#include"../mcal_std_types.h"
#include"../DeviceConfig/DeviceConfig.h"
#include"../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
/*---------------macros*-----------------*/


/*--------------funcMACROS---------------*/
#define HWREG8(REG_ADD)      (*((volatile uint8 *)(REG_ADD)))
#define BIT_MASK(BIT_POS)       ((uint8_t)(1<<BIT_POS))
#define BIT_SET(REG ,POS)       (REG |= BIT_MASK(POS))
#define BIT_CLEAR(REG,POS)      (REG &= (~(BIT_MASK(POS))))
#define BIT_TOGGLE(REG,POS)     (REG ^= (BIT_MASK(POS)))
#define BIT_READ(REG,POS)       ((REG >> POS) & (uint8_t)0x01)
#define PORT_TOGGLE(REG)        (REG = ~REG)
#define PORT_SET(REG)           (REG = 0xFF)
#define PORT_CLEAR(REG)         (REG = 0x00)
/*--------------Data Type declarition----------------*/
typedef enum{
    low = 0,
    high
}logic_t;
typedef enum{
    output,input
}direction_t;
typedef enum{
            pin0,
            pin1,
            pin2,
            pin3,
            pin4,
            pin5,
            pin6,
            pin7
}pinIndex_t;
typedef enum{
    PORTA_INDEX,
            PORTB_INDEX,
            PORTC_INDEX,
            PORTD_INDEX,
            PORTE_INDEX,
}PortIndex_t;
typedef struct{
    uint8_t port : 3 ;
    uint8_t pinIndex : 3 ;
    uint8_t direction :1;
    uint8_t logic :1;
}pinConfig_t;
/*--------------function declarition-----------------*/
/**
 * inistialize the direction (input/output) of the pin
 * @param pinCon pointer to @ref pinConfig_t
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_pin_direction_intialize( const pinConfig_t* pinCon);
/**
 * get the direction of the pin
 * @param pinCon pointer to @ref pinConfig_t
 * @param dir_status pointer to @ref direction_t to return the direction of the pin
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_pin_get_direction(const pinConfig_t* pinConfig ,direction_t* dir_status);
/**
 * write logic on pin
 * @param pinCon pointer to @ref pinConfig_t
 * @param logic : the logic that user wanna to write it
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_pin_write_logic( const pinConfig_t* pinConfig ,logic_t logic);
/**
 * read a logic on a pin
 * @param pinCon pointer to @ref pinConfig_t
 * @param ret_logic pointer to @ref logic_t  to return the logic
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_pin_read_logic(const pinConfig_t* pinConfig ,logic_t* ret_logic);
/**
 * toggle a logic on a pin
 * @param pinCon pointer to @ref pinConfig_t
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_pin_toggle_logic( pinConfig_t* pinConfig);
/**
 * intialize the direction and the logic on a pin
 * @param pinCon pointer to @ref pinConfig_t
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_pin_intialize( const pinConfig_t* pinCon);

/*--------------------------------------------------------------*/

/**
 * intialize the direction of the port
 * @param port  @ref PortIndex_t
 * @param dir the direction that user wanna to write it
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_port_direction_intialize( const PortIndex_t port , uint8_t dir);
/**
 * read direction of port
 * @param port  @ref PortIndex_t
 * @param dir_status pointer to uint8_t to return the direction of port
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_port_get_direction_stat(const PortIndex_t port , uint8_t* dir_status);
/**
 * write logic on port
 * @param port  @ref PortIndex_t
 * @param logic : logic  to write it 
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_port_write_logic(const PortIndex_t port ,uint8_t logic);
/**
 * read logic on port
 * @param port  @ref PortIndex_t
 * @param ret_logic: pointer to uint8 to return logic value 
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_port_read_logic(const PortIndex_t port ,uint8_t *ret_logic);
/**
 * toggle logic on port
 * @param port  @ref PortIndex_t
 * @return  E_OK = 1 if done successfully
 *          E_NOT = 0 if not done successfully
 */
Std_ReturnType gpio_port_toggle_logic(const PortIndex_t port);

#endif	/* HAL_GPIO_H */

