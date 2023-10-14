/* 
 * File:   hal_usart.h
 * Author: yosse
 *
 * Created on September 17, 2023, 8:15 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/**********Includes****************/
#include "../mcal_std_types.h"
#include "../GPIO/HAL_GPIO.h"
#include "../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
#include "hal_usart_cfg.h"

/**************MACROS***************/

// eusart mode
#define EUSART_SYNC_MODE        0
#define EUSART_ASYNC_MODE       1

//EUSART Baudrate speed Mode
#define EUSART_ASYNC_LOW_SPEED       0
#define EUSART_ASYNC_HIGH_SPEED      1


// TRASMIT MACROS
#define EUSART_ASYNC_TX_DISABLE                  0
#define EUSART_ASYNC_TX_ENABLE                   1

#define EUSART_ASYNC_TX_INTERRUPT_DISABLE        0
#define EUSART_ASYNC_TX_INTERRUPT_ENABLE         1

#define EUSART_ASYNC_9BIT_TX_DISABLE            0
#define EUSART_ASYNC_9BIT_TX_ENABLE             1
        
// RX MACROS
#define EUSART_ASYNC_RX_DISABLE                 0
#define EUSART_ASYNC_RX_ENABLE                  1

#define EUSART_ASYNC_RX_INTERRUPT_DISABLE       0
#define EUSART_ASYNC_RX_INTERRUPT_ENABLE        1

#define EUSART_ASYNC_9BIT_RX_DISABLE            0
#define EUSART_ASYNC_9BIT_RX_ENABLE             1      

#define EUSART_FRAMING_ERROR_DETECTED           1
#define EUSART_FRAMING_ERROR_CLEARED            0

#define EUSART_OVERRUN_ERROR_DETECTED           1
#define EUSART_OVERRUN_ERROR_CLEARED            0


/********Function Like Macro *******/

#define EUSART_ENABLE()         (RCSTAbits.SPEN = 1)
#define EUSART_DISABLE()        (RCSTAbits.SPEN = 0)

/***********User Data Types*********/

typedef void (*eusart_pfunc_CBF_t)(void);

typedef enum {
    BAUDRATE_ASYNC_8BIT_LOW_SPEED = 0,
            BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
            BAUDRATE_ASYNC_16BIT_LOW_SPEED,
            BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
            BAUDRATE_SYNC_8BIT,
            BAUDRATE_SYNC_16BIT = 6
}eusart_baudrate_gen_t;

typedef union {
    struct {
        uint8_t reserved:6;
        uint8_t usart_ferr : 1; /* @ frame error detection bit*/
        uint8_t usart_oerr : 1; /*@ over run error bit*/
    };
    uint8_t status;
}eusart_error_stat_t;

typedef struct {
    uint8_t eusart_rx_enable:1;
    uint8_t eusart_rx_9bit_enable:1;
    uint8_t reserved : 6;
}eusart_rx_cfg_t;

typedef struct {
    uint8_t eusart_tx_enable:1; 
    uint8_t eusart_tx_9bit_enable:1;
    uint8_t reserved : 6;
}eusart_tx_cfg_t;

typedef struct {
    uint32_t baudrate;
    eusart_baudrate_gen_t baudrate_cfg;
    eusart_tx_cfg_t eusart_tx_cfg;
    eusart_rx_cfg_t eusart_rx_cfg;
    eusart_error_stat_t error_stat;
    
    
    // call back function for interrupt
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    eusart_pfunc_CBF_t  EUSART_Tx_InterruptHandler;              
#endif
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    eusart_pfunc_CBF_t  EUSART_Rx_InterruptHandler;
    eusart_pfunc_CBF_t  EUSART_FrameError_InterruptHandler;      /*  !! MUST BE init with NULL if u dont need cbf    */
    eusart_pfunc_CBF_t  EUSART_OverRunError_InterruptHandler;    /*  !! MUST BE init with NULL if u dont need cbf    */
#endif

}eusart_cfg_t;


/**********interfaces Prototypes******/


Std_ReturnType EUSART_Async_Init(const eusart_cfg_t *_eusart);
Std_ReturnType EUSART_Async_Deinit(const eusart_cfg_t *_eusart);
Std_ReturnType EUSART_WriteByte_Blocking(uint8_t data);
Std_ReturnType EUSART_WriteStr_Blocking(uint8_t* data);

Std_ReturnType EUSART_ReadByte_Blocking( uint8_t* _data);

/**
 * 
 * @param data
 * @return 
 *          @E_NOT  if data not send  TXREG IS FULL
 *          @E_OK  if data send 
 */
Std_ReturnType EUSART_WriteByte_polling(uint8_t data);
Std_ReturnType EUSART_WriteStr_polling(uint8_t* data);
/**
 * 
 * @param data
 * @return 
 *          @E_NOT  if no data received
 *          @E_OK  if data reveived 
 */
Std_ReturnType EUSART_ReadByte_polling(uint8_t* data);

#endif	/* HAL_USART_H */

