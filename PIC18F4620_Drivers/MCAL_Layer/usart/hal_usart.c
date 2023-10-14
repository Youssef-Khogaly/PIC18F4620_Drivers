

#include "hal_usart.h"


static eusart_pfunc_CBF_t  G_EUSART_Tx_CBF = NULL;
static eusart_pfunc_CBF_t  G_EUSART_Rx_CBF = NULL;
static eusart_pfunc_CBF_t  G_EUSART_FrameError_CBF = NULL;
static eusart_pfunc_CBF_t  G_EUSART_OverRunError_CBF = NULL;

// helper functions

static void EUSART_Tx_init(const eusart_cfg_t *_eusart);
static void EUSART_Rx_init(const eusart_cfg_t *_eusart);
static void EUSART_BaudRateInit(const eusart_cfg_t *_eusart);

static uint8_t* TxData = NULL;


Std_ReturnType EUSART_Async_Init(const eusart_cfg_t *_eusart)
{
    Std_ReturnType ret = E_NOT;
    if(_eusart == NULL)
    {
        ret = E_NOT;
    }
    else
    {
        
        EUSART_DISABLE();
        // init tx and rx direction
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        /*init baudrate and mode*/
        EUSART_BaudRateInit(_eusart);
        /* init reciver*/
        if(_eusart->eusart_tx_cfg.eusart_tx_enable == EUSART_ASYNC_TX_ENABLE)
        {
            EUSART_Tx_init(_eusart);
        }
        else {/*nothing*/}
        
        /* init transmeter*/
        if(_eusart->eusart_rx_cfg.eusart_rx_enable == EUSART_ASYNC_RX_ENABLE)
        {
            EUSART_Rx_init(_eusart);
        }
        else {/*nothing*/}   
        EUSART_ENABLE();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType EUSART_Deinit(const eusart_cfg_t *_eusart)
{
    Std_ReturnType ret = E_NOT;
    if(_eusart == NULL)
    {
        ret = E_NOT;
    }
    else
    {
        EUSART_DISABLE();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType EUSART_WriteByte_Blocking(uint8_t data)
{
    Std_ReturnType ret = E_NOT;
        // wait untill tsr txreg not empty
        while( !TXSTAbits.TRMT )
            ;
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_INTERRUPT_ENABLE();
#endif
        TXREG = data;
        ret = E_OK;
    return ret;
}
Std_ReturnType EUSART_WriteStr_Blocking(uint8_t* data)
{
    Std_ReturnType ret = E_NOT;
    if(data == NULL)
    {
        ret = E_NOT;
    }
    else
    {
        while(*data)
        {
            EUSART_WriteByte_Blocking(*data++);
        }
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType EUSART_ReadByte_Blocking( uint8_t* _data)
{
    Std_ReturnType ret = E_NOT;
    if(_data == NULL)
    {
        ret = E_NOT;
    }
    else
    {
        while(!PIR1bits.RCIF)
            ;
        *_data = RCREG;
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_INTERRUPT_ENABLE();
#endif
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType EUSART_WriteByte_polling(uint8_t data)
{
    Std_ReturnType ret = E_NOT;
    if(TXSTAbits.TRMT == 1)
    {
        TXREG = data;
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_INTERRUPT_ENABLE();
#endif
        ret = E_OK;
    }
    else
    {
        ret = E_NOT;
    }

    return ret;
}

Std_ReturnType EUSART_WriteStr_polling(uint8_t* data)
{
    Std_ReturnType ret = E_NOT;
    if(data)
    {
        while(*data)
        {
            ret = EUSART_WriteByte_polling(*data);
            if(ret == E_OK)
            {
                data++;
                
            }
            else
            {
                //nothing
            }  
        
        }
    }

    else
    {
        ret = E_NOT;
    }
    return ret;
}

Std_ReturnType EUSART_ReadByte_polling(uint8_t* data)
{
    Std_ReturnType ret = E_NOT;
    if( !data || !PIR1bits.RCIF )
    {
        ret = E_NOT;
    }
    else
    {
        *data = RCREG;
        ret = E_OK;
    }
    return ret;
}

static void EUSART_Tx_init(const eusart_cfg_t *_eusart)
{
    // enable interrupt if need
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_FEATURE_ENABLE();
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        INTERRUPT_LOW_PRIORITY_ENABLE();
        // set tx priority
        IPR1bits.TXIP = EUSART_TX_INTERRUPT_PRI;
#else
        INTERRUPT_ENABLE_UNMASKED();
        INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
#endif
        EUSART_TX_INTERRUPT_DISABLE();
        G_EUSART_Tx_CBF = _eusart->EUSART_Tx_InterruptHandler;
         
#endif
    //enable 9bit if need
    if(_eusart->eusart_tx_cfg.eusart_tx_9bit_enable == EUSART_ASYNC_9BIT_TX_ENABLE)
    {
        TXSTAbits.TX9 = 1;
    }
    else {}
    // enable trasmit txen
    TXSTAbits.TXEN = 1;
    return;
}
static void EUSART_Rx_init(const eusart_cfg_t *_eusart)
{
    
    // enable interrupt if need
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_FEATURE_ENABLE();
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        INTERRUPT_LOW_PRIORITY_ENABLE();
        // set rx priority
        IPR1bits.RCIP = EUSART_RX_INTERRUPT_PRI;
#else
        INTERRUPT_ENABLE_UNMASKED();
        INTERRUPT_ENABLE_UNMASKED_PERIPHERALS();
#endif
        EUSART_RX_INTERRUPT_ENABLE();
        G_EUSART_Rx_CBF = _eusart->EUSART_Rx_InterruptHandler;
        G_EUSART_FrameError_CBF = _eusart->EUSART_FrameError_InterruptHandler;
        G_EUSART_OverRunError_CBF = _eusart->EUSART_OverRunError_InterruptHandler;
#endif
    //enable 9bit if need
    if(_eusart->eusart_rx_cfg.eusart_rx_9bit_enable == EUSART_ASYNC_9BIT_RX_ENABLE)
    {
        RCSTAbits.RX9 = 1;
    }
    else {}  
    // enable receiver
    RCSTAbits.CREN = 1;
    
    return;
}
static void EUSART_BaudRateInit(const eusart_cfg_t *_eusart)
{
    float_t baudRateVal = 0;
    switch(_eusart->baudrate_cfg)
    {
        case BAUDRATE_ASYNC_8BIT_LOW_SPEED :
            TXSTA1bits.BRGH = 0;
            TXSTA1bits.SYNC = 0;
            BAUDCONbits.BRG16 = 0;
            SPBRG1 = (uint8_t)(((_XTAL_FREQ/(float_t)_eusart->baudrate) / 64.0f) - 1.0f);
            break;
        case BAUDRATE_ASYNC_8BIT_HIGH_SPEED :
            TXSTA1bits.BRGH = 1;
            TXSTA1bits.SYNC = 0;
            BAUDCONbits.BRG16 = 0;
            SPBRG1 = (uint8_t)(((_XTAL_FREQ/(float_t)_eusart->baudrate) /16.0f) - 1.0f);
            break;
        case BAUDRATE_ASYNC_16BIT_LOW_SPEED :
            TXSTA1bits.BRGH = 0;
            TXSTA1bits.SYNC = 0;
            BAUDCONbits.BRG16 = 1;
            baudRateVal = (float_t)( ((_XTAL_FREQ/(float_t)_eusart->baudrate) / 16.0f) - 1.0f );
            SPBRG1 = (uint8_t)baudRateVal;
            SPBRGH = (uint8_t)((uint32_t)baudRateVal >> 8);
            break;
        case BAUDRATE_ASYNC_16BIT_HIGH_SPEED :
            TXSTA1bits.BRGH = 1;
            TXSTA1bits.SYNC = 0;
            BAUDCONbits.BRG16 = 1;
            baudRateVal = (float_t)(((_XTAL_FREQ/(float_t)_eusart->baudrate) / 4.0f) - 1.0f);
            SPBRG1 = (uint8_t)baudRateVal;
            SPBRGH = (uint8_t)((uint32_t)baudRateVal >> 8);
            break;
        case BAUDRATE_SYNC_8BIT :
            TXSTA1bits.SYNC = 1;
            BAUDCONbits.BRG16 = 0;
            SPBRG1 = (uint8_t)(((_XTAL_FREQ/(float_t)_eusart->baudrate) / 4.0f) - 1.0f);
            break;
        case BAUDRATE_SYNC_16BIT:
            TXSTA1bits.SYNC = 1;
            BAUDCONbits.BRG16 = 1;
            baudRateVal = (float_t)(((_XTAL_FREQ/(float_t)_eusart->baudrate) / 4.0f) - 1.0f);
            SPBRG1 = (uint8_t)baudRateVal;
            SPBRGH = (uint8_t)((uint32_t)baudRateVal >> 8);
            break;
            
        default:
            break;
    }
    return;
}


// interrupt handlers

void EUSART_TX_interruptHandler(void)
{
    if(G_EUSART_Tx_CBF != NULL)
    {
        EUSART_TX_INTERRUPT_DISABLE();
        G_EUSART_Tx_CBF();
        
    }
    else
    {
        // nothing  
    }
}

void EUSART_RX_interruptHandler(void)
{
    if(G_EUSART_FrameError_CBF && RCSTAbits.FERR == 1)
    {
        uint8_t dummyRead;
       //dummy read to clear framing error
        EUSART_ReadByte_polling(&dummyRead);
        G_EUSART_FrameError_CBF();
    }
    else if(G_EUSART_Rx_CBF)
    {
        G_EUSART_Rx_CBF();
    }
    else
    {
        // nothing  
    }
   if(G_EUSART_OverRunError_CBF)
    {
        G_EUSART_OverRunError_CBF();
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    else
    {
        // nothing  
    }
}