/* 
 * File:   SPI.h
 * Author: yosse
 *
 * Created on October 4, 2023, 2:13 AM
 */

#ifndef SPI_H
#define	SPI_H
/*--------------Includes----------------*/
#include "SPI_cfg.h"
#include "../GPIO/HAL_GPIO.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_interrupt_cfg.h"
#include "../interrupt/internal_interrupt/mcal_internal_interrupt.h"
#include"../../../../MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8/pic/include/proc/pic18f4620.h"
/*-------------MACROS-------------*/
#define SPI_INPUT_DATA_SAMBLED_END         ((uint8_t)0x01)
#define SPI_INPUT_DATA_SAMBLED_MIDDLE      ((uint8_t)0x00)


#define SPI_RECIVED_COMPLETE                    ((uint8_t)0x01)
#define SPI_RECIVED_NOT_COMPLETE                ((uint8_t)0x00)

#define SPI_WRITE_COLLISION_OCCUR                   ((uint8_t)0x01)
#define SPI_WRITE_COLLISION_NOT_OCCUR               ((uint8_t)0x01)


#define SPI_CKP_IDLE_LOW                    ((uint8_t)0x00)
#define SPI_CKP_IDLE_HIGH                    ((uint8_t)0x01)


#define SPI_CKE_TRANSMIT_LEADING_EDGE       ((uint8_t)0x00)
#define SPI_CKE_TRANSMIT_TRAILING_EDGE      ((uint8_t)0x01)
/*-------------Functions like Macro-------------*/
/*
 *  use it to check BUFFER STAT IN receive mode only!!
 * if return SPI_RECIVED_COMPLETE -> data is completeled received
 * return SPI_RECIVED_NOT_COMPLETE -> buffer is empty
 */
#define SPI_BUFFER_STATUS()             (SSPSTATbits.BF)

/*
     return SPI_WRITE_COLLISION_OCCUR if buffer is written while  transmisting data
 
 *  return SPI_WRITE_COLLISION_NOT_OCCUR  -> NO COLLISION ERROR
 */
#define SPI_WRITE_COLLISION_CHECK()     (SSPCON1bits.WCOL)

#define SPI_WRITE_COLLISION_CLEAR()     (SSPCON1bits.WCOL = 0)

#define SPI_ENABLE()                    (SSPCON1bits.SSPEN = 1)
#define SPI_DISABLE()                   (SSPCON1bits.SSPEN = 0)


/*
 * Parameters:  options
 *              SPI_CKP_IDLE_LOW
 *              SPI_CKP_IDLE_HIGH
 *      
 */
#define SPI_CLK_POLARIY_SELECT(_SPI_CLK_POLARITY_t) (SSPCON1bits.CKP = _SPI_CLK_POLARITY_t)

/**
 parameter: @ref SPI_Modes_Cfg_t
 */
#define SPI_MODE_SELECT(_SPI_MODE)      (SSPCON1bits.SSPM = _SPI_MODE )

/*
 Parameter options:
 *                  SPI_INPUT_DATA_SAMBLED_END
 *                  SPI_INPUT_DATA_SAMBLED_MIDDLE    
 */
#define SPI_SAMPLE_MODE_SELECT(_MODE)          (SSPSTATbits.SMP = _MODE)

/*
 * options:  
 *          SPI_CKE_TRANSMIT_LEADING_EDGE
 *          SPI_CKE_TRANSMIT_TRAILING_EDGE
 */
#define SPI_CKE_SELECT(_CKE_MODE)               (SSPSTATbits.CKE = _CKE_MODE)

/*-------------User data types-----------------*/

typedef void (*SPI_InterruptHandler_t)(void) ;

typedef enum {
    SPI_MASTER_MODE_FOSC_DIV_4 = 0,
            SPI_MASTER_MODE_FOSC_DIV_16,
            SPI_MASTER_MODE_FOSC_DIV_64,
            SPI_MASTER_MODE_CLK_TMR2_DIV_2,
            SPI_SLAVE_MODE_SS_ENABLE,
            SPI_SLAVE_MODE_SS_DISABLE
}SPI_Modes_Cfg_t;


typedef struct {
#if SPI_MODE == SPI_MASTER_MODE && SPI_SS_MODE == SPI_SS_ENABLE && SPI_NUMBER_OF_SLAVES != 0
    pinConfig_t SlaveSelect_pins[SPI_NUMBER_OF_SLAVES]; /*must be configure as output and init logic high*/
#endif
    SPI_Modes_Cfg_t spi_mode; /* @ref  SPI_Modes_Cfg_t*/
    /*
     * options
                SPI_CKP_IDLE_LOW
     *          SPI_CKP_IDLE_HIGH
     */
    uint8_t spi_clk_polarity : 1;
/*
 * options:  
 *          SPI_CKE_TRANSMIT_LEADING_EDGE
 *          SPI_CKE_TRANSMIT_TRAILING_EDGE
     * !!!!!IMPORTANT NOTE:
     *              if spi used in slave mode with CKE TRAILING EDGE
 *                  then must use SPI_SLAVE_MODE_SS_ENABLE in spi mode
 *                  SS pin must be used!!!
 * */
    uint8_t spi_clk_select : 1;
/*
 * options:
 *                  SPI_INPUT_DATA_SAMBLED_END
 *                  SPI_INPUT_DATA_SAMBLED_MIDDLE    */
    uint8_t spi_sample_mode : 1; /*ignore if you operate in slave mode*/
#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    SPI_InterruptHandler_t spi_pFunc_cbf;
#endif
}SPI_cfg_t;

/*-----------------interfaces Prototypes----------*/

/**
 * @Brief Initialize spi moduel
 * @param _spi_cfg @SPI_cfg_t spi configureation and dont forget to check SPI_cfg.h
 * @return  
 *          E_OK -> 1 done successfully
 *          E_NOT -> 0 Error
 */
Std_ReturnType SPI_init(const SPI_cfg_t* _spi_cfg);
Std_ReturnType SPI_deInit(void);

/**
 * 
 * @brief function select slave and transmit data and Wait "Blocking" till data is recived and return data in pointer to @uint8_t
 * 
 * 
 * @param Transmit_data @uint8_t data to transmit
 * @param Rec_data      p@uint8_t  pointer to receive data
 * @param slaveNumber  @pinConfig_t  SlaveSelectPin -> slave select pin 
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Transceive_SlaveSelect(const uint8_t Transmit_data , uint8_t* Rec_data , const pinConfig_t* SlaveSelectPin);

/**
 * @brief  transmit data and Wait "Blocking" till data is recived and return data in pointer to @uint8_t
 * @param Transmit_data @uint8_t data to transmit
 * @param Rec_data p@uint8_t  pointer to receive data
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Transceive(const uint8_t Transmit_data , uint8_t* Rec_data);

/**
 * @brief function transmit string and recive string 
 * @param Transmit_data  p@uint8_t string to transmit
 * @param Transmit_arrLen @uint8_t Transmit_data array size include the null terminator
 * @param Rec_data p@uint8_t pointer to string to return recived data
 * @return 
 */
Std_ReturnType SPI_Transceive_string(uint8_t* Transmit_data ,uint8_t Transmit_arrLen  ,uint8_t* Rec_data);

/**
 * @brief transmit data and do temporary read to clear buffer flag
 *          
 * @param Transmit_data @uint8_t data to transmit
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Transmit(const uint8_t Transmit_data);

/**
 * @brief transmit string  function stop when reach transArr_len or reach after send null terminator
 * @param Transmit_data p@uint8_t arra of chars to be transmit
 * @param transArr_len @uint8_t Transmit_data array size include the null terminator
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Transmit_string(uint8_t* Transmit_data , uint8_t transArr_len);

/**
 *          MUST USE WITH THE MASTER ONLY!!
 * @brief  transmit data with slave select 
 * @param  Transmit_data @uint8_t data to transmit
 * @param SlaveSelectPin @pinConfig_t  Slave Select Pin @ref pinConfig_t @ref SPI_cfg_t
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Transmit_SlaveSelect(const uint8_t Transmit_data , const pinConfig_t* SlaveSelectPin);

/**
 *          MUST USE WITH THE MASTER ONLY!!
 * @brief transmit String with slave select 
 *        function stop when reach transArr_len or  after send null terminator
 * @param Transmit_data p@uint8_t string to transmit 
 * @param transArr_len @uint8_t Transmit_data array size include the null terminator
 * @param SlaveSelectPin  @pinConfig_t  Slave Select Pin @ref pinConfig_t @ref SPI_cfg_t
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully 
 */
Std_ReturnType SPI_TransmitString_SlaveSelect(const uint8_t* Transmit_data ,uint8_t transArr_len , const pinConfig_t* SlaveSelectPin);

/**
 * @note:
 *          MUST USE IT WITH MASTER ONLY cause its do temporary write to start clock
 * @brief start communication and recive data
 * @param Rec_data @puint8_t pointer to return recived data
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Master_Recieve( uint8_t* Rec_data);

/**
 * @note:
 *          MUST USE IT WITH SLAVE ONLY cause  there is no temporary write to start clock
 * @brief start communication and recive data
 * @param Rec_data @puint8_t pointer to return recived data
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Slave_Recieve( uint8_t* Rec_data);

/**
 * @note:
 *          MUST USE IT WITH SLAVE ONLY cause  there is no temporary write to start clock
 * @brief recived string function stop when transmiter send null terminator or when trasmiter send string size equal to Rec_dataSize
 * @param Rec_data p@uint8_t string to return recived data
 * @param Rec_dataSize @uint8_t Rec_data array size include null ternminator
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Slave_RecieveString( uint8_t* Rec_data , uint8_t Rec_dataSize);

/**
 * @note:
 *          MUST USE IT WITH MASTER ONLY cause its do temporary write to start clock
 * @brief start communication and slave select and recive data
 * @param Rec_data p@uint8_t pointer to return recived data
 * @param SlaveSelectPin @pinConfig_t  Slave Select Pin @ref pinConfig_t @ref SPI_cfg_t
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Master_Recieve_SlaveSelect( uint8_t* Rec_data ,  const pinConfig_t* SlaveSelectPin);
/**
 * @note:
 *          MUST USE IT WITH MASTER ONLY cause its do temporary write to start clock
 *          and function stop when transmiter send null terminator or send string size equal to Rec_dataArrSize
 * @brief start communication and slave select and recive string 
 * @param Rec_data p@uint8_t array to return recived string
 * @param Rec_dataArrSize @uint8_t Rec_data array size include null ternminator
 * @param SlaveSelectPin @pinConfig_t  Slave Select Pin @ref pinConfig_t @ref SPI_cfg_t
 * @return 
 *          E_NOT - > 0 if function didnt done successfully
 *          E_OK - > 1 if function done successfully
 */
Std_ReturnType SPI_Master_RecieveString_SlaveSelect( uint8_t* Rec_data, uint8_t Rec_dataArrSize ,   const pinConfig_t* SlaveSelectPin);
#endif	/* SPI_H */

