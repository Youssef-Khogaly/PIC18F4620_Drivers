
#include "MCAL_INIT.h"


/*------Global Variables---------*/
eusart_cfg_t uart = {
  .baudrate = 9600,
  .baudrate_cfg = BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
  
  .eusart_tx_cfg.eusart_tx_9bit_enable = EUSART_ASYNC_9BIT_TX_DISABLE,
  .eusart_tx_cfg.eusart_tx_enable = EUSART_ASYNC_TX_ENABLE,
  
  .eusart_rx_cfg.eusart_rx_9bit_enable = EUSART_ASYNC_9BIT_RX_DISABLE,
  .eusart_rx_cfg.eusart_rx_enable = EUSART_ASYNC_RX_ENABLE
};

/*-----Static functions---------*/

Std_ReturnType mcal_init(void)
{
    Std_ReturnType ret = EUSART_Async_Init(&uart);
    
    
    
    
    
    return ret;
}