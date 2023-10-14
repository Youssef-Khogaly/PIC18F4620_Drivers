#include "SPI.h"



static SPI_InterruptHandler_t SPI_InterruptHandler_CBF = NULL;

/* Helper functions*/

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static void SPI_interrupt_init(void);

#endif

static void SPI_MasterMode_init(const SPI_cfg_t* _spi_cfg);
static void SPI_SlaveMode_init(const SPI_cfg_t* _spi_cfg);





Std_ReturnType SPI_init(const SPI_cfg_t* _spi_cfg)
{
    Std_ReturnType ret = E_NOT;
    if(_spi_cfg != NULL)
    {
        SPI_DISABLE();
        
        if(_spi_cfg->spi_mode == SPI_MASTER_MODE_FOSC_DIV_4 || _spi_cfg->spi_mode == SPI_MASTER_MODE_FOSC_DIV_16 || _spi_cfg->spi_mode == SPI_MASTER_MODE_FOSC_DIV_64 || _spi_cfg->spi_mode == SPI_MASTER_MODE_CLK_TMR2_DIV_2)
        {
            SPI_MasterMode_init(_spi_cfg);
        }
        else if(_spi_cfg->spi_mode == SPI_SLAVE_MODE_SS_ENABLE || _spi_cfg->spi_mode == SPI_SLAVE_MODE_SS_DISABLE )
        {
            SPI_SlaveMode_init(_spi_cfg);
        }
        else {/*empty*/}
#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        SPI_InterruptHandler_CBF = _spi_cfg->spi_pFunc_cbf;
        SPI_interrupt_init();
#endif
        
        
        
        
        
        SPI_ENABLE();
         ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    
    return ret;
}

Std_ReturnType SPI_deInit(void)
{
    Std_ReturnType ret = E_OK;
    SPI_DISABLE();
    return ret;
}

Std_ReturnType SPI_Transceive_SlaveSelect(const uint8_t Transmit_data , uint8_t* Rec_data , const pinConfig_t* SlaveSelectPin)
{
    Std_ReturnType ret = E_NOT;
    if(Rec_data && SlaveSelectPin )
    {

        gpio_pin_write_logic(SlaveSelectPin,low);

        SSPBUF = Transmit_data;
        while( SPI_WRITE_COLLISION_CHECK() == SPI_WRITE_COLLISION_OCCUR)
        {
            SPI_WRITE_COLLISION_CLEAR();
            SSPBUF = Transmit_data;
        }
        
        while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
        *Rec_data = SSPBUF;
        
        
       gpio_pin_write_logic(SlaveSelectPin,high); 

        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}

Std_ReturnType SPI_Transceive(const uint8_t Transmit_data , uint8_t* Rec_data)
{
    Std_ReturnType ret = E_NOT;
    if(Rec_data)
    {
        SSPBUF = Transmit_data;
        while( SPI_WRITE_COLLISION_CHECK() == SPI_WRITE_COLLISION_OCCUR)
        {
            SPI_WRITE_COLLISION_CLEAR();
            SSPBUF = Transmit_data;
        }
        
        while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
        *Rec_data = SSPBUF;
        
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}

Std_ReturnType SPI_Transceive_string(uint8_t* Transmit_data ,uint8_t Transmit_arrLen  ,uint8_t* Rec_data)
{
    Std_ReturnType ret = E_NOT;
    int l_trans_counter = 0;
    if(Rec_data && Transmit_data )
    {
        while ( l_trans_counter < Transmit_arrLen )
        {
            SSPBUF = Transmit_data[l_trans_counter];
            while( SPI_WRITE_COLLISION_CHECK() == SPI_WRITE_COLLISION_OCCUR)
            {
                SPI_WRITE_COLLISION_CLEAR();
                SSPBUF = Transmit_data[l_trans_counter];
            }
            while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
                ;
            if(Rec_data == NULL)
            {
                ret = E_NOT;
                return ret;
            }
            *Rec_data++ = SSPBUF;
            ++l_trans_counter;
        }

        
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}


Std_ReturnType SPI_Transmit(const uint8_t Transmit_data)
{
    Std_ReturnType ret = E_NOT;
    uint8_t l_spi_tempRead = 0;
    
    SSPBUF = Transmit_data;
    while( SPI_WRITE_COLLISION_CHECK() == SPI_WRITE_COLLISION_OCCUR )
    {
         SPI_WRITE_COLLISION_CLEAR();
         SSPBUF = Transmit_data;
     }
    while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
    l_spi_tempRead = SSPBUF;
    ret = E_OK;
    return ret;
}

Std_ReturnType SPI_Transmit_string(uint8_t* Transmit_data , uint8_t transArr_len)
{
    Std_ReturnType ret = E_NOT;
    int l_trans_counter = 0;
    for(; l_trans_counter < transArr_len  ; ++l_trans_counter)
    {
        SPI_Transmit(Transmit_data[l_trans_counter]);
        if(Transmit_data[l_trans_counter] == '\0')
            break;
    }
    ret = E_OK;
    return ret;
}
Std_ReturnType SPI_Transmit_SlaveSelect(const uint8_t Transmit_data , const pinConfig_t* SlaveSelectPin)
{
    Std_ReturnType ret = E_NOT;
    uint8_t l_spi_tempRead = 0;
    if(SlaveSelectPin)
    {
        gpio_pin_write_logic(SlaveSelectPin,low);
        SSPBUF = Transmit_data;
        while( SPI_WRITE_COLLISION_CHECK() == SPI_WRITE_COLLISION_OCCUR)
        {
            SPI_WRITE_COLLISION_CLEAR();
            SSPBUF = Transmit_data;
        }
        
        while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
        l_spi_tempRead = SSPBUF;
        gpio_pin_write_logic(SlaveSelectPin,high);
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}
Std_ReturnType SPI_TransmitString_SlaveSelect(const uint8_t* Transmit_data ,uint8_t transArr_len , const pinConfig_t* SlaveSelectPin)
{
    Std_ReturnType ret = E_NOT;
    uint8_t l_transCounter = 0;
    if(Transmit_data && Transmit_data)
    {
        gpio_pin_write_logic(SlaveSelectPin,low);
        for(; l_transCounter < transArr_len ; ++l_transCounter)
        {
            SPI_Transmit(Transmit_data[l_transCounter]);
        }
        gpio_pin_write_logic(SlaveSelectPin,high);
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    
    return ret;
    
}

Std_ReturnType SPI_Master_Recieve( uint8_t* Rec_data)
{
    Std_ReturnType ret = E_NOT;
    if(Rec_data)
    {
        /* SDO input
         * DISABLE spi transmiting
         */
        TRISCbits.RC5 = input;
        SSPBUF = 0;
        while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
        *Rec_data = SSPBUF;
        ret = E_OK;
        /* SDO output
         * enable spi transmiting
         */
        TRISCbits.RC5 = output;
    }
    else
    {
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_RecieveString( uint8_t* Rec_data , uint8_t Rec_dataSize)
{
    Std_ReturnType ret = E_NOT;
    int l_recCounter = 0;
    if(Rec_data)
    {
        for( ; l_recCounter < Rec_dataSize ; ++l_recCounter )
        {
          while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
          Rec_data[l_recCounter] = SSPBUF;
          if(Rec_data[l_recCounter] == '\0')
              break;
        }
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}
Std_ReturnType SPI_Slave_Recieve( uint8_t* Rec_data)
{
    Std_ReturnType ret = E_OK;
        while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
        *Rec_data = SSPBUF;
        return ret;
}
Std_ReturnType SPI_Master_Recieve_SlaveSelect( uint8_t* Rec_data ,  const pinConfig_t* SlaveSelectPin)
{
    Std_ReturnType ret = E_NOT;
    if(Rec_data && SlaveSelectPin)
    {
         gpio_pin_write_logic(SlaveSelectPin,low);
         
        /* SDO input
         * DISABLE spi transmiting
         */
        TRISCbits.RC5 = input;
        SSPBUF = 0; // temp write to start clock
        while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
            ;
        *Rec_data = SSPBUF;
        ret = E_OK;
        /* SDO output
         * enable spi transmiting
         */
        TRISCbits.RC5 = output;
        
         gpio_pin_write_logic(SlaveSelectPin,high);
    }
    else
    {
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType SPI_Master_RecieveString_SlaveSelect( uint8_t* Rec_data, uint8_t Rec_dataArrSize ,   const pinConfig_t* SlaveSelectPin)
{
    Std_ReturnType ret = E_NOT;
    int l_recCounter = 0;
    if(Rec_data && SlaveSelectPin )
    {
         gpio_pin_write_logic(SlaveSelectPin,low);
        /* SDO input
         * DISABLE spi transmiting
         */
        TRISCbits.RC5 = input;
         
        for(; l_recCounter < Rec_dataArrSize ; ++l_recCounter)
        {
            SSPBUF = 0; // temp write to start clock
            while(SPI_BUFFER_STATUS() == SPI_RECIVED_NOT_COMPLETE)
                ;
            Rec_data[l_recCounter] = SSPBUF;
            if(Rec_data[l_recCounter] == '\0')
                break;
        }

        /* SDO output
         * enable spi transmiting
         */
        TRISCbits.RC5 = output;
         gpio_pin_write_logic(SlaveSelectPin,high);
    }
    else
    {
        ret = E_NOT;
    }
    return ret;
}

static void SPI_MasterMode_init(const SPI_cfg_t* _spi_cfg)
{
    
#if SPI_MODE == SPI_MASTER_MODE && SPI_SS_MODE == SPI_SS_ENABLE
    int l_counter = 0;
    for( ;l_counter < SPI_NUMBER_OF_SLAVES ; ++l_counter )
    {
        gpio_pin_direction_intialize(&_spi_cfg->SlaveSelect_pins[l_counter]);
        gpio_pin_write_logic(&_spi_cfg->SlaveSelect_pins[l_counter] , high);
    }
    
#endif
    TRISCbits.RC3 = output; /*SCK output*/
    TRISCbits.RC5 = output; /*SDO output*/
    SPI_SAMPLE_MODE_SELECT(_spi_cfg->spi_sample_mode);
    SPI_CKE_SELECT(_spi_cfg->spi_clk_select);
    SPI_CLK_POLARIY_SELECT(_spi_cfg->spi_clk_polarity);
    SPI_MODE_SELECT(_spi_cfg->spi_mode);
    
}
static void SPI_SlaveMode_init(const SPI_cfg_t* _spi_cfg)
{
    TRISCbits.RC3 = input; /*SCK input*/
    TRISCbits.RC5 = output; /*SDO output*/
    TRISAbits.RA5 = input;
    if(_spi_cfg->spi_mode == SPI_SLAVE_MODE_SS_ENABLE )
    {
        /* configure SS pin as input */
        TRISAbits.RA5 = input;
    }
    SPI_SAMPLE_MODE_SELECT(((uint8_t)0x00));
    SPI_CKE_SELECT(_spi_cfg->spi_clk_select);
    SPI_CLK_POLARIY_SELECT(_spi_cfg->spi_clk_polarity);
    SPI_MODE_SELECT(_spi_cfg->spi_mode);
}
    
#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static void SPI_interrupt_init(void)
{
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_HIGH_PRIORITY_ENABLE();
    INTERRUPT_LOW_PRIORITY_ENABLE();
    INTERRUPT_PRIORITY_FEATURE_ENABLE();

#else
    INTERRUPT_ENABLE_UNMASKED();
    INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
#endif
    
    SPI_INTERRUPT_PRI_SELECT();
    SPI_INTERRUPT_CLEAR_FLAG();
    SPI_INTERRUPT_ENABLE();
}

#endif

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void SPI_ISR(void)
{
    SPI_INTERRUPT_CLEAR_FLAG();
    if(SPI_InterruptHandler_CBF)
        SPI_InterruptHandler_CBF();
}
#endif