#include "I2C.h"

i2c_pFunc_CBF_t static  G_I2C_WirteCollision_Report = NULL;
i2c_pFunc_CBF_t static G_I2C_ReceiveOverFLow_Report_NULL;
i2c_pFunc_CBF_t static G_I2C_MSSP_InterruptHandler = NULL;
i2c_pFunc_CBF_t static G_I2C_BusCollision_InterruptHandler = NULL;

#if (I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE) || (I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE)
static void inline i2c_interrupt_init(const i2c_t* _i2c_config);
#endif
static void inline i2c_Master_config(const i2c_t* _i2c_config);
static void inline i2c_Slave_config(const i2c_t* _i2c_config);
static void inline i2c_gpio_config(void);

Std_ReturnType i2c_init(const i2c_t* _i2c_config)
{
    Std_ReturnType ret = E_NOT;
    if(_i2c_config)
    {
        /* Disable i2c */
        I2C_MSSP_DISABLE_CFG();
        
        if(I2C_MASTER_MODE_DEFINED_CLK == _i2c_config->i2c_cfg.i2c_mode)
        {
            i2c_Master_config(_i2c_config);
        }
        else if (I2C_SLAVE_MODE_7BIT_ADDRESS == _i2c_config->i2c_cfg.i2c_mode || I2C_SLAVE_MODE_10BIT_ADDRESS == _i2c_config->i2c_cfg.i2c_mode || I2C_SLAVE_MODE_7BIT_ADDRESS_INTERRUPT_ENABLE == _i2c_config->i2c_cfg.i2c_mode  || I2C_SLAVE_MODE_10BIT_ADDRESS_INTERRUPT_ENABLE == _i2c_config->i2c_cfg.i2c_mode)
        {
            i2c_Slave_config(_i2c_config);
        }
        else { /* nothing */}
        
        /* Configure GPIO */
        i2c_gpio_config();
        
        /* configure Slew rate*/
        if (I2C_SLEW_RATE_ENABLE == _i2c_config->i2c_cfg.i2c_SlewRate)
        {
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if (I2C_SLEW_RATE_DISABLE == _i2c_config->i2c_cfg.i2c_SlewRate)
        {
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else { /* empty*/}
        
        /* configure SM bus  */
        if (I2C_SMBUS_ENABLE == _i2c_config->i2c_cfg.i2c_SMBUS)
        {
            I2C_SM_BUS_ENABLE_CFG();
        }
        else if (I2C_SMBUS_DISABLE == _i2c_config->i2c_cfg.i2c_SMBUS)
        {
            I2C_SM_BUS_DISABLE_CFG();
        }
        else { /* empty*/}
        
        /* Clear write collision flag */
        I2C_WRITE_COLLISION_CLEAR_CFG();
        
        /* Clear Receive over flow flag */
        I2C_RECEIVE_OV_CLEAR_CFG();
        
        /* configure interrupt */
#if (I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE) || (I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE)
        i2c_interrupt_init(_i2c_config);
#endif
        /* enable i2c */
        I2C_MSSP_ENABLE_CFG();
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    
    return ret;
}


Std_ReturnType i2c_Deinit(const i2c_t* _i2c_config)
{
    Std_ReturnType ret = E_NOT;
    if(_i2c_config)
    {
        /* Disable i2c */
        I2C_MSSP_DISABLE_CFG();
#if (I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE)
      I2C_MSSP_INTERRUPT_DISABLE();
#endif
#if (I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE)
      I2C_BUS_COLLISION_INTERRUPT_DISABLE();
#endif
      
      ret = E_OK;
    }
    else{
        
    }
    return ret;
}



Std_ReturnType i2c_Master_SendStart(void)
{
    Std_ReturnType ret = E_NOT;
    
        I2C_MASTER_START_CONDITION();

        /* Wait start condition to finish */
        while(SSPCON2bits.SEN)
            ;
        
        /* clear flag */
        PIR1bits.SSPIF = 0;
        
        if( I2C_START_BIT_CHECK_CFG() == I2C_START_BIT_DETECTED )
        {
            /* indicate that start bit has beed detected*/
            ret = E_OK;
        }
        else
        {
            /* indicate that start bit was not  detected last */
            ret = E_NOT;
        }  
    return ret;
}
Std_ReturnType i2c_Master_Send_RepeatedStart(void)
{
    Std_ReturnType ret = E_NOT;
    
        I2C_MASTER_REPEATED_START();

        /* Wait Re start condition to finish */
        while(SSPCON2bits.RSEN)
            ;
        
        /* clear flag */
        PIR1bits.SSPIF = 0;
        
        if( I2C_START_BIT_CHECK_CFG() == I2C_START_BIT_DETECTED )
        {
            /* indicate that start bit has beed detected*/
            ret = E_OK;
        }
        else
        {
            /* indicate that start bit was not  detected last */
            ret = E_NOT;
        }  
    return ret;  
}

Std_ReturnType i2c_Master_SendStop(void)
{
    Std_ReturnType ret = E_NOT;
    
    // initiate stop condition
    I2C_MASTER_STOP_CONDITION();
    
    /* Wait Stop condition to finish */
    while(SSPCON2bits.PEN)
            ;
    /* clear flag */
    PIR1bits.SSPIF = 0;
    
    if( I2C_STOP_BIT_CHECK_CFG() == I2C_STOP_BIT_DETECTED )
    {
        /* indicate that Stop bit has beed detected*/
        ret = E_OK;
     }
     else
     {
        /* indicate that Stop bit was not  detected last */
        ret = E_NOT;
     }
            
    return ret;
}

Std_ReturnType i2c_Master_WriteByte_Blocking(uint8_t Data , uint8_t* _Ret_ACK)
{
    Std_ReturnType ret = E_NOT;
    /* Check null pointer and BF Status*/
    if(_Ret_ACK && I2C_BUFFER_STAT_CFG() == I2C_BF_STAT_EMPTY)
    {
        // write data to sspbuf reg 
        SSPBUF = Data;
        // if check if write collision occur
        if(I2C_WRITE_COLLISION_CHECK_CFG() == I2C_WRITE_COLLISION_DETECTED)
        {
            // clear write collision flag and exit
            I2C_WRITE_COLLISION_CLEAR_CFG();
            ret = E_NOT;
            *_Ret_ACK = I2C_TRASMITER_ACK_NOT_RECEIVED;
        }
        else
        {
            // wait till transmit finish
            while(!PIR1bits.SSPIF)
                ;
            /* clear flag */
            PIR1bits.SSPIF = 0;
            
            /* Read ack bit form the slave*/
            *_Ret_ACK = SSPCON2bits.ACKSTAT;
            ret = E_OK;
        }
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}

Std_ReturnType i2c_Master_ReadByte_Blocking(uint8_t* Rec_Data , uint8_t Send_ACK)
{
   Std_ReturnType ret = E_NOT;
   if(Rec_Data)
   {
       /* Enable receiveing mode */
       I2C_RECEIVE_ENABLE_CFG(); /* auto clear by hardware*/
       // check if recerive over flow occured
       if(SSPCON1bits.SSPOV  == 1)
       {
           SSPCON1bits.SSPOV = 0;
       }
       else {/*empty*/}
       if(I2C_WRITE_COLLISION_CHECK_CFG() == I2C_WRITE_COLLISION_DETECTED)
       {
           I2C_WRITE_COLLISION_CLEAR_CFG();
       }
       else { /* empty */}
       while(I2C_BF_STAT_EMPTY == I2C_BUFFER_STAT_CFG())
           ;
       /* clear flag */
       PIR1bits.SSPIF = 0;
       // read data from sspbuf reg
       *Rec_Data = SSPBUF;
       
       /* Generate ack */
       SSPCON2bits.ACKDT = Send_ACK; /* Acknowledge Data bit (Master Receive mode only) */
       SSPCON2bits.ACKEN = 1; /*Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit*/
       ret =  E_OK;
   }
   else
   {
       ret = E_NOT;
   }
   return ret;
}

Std_ReturnType i2c_Slave_ReadData_Polling(uint8_t* RecData)
{
    Std_ReturnType ret = E_NOT;
    uint8_t dummy_read = 0;
    if(RecData)
    {
        // check if receive over flow occured
        if(SSPCON1bits.SSPOV  == 1)
        {
            SSPCON1bits.SSPOV = 0;
        }
        else {/*empty*/}
        if(I2C_SLAVE_REC_BYTE_CHECK_CFG() == I2C_SLAVE_REC_BYTE_ADD )
        {
            dummy_read = SSPBUF;
            /* clear flag */
            PIR1bits.SSPIF = 0;
        }
        else {/*nothing*/}
        if( I2C_BUFFER_STAT_CFG() == I2C_BF_STAT_FULL)
        {
            *RecData = SSPBUF;
            /* clear flag */
            PIR1bits.SSPIF = 0;
        }
        else {/*nothing*/}
        ret = E_OK;
        
    }
    else
    {
        //nothing
    }
        
    return ret;
}

Std_ReturnType i2c_Slave_WriteData_Polling(uint8_t RecData)
{
    Std_ReturnType ret = E_NOT;
    uint8_t dummyRead;
    //  last received byte was address and buffer is full 
        if(I2C_SLAVE_REC_BYTE_CHECK_CFG() == I2C_SLAVE_REC_BYTE_ADD &&   I2C_BUFFER_STAT_CFG() == I2C_BF_STAT_FULL )
        {
            dummyRead = SSPBUF;
            /* clear flag */
            PIR1bits.SSPIF = 0;
        }
        else {/*nothing*/}
        SSPBUF = RecData;
       if(I2C_WRITE_COLLISION_CHECK_CFG() == I2C_WRITE_COLLISION_DETECTED)
       {
           I2C_WRITE_COLLISION_CLEAR_CFG();
       }
        ret = E_OK;
        
    return ret;
}

static void inline i2c_Master_config(const i2c_t* _i2c_config)
{
    /* Master clock */
    SSPADD = (uint8_t) ( ( _XTAL_FREQ / (4.0 * _i2c_config->i2c_MasterClock_SlaveAddress ) ) -  1.0 );
    
    /* I2C Mode */
    SSPCON1bits.SSPM = _i2c_config->i2c_cfg.i2c_mode;
}
static void inline i2c_Slave_config(const i2c_t* _i2c_config)
{
    /* I2C Mode */
    SSPCON1bits.SSPM = _i2c_config->i2c_cfg.i2c_mode;
    /* General Call */
    if(I2C_SLAVE_MODE_GENERAL_CALL_ENABLE == _i2c_config->i2c_cfg.i2c_general_call)
    {
        I2C_GENERAL_CALL_ENABLE_CFG();
    }
    else if(I2C_SLAVE_MODE_GENERAL_CALL_DISABLE == _i2c_config->i2c_cfg.i2c_general_call)
    {
        I2C_GENERAL_CALL_DISABLE_CFG();
    }
    else { /* nothing */}
    
    /* Clock stretching */
    if(I2C_SLAVE_MODE_CLK_STRETCH_ENABLE == _i2c_config->i2c_cfg.i2c_clk_stretch)
    {
        I2C_SLAVE_CLK_STRETCH_ENABLE_CFG();
    }
    else if(I2C_SLAVE_MODE_CLK_STRETCH_DISABLE == _i2c_config->i2c_cfg.i2c_clk_stretch)
    {
        I2C_SLAVE_CLK_STRETCH_DISABLE_CFG();
    }
    else { /* nothing */}
    
    /* Slave realse clock */
    I2C_SLAVE_SCK_RELEASE_CFG(); /* write logic 1 to SCL */
    
    /* Slave Address */
    SSPADD = (uint8_t)(_i2c_config->i2c_MasterClock_SlaveAddress);
}

static void inline i2c_gpio_config(void)
{
    TRISCbits.TRISC3 = 1; /* configure Serial clock (SCL) as input */
    TRISCbits.TRISC4 = 1; /* configure Serial data (SDA) as input */
}

#if (I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE) || (I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE)

static void inline i2c_interrupt_init(const i2c_t* _i2c_config)
{
    
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    
    INTERRUPT_PRIORITY_FEATURE_ENABLE();
    INTERRUPT_HIGH_PRIORITY_ENABLE();
    INTERRUPT_LOW_PRIORITY_ENABLE();
    
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   I2C_MSSP_INTERRUPT_PRI_SELECT();
#endif
  
#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    I2C_BUS_COLLISION_INTERRUPT_PRI_SELECT();
#endif
    
#else
     INTERRUPT_ENABLE_UNMASKED();
     INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
#endif
     
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    I2C_MSSP_INTERRUPT_CLEAR_FLAG();
   G_I2C_MSSP_InterruptHandler = _i2c_config->I2C_DefaultInterruptHandler;
   I2C_MSSP_INTERRUPT_ENABLE();
#endif
   
#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
   I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
   G_I2C_BusCollision_InterruptHandler = _i2c_config->I2C_BUSCollision_Handler;
   I2C_BUS_COLLISION_INTERRUPT_ENABLE();
#endif
}

#endif

void I2C_MSSP_ISR(void)
{
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    I2C_MSSP_INTERRUPT_CLEAR_FLAG();
    if(G_I2C_MSSP_InterruptHandler)
        G_I2C_MSSP_InterruptHandler();
#endif
}

void I2C_BusCollision_ISR(void)
{
#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
    if(G_I2C_BusCollision_InterruptHandler)
        G_I2C_BusCollision_InterruptHandler();
#endif
}