/* 
 * File:   I2C.h
 * Author: yosse
 *
 * Created on October 8, 2023, 6:54 AM
 */

#ifndef I2C_H
#define	I2C_H

/* ---------------- Includes ----------------*/
#include "I2C_cfg.h"
#include "../GPIO/HAL_GPIO.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_interrupt_cfg.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
#include"../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"

/* --------------------- Macros ----------------*/

/* SLEW RATE */
#define I2C_SLEW_RATE_DISABLE       1U
#define I2C_SLEW_RATE_ENABLE        0U

/* SMBUS */
#define I2C_SMBUS_ENABLE             1U
#define I2C_SMBUS_DISABLE            0U

/* I2C Mode*/
#define I2C_SLAVE_MODE_10BIT_ADDRESS_INTERRUPT_ENABLE           (uint8_t)0x0F
#define I2C_SLAVE_MODE_7BIT_ADDRESS_INTERRUPT_ENABLE            (uint8_t)0x0E
#define I2C_MASTER_MODE_DEFINED_CLK                             0x08
#define I2C_SLAVE_MODE_10BIT_ADDRESS                            (uint8_t)0x07
#define I2C_SLAVE_MODE_7BIT_ADDRESS                             (uint8_t)0x06

/* General Call "SLAVE MODE ONLY"*/
#define I2C_SLAVE_MODE_GENERAL_CALL_ENABLE                 1U
#define I2C_SLAVE_MODE_GENERAL_CALL_DISABLE                0U

/* Recieve enable and disable "MASTER MODE ONLY "*/
#define I2C_MASTER_MODE_RECEIVE_ENABLE                      1U
#define I2C_MASTER_MODE_RECEIVE_DISABLE                     0U

/* Stop Bit*/
#define I2C_STOP_BIT_DETECTED                               1U
#define I2C_STOP_BIT_NOT_DETECTED                           0U

/* Start Bit*/
#define I2C_START_BIT_DETECTED                              1U
#define I2C_START_BIT_NOT_DETECTED                          0U

/* buffer status*/  
#define I2C_BF_STAT_FULL                                     1U
#define I2C_BF_STAT_EMPTY                                    0U

/* Write collision status */
#define I2C_WRITE_COLLISION_DETECTED                         1U
#define I2C_WRITE_COLLISION_NOT_DETECTED                     0U

/* Receive Overflow STATUS */
#define I2C_RECEIVE_OV_DETECTED                             1U
#define I2C_RECEIVE_OV_NOT_DETECTED                         0U

/* Clock stretch*/
#define I2C_SLAVE_MODE_CLK_STRETCH_ENABLE                    1U
#define I2C_SLAVE_MODE_CLK_STRETCH_DISABLE                   0U

/* ACK Trasmitter */
#define I2C_TRASMITER_ACK_RECEIVED                                   0U
#define I2C_TRASMITER_ACK_NOT_RECEIVED                               1U

/* ACK RECEIVER */
#define I2C_RECEIVER_ACK_TRASNMIT                                   0U
#define I2C_RECEIVER_NACK_TRASNMIT                                   1U


/* Slave Read/Write Information bit */
#define I2C_SLAVE_WRITE_BIT                 0U
#define I2C_SLAVE_READ_BIT                  1U

/* SLAVE Data/Address bit */
#define I2C_SLAVE_REC_BYTE_ADD              0U
#define I2C_SLAVE_REC_BYTE_DATA             1U
/* -------------------- Macro Functions -------------------*/

/*SLEW RATE*/
#define I2C_SLEW_RATE_ENABLE_CFG()              (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_DISABLE_CFG()              (SSPSTATbits.SMP = 0)

/* SMBUS */
#define I2C_SM_BUS_ENABLE_CFG()                     (SSPSTATbits.CKE = 1)
#define I2C_SM_BUS_DISABLE_CFG()                    (SSPSTATbits.CKE = 0)

/* stop bit check
 * return I2C_STOP_BIT_DETECTED
 *        I2C_STOP_BIT_NOT_DETECTED  
 */
#define I2C_STOP_BIT_CHECK_CFG()            (SSPSTATbits.P)

/* start bit check
 * return I2C_START_BIT_DETECTED
 *        I2C_START_BIT_NOT_DETECTED  
 */
#define I2C_START_BIT_CHECK_CFG()            ( SSPSTATbits.S )

/* Buffer check
 * return: I2C_BF_STAT_FULL
 *         I2C_BF_STAT_EMPTY
 */
#define I2C_BUFFER_STAT_CFG()               (SSPSTATbits.BF)


/* Write collision check
 * return: I2C_WRITE_COLLISION_DETECTED
 *         I2C_WRITE_COLLISION_NOT_DETECTED
 */
#define I2C_WRITE_COLLISION_CHECK_CFG()         (SSPCON1bits.WCOL)
#define I2C_WRITE_COLLISION_CLEAR_CFG()         (SSPCON1bits.WCOL = 0)
/* Receive Over Flow Check
 * return : I2C_RECEIVE_OV_DETECTED
 *          I2C_RECEIVE_OV_NOT_DETECTED
 */
#define I2C_RECEIVE_OV_CHECK_CFG()              (SSPCON1bits.SSPOV)
#define I2C_RECEIVE_OV_CLEAR_CFG()              (SSPCON1bits.SSPOV = 0)

/*
 *  enable and disable Master Synchronous Serial Port
 */
#define I2C_MSSP_ENABLE_CFG()                   (SSPCON1bits.SSPEN = 1)
#define I2C_MSSP_DISABLE_CFG()                   (SSPCON1bits.SSPEN = 0)

/**
 * I2C_SLAVE_SCK_RELEASE_CFG:
 *@brief: SLAVE RELASE CLOCK LINE: "Write Logic 1 to CLOCK LINE"
 */
#define I2C_SLAVE_SCK_RELEASE_CFG()             (SSPCON1bits.CKP = 1)
/*
 * I2C_SLAVE_SCK_HOLD_CFG:
 * @brief: SLAVE Hold Clock line " Write logic 0 to clock line " (Clock Stretch)
 *         used to ensure data setup time
 */
#define I2C_SLAVE_SCK_HOLD_CFG()                (SSPCON1bits.CKP = 0)

/* General call used in slave mode only */
#define I2C_GENERAL_CALL_ENABLE_CFG()           (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE_CFG()          (SSPCON2bits.GCEN = 0)

/* Receive enable/disable only in master mode */
#define I2C_RECEIVE_ENABLE_CFG()                (SSPCON2bits.RCEN = 1)
#define I2C_RECEIVE_DISABLE_CFG()               (SSPCON2bits.RCEN = 0)

/* enable/disable clock stretching  use it in SLAVE MODE ONLY !!*/
#define I2C_SLAVE_CLK_STRETCH_ENABLE_CFG()          (SSPCON2bits.SEN = 1)
#define I2C_SLAVE_CLK_STRETCH_DISABLE_CFG()         (SSPCON2bits.SEN = 0)

/* MASTER Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware. */
#define I2C_MASTER_START_CONDITION()        ( SSPCON2bits.SEN = 1 )

/* MASTER Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware */
#define I2C_MASTER_STOP_CONDITION()         (SSPCON2bits.PEN = 1)

/* MASTER Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
#define I2C_MASTER_REPEATED_START()         (SSPCON2bits.RSEN = 1)

/* SLave Data/Address bit Check
 * @return:  I2C_SLAVE_REC_BYTE_ADD -> received byte was address
 *          I2C_SLAVE_REC_BYTE_DATA -> received byte was data
 */
#define I2C_SLAVE_REC_BYTE_CHECK_CFG()          (SSPSTATbits.D_nA)

/* SLAVE Read/Write Information bit Check
 * @return : I2C_SLAVE_WRITE_BIT -> slave received write bit / master want to write data
 *           I2C_SLAVE_READ_BIT -> slave received read bit/ master want to read data 
 */
#define I2C_SLAVE_READ_WRITE_CHECK_CFG()          (SSPSTATbits.R_nW)
/* ---------------- User Data Types ----------------- */
typedef void (*i2c_pFunc_CBF_t)(void);
typedef struct {
    uint8_t i2c_mode;
    uint8_t i2c_SlewRate :1;
    uint8_t i2c_SMBUS   :1;
    uint8_t i2c_general_call : 1; /*ignore it if you are operateing in master mode*/
    uint8_t i2c_clk_stretch : 1; /*ignore it if you are operateing in master mode*/
    uint8_t i2c_receive_mode : 4; /*ignore it if you are operating in slave mode*/
}i2c_cfg_t;

typedef struct {
    i2c_cfg_t i2c_cfg;
    /*
     * in Master Mode:  @uint32_t Master clock freq
     * in Slave Mode : Slave Address  (7 bit address or 9 bit address max)
     */
    uint32_t i2c_MasterClock_SlaveAddress;
    i2c_pFunc_CBF_t I2C_Report_writeCollision; /* write collision handler pointer to function  , must init with null if dont need it */
    i2c_pFunc_CBF_t I2C_Report_Receive_OverFlow; /* Receive overFlow handler pointer to function  , must init with null if dont need it */
    
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    i2c_pFunc_CBF_t I2C_DefaultInterruptHandler; /*Default interrupt handler pointer to function */
#endif
    
#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    i2c_pFunc_CBF_t I2C_BUSCollision_Handler; 
#endif
}i2c_t;
/* ----------------- Software Prototypes --------------*/

Std_ReturnType i2c_init(const i2c_t* _i2c_config);
Std_ReturnType i2c_Deinit(const i2c_t* _i2c_config);
Std_ReturnType i2c_Master_SendStart(void);
Std_ReturnType i2c_Master_Send_RepeatedStart(void);
Std_ReturnType i2c_Master_SendStop(void);
Std_ReturnType i2c_Master_WriteByte_Blocking(uint8_t Data , uint8_t* _Ret_ACK);
Std_ReturnType i2c_Master_ReadByte_Blocking(uint8_t* Rec_Data , uint8_t Send_ACK);

/**
 * 
 * @brief:
 *          read data from master
 * @note: !! if data that trasmited from master was address it will dummy read to clear the buffer will not change @uint8_t* RecData
 * 
 * @param RecData: p@uint8_t return received data
 * @return 
 */
Std_ReturnType i2c_Slave_ReadData_Polling(uint8_t* RecData);
Std_ReturnType i2c_Slave_WriteData_Polling(uint8_t RecData);
#endif	/* I2C_H */

