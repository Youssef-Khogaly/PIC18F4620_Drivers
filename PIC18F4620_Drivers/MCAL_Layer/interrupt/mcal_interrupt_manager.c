/* 
 * File:   mcal_interrupt_manager.h
 * Author: yossef
 *
 * Created on April 5, 2023, 10:47 AM
 */
#include "mcal_interrupt_manager.h"

/*---------Global-variables------*/
static volatile uint8_t RB4_flag = 1;
static volatile uint8_t RB5_flag = 1;
static volatile uint8_t RB6_flag = 1;
static volatile uint8_t RB7_flag = 1;
/*---------helper-functions------*/


/*-------------------------------------*/
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManager_High(void){
#if INTERRUPT_INTO_FEATURE == INTERRUPT_FEATURE_ENABLE
  if( (INTCONbits.INT0E) && (INTCONbits.INT0IF))
    {
        INTO_ISR ();
    }
    else {/* nothing*/}
#endif
#if (INTERRUPT_INT1_FEATURE == INTERRUPT_FEATURE_ENABLE) && (INTERRUPT_INT1_PRI == INTERRUPT_HIGH_PRI)
  if( (INTCON3bits.INT1E) && (INTCON3bits.INT1IF))
    {
        INT1_ISR ();
    }
    else {/* nothing*/}
#endif
#if (INTERRUPT_INT2_FEATURE == INTERRUPT_FEATURE_ENABLE) && (INTERRUPT_INT2_PRI == INTERRUPT_HIGH_PRI)
  if( (INTCON3bits.INT2IE) && (INTCON3bits.INT2IF))
    {
        INT2_ISR ();
    }
    else {/* nothing*/}
#endif
#if (INTERRUPT_EXTERNAL_ONCHANGE_FEATURE == INTERRUPT_FEATURE_ENABLE) && (INTERRUPT_RBx_priority == INTERRUPT_HIGH_PRI)
  
  /* KB0 */
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI0) && (1 == RB4_flag) )
    {
      RB4_flag = 0;
      RB4_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI0)&& (0 == RB4_flag) )
    {
      RB4_flag = 1;
      RB4_ISR(0);
    }
  else { /*Nothing*/}
  /*------*/
  /* KB1 */
    if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI1)&& (1 == RB5_flag) )
    {
      RB5_flag = 0;
      RB5_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI1)&& (0 == RB5_flag) )
    {
      RB5_flag = 1;
      RB5_ISR(0);
    }
  else { /*Nothing*/}
  /*----------------*/
    /*KB2*/
    if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI2)&& (1 == RB6_flag) )
    {
      RB6_flag = 0;
      RB6_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI2)&& (0 == RB6_flag) )
    {
      RB6_flag = 1;
      RB6_ISR(0);
    }
  else { /*Nothing*/}
  /*---------*/
    /*KB3*/
   if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI3)&& (1 == RB7_flag) )
    {
      RB7_flag = 0;
      RB7_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI3)&& (0 == RB7_flag) )
    {
      RB7_flag = 1;
      RB7_ISR(0);
    }
  else { /*Nothing*/}

  /*---------*/
#endif
  /**-----ADC-------*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && ADC_INTERRUPT_PRI == INTERRUPT_HIGH_PRI
  if(INTERRUPT_OCCUR == PIR1bits.ADIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.ADIE)
    {
      ADC_ISR();
    }
  
#endif
  
  /*-------Timer0-----*/
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == TIMER0_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == INTCONbits.T0IF && INTERRUPT_FEATURE_ENABLE == INTCONbits.T0IE)
    {
        TMR0_ISR();
    }  
#endif
  /*-------------*/

  /*-------Timer1-----*/
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == TIMER1_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.TMR1IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.TMR1IE)
    {
        TMR1_ISR();
    }  
#endif
  /*-------------*/
  /*-------Timer1-----*/
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == TIMER2_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.TMR2IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.TMR2IE)
    {
        TMR2_ISR();
    }  
#endif
  /*-------------*/
  
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == TIMER3_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR2bits.TMR3IF && INTERRUPT_FEATURE_ENABLE == PIE2bits.TMR3IE)
    {
        TMR3_ISR();
    }  
#endif
  
   /*-------------- CCP1-------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == CCP1_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.CCP1IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.CCP1IE)
    {
        CCP1_ISR();
    }  
#endif
  
  /*---------------CCP2--------------*/
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == CCP2_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR2bits.CCP2IF && INTERRUPT_FEATURE_ENABLE == PIE2bits.CCP2IE)
    {
        CCP2_ISR();
    }  
#endif

  /*---------------eusart tx--------------*/
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == EUSART_TX_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIE1bits.TXIE && INTERRUPT_FEATURE_ENABLE == PIR1bits.TXIF)
    {
        EUSART_TX_interruptHandler();
    } 
#endif
  
  /*---------------eusart rx--------------*/
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == EUSART_RX_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIE1bits.RCIE && INTERRUPT_FEATURE_ENABLE == PIR1bits.RCIF)
    {
        EUSART_RX_interruptHandler();
    }  
#endif
  
#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == SPI_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.SSPIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.SSPIE)
    {
        SPI_ISR();
    }  
#endif
  
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == I2C_MSSP_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.SSPIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.SSPIE)
    {
       I2C_MSSP_ISR();
    }  
#endif

#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_HIGH_PRI == I2C_BUS_COLLISION_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR2bits.BCLIF && INTERRUPT_FEATURE_ENABLE == PIE2bits.BCLIE)
    {
        I2C_BusCollision_ISR();
    }  
#endif
}



void __interrupt (low_priority) InterruptManager_Low(void){
  
 #if (INTERRUPT_INT1_FEATURE == INTERRUPT_FEATURE_ENABLE) && (INTERRUPT_INT1_PRI == INTERRUPT_LOW_PRI)
  if( (INTCON3bits.INT1E) && (INTCON3bits.INT1IF))
    {
        INT1_ISR ();
    }
    else {/* nothing*/}
#endif
#if (INTERRUPT_INT2_FEATURE == INTERRUPT_FEATURE_ENABLE) && (INTERRUPT_INT2_PRI == INTERRUPT_LOW_PRI)
  if( (INTCON3bits.INT2IE) && (INTCON3bits.INT2IF))
    {
        INT2_ISR ();
    }
    else {/* nothing*/}
#endif
#if (INTERRUPT_EXTERNAL_ONCHANGE_FEATURE == INTERRUPT_FEATURE_ENABLE) && (INTERRUPT_RBx_priority == INTERRUPT_LOW_PRI)
  
  /* KB0 */
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI0) && (1 == RB4_flag) )
    {
      RB4_flag = 0;
      RB4_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI0)&& (0 == RB4_flag) )
    {
      RB4_flag = 1;
      RB4_ISR(0);
    }
  else { /*Nothing*/}
  /*------*/
  /* KB1 */
    if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI1)&& (1 == RB5_flag) )
    {
      RB5_flag = 0;
      RB5_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI1)&& (0 == RB5_flag) )
    {
      RB5_flag = 1;
      RB5_ISR(0);
    }
  else { /*Nothing*/}
  /*----------------*/
    /*KB2*/
    if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI2)&& (1 == RB6_flag) )
    {
      RB6_flag = 0;
      RB6_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI2)&& (0 == RB6_flag) )
    {
      RB6_flag = 1;
      RB6_ISR(0);
    }
  else { /*Nothing*/}
  /*---------*/
    /*KB3*/
   if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI3)&& (1 == RB7_flag) )
    {
      RB7_flag = 0;
      RB7_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI3)&& (0 == RB7_flag) )
    {
      RB7_flag = 1;
      RB7_ISR(0);
    }
  else { /*Nothing*/}
  /*---------*/
#endif

  /**-----ADC-------*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && ADC_INTERRUPT_PRI == INTERRUPT_LOW_PRI
  if(INTERRUPT_OCCUR == PIR1bits.ADIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.ADIE )
    {
      ADC_ISR();
    }
#endif
  /*-------Timer0-----*/
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == TIMER0_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == INTCONbits.T0IF && INTERRUPT_FEATURE_ENABLE == INTCONbits.T0IE)
    {
        TMR0_ISR();
    }  
#endif
  /*-------Timer1-----*/
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == TIMER1_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.TMR1IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.TMR1IE)
    {
        TMR1_ISR();
    }  
#endif
  /*-------------*/
  /*-----------timer2----------*/
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == TIMER2_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.TMR2IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.TMR2IE)
    {
        TMR2_ISR();
    }  
#endif
  /*-------------*/
  
  /*--------------Timer 3--------------*/
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == TIMER3_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR2bits.TMR3IF && INTERRUPT_FEATURE_ENABLE == PIE2bits.TMR3IE)
    {
        TMR3_ISR();
    }  
#endif
  
   /*-------------- CCP1-------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == CCP1_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.CCP1IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.CCP1IE)
    {
        CCP1_ISR();
    }  
#endif
  
  /*---------------CCP2--------------*/
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == CCP2_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR2bits.CCP2IF && INTERRUPT_FEATURE_ENABLE == PIE2bits.CCP2IE)
    {
        CCP2_ISR();
    }  
#endif
  
  
  /*---------------eusart tx--------------*/
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == EUSART_TX_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIE1bits.TXIE && INTERRUPT_FEATURE_ENABLE == PIR1bits.TXIF)
    {
        EUSART_TX_interruptHandler();
    }  
#endif
  
  /*---------------eusart rx--------------*/
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == EUSART_RX_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIE1bits.RCIE && INTERRUPT_FEATURE_ENABLE == PIR1bits.RCIF)
    {
        EUSART_RX_interruptHandler();
    }   
#endif
  
  
#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == SPI_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.SSPIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.SSPIE)
    {
        SPI_ISR();
    }  
#endif
  
  
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == I2C_MSSP_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR1bits.SSPIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.SSPIE)
    {
       I2C_MSSP_ISR();
    }  
#endif

#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE && INTERRUPT_LOW_PRI == I2C_BUS_COLLISION_INTERRUPT_PRI
  if(INTERRUPT_OCCUR == PIR2bits.BCLIF && INTERRUPT_FEATURE_ENABLE == PIE2bits.BCLIE)
    {
        I2C_BusCollision_ISR();
    }  
#endif
}  
  



#else
void __interrupt() InterruptManager(void){
  
#if INTERRUPT_INTO_FEATURE == INTERRUPT_FEATURE_ENABLE
  if( (INTCONbits.INT0E == 1) && (INTCONbits.INT0IF == 1))
    {
        INTO_ISR ();
    }
  else {/* nothing*/}
#endif
  
#if INTERRUPT_INT1_FEATURE == INTERRUPT_FEATURE_ENABLE
  if( (INTCON3bits.INT1E == 1) && (INTCON3bits.INT1IF == 1))
    {
        INT1_ISR ();
    }
  else {/* nothing*/}
#endif
  
#if INTERRUPT_INT2_FEATURE == INTERRUPT_FEATURE_ENABLE
  if( (INTCON3bits.INT2IE == 1) && (INTCON3bits.INT2IF == 1))
    {
        INT2_ISR ();
    }
  else {/* nothing*/}
#endif
  
#if INTERRUPT_EXTERNAL_ONCHANGE_FEATURE == INTERRUPT_FEATURE_ENABLE
  
  /* KB0 */
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI0) && (1 == RB4_flag) )
    {
      RB4_flag = 0;
      RB4_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI0)&& (0 == RB4_flag) )
    {
      RB4_flag = 1;
      RB4_ISR(0);
    }
  else { /*Nothing*/}
  /*------*/
  /* KB1 */
    if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI1)&& (1 == RB5_flag) )
    {
      RB5_flag = 0;
      RB5_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI1)&& (0 == RB5_flag) )
    {
      RB5_flag = 1;
      RB5_ISR(0);
    }
  else { /*Nothing*/}
  /*----------------*/
    /*KB2*/
    if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI2)&& (1 == RB6_flag) )
    {
      RB6_flag = 0;
      RB6_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI2)&& (0 == RB6_flag) )
    {
      RB6_flag = 1;
      RB6_ISR(0);
    }
  else { /*Nothing*/}
  /*---------*/
    /*KB3*/
   if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (high == PORTBbits.KBI3)&& (1 == RB7_flag) )
    {
      RB7_flag = 0;
      RB7_ISR(1);
    }
  else { /*Nothing*/}
  if( (INTCONbits.RBIE == 1) && (INTCONbits.RBIF == 1 ) && (low == PORTBbits.KBI3)&& (0 == RB7_flag) )
    {
      RB7_flag = 1;
      RB7_ISR(0);
    }
  else { /*Nothing*/}
  /*---------*/
  
#endif
   /**-----ADC-------*/
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR1bits.ADIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.ADIE)
    {
      ADC_ISR();
    }
  
#endif
  /*-------------*/
  /*Timer0*/
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == INTCONbits.T0IF && INTERRUPT_FEATURE_ENABLE == INTCONbits.T0IE)
    {
        TMR0_ISR();
    }
#endif

  /*-------Timer1-----*/
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR1bits.TMR1IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.TMR1IE)
    {
        TMR1_ISR();
    }  
#endif
  /*-------------*/
  /*-----Timer2-------*/
  #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR1bits.TMR2IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.TMR2IE)
    {
        TMR2_ISR();
    }  
#endif
  /*-------------*/
  
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR2bits.TMR3IF && INTERRUPT_FEATURE_ENABLE == PIE2bits.TMR3IE)
    {
        TMR3_ISR();
    }  
#endif
  
  
   /*-------------- CCP1-------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR1bits.CCP1IF && INTERRUPT_FEATURE_ENABLE == PIE1bits.CCP1IE)
    {
        CCP1_ISR();
    }  
#endif
  
  /*---------------CCP2--------------*/
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 
  if(INTERRUPT_OCCUR == PIR2bits.CCP2IF && INTERRUPT_FEATURE_ENABLE == PIE2bits.CCP2IE)
    {
        CCP2_ISR();
    }  
#endif
  
  /*---------------eusart tx--------------*/
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIE1bits.TXIE && INTERRUPT_FEATURE_ENABLE == PIR1bits.TXIF)
    {
        EUSART_TX_interruptHandler();
    } 
#endif
  
  /*---------------eusart rx--------------*/
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIE1bits.RCIE && INTERRUPT_FEATURE_ENABLE == PIR1bits.RCIF)
    {
        EUSART_RX_interruptHandler();
    }   
#endif
  
#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR1bits.SSPIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.SSPIE)
    {
        SPI_ISR();
    }  
#endif
  
  
#if I2C_MSSP_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR1bits.SSPIF && INTERRUPT_FEATURE_ENABLE == PIE1bits.SSPIE)
    {
       I2C_MSSP_ISR();
    }  
#endif

#if I2C_BUS_COLLISION_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
  if(INTERRUPT_OCCUR == PIR2bits.BCLIF && INTERRUPT_FEATURE_ENABLE == PIE2bits.BCLIE)
    {
        I2C_BusCollision_ISR();
    }  
#endif
}
#endif