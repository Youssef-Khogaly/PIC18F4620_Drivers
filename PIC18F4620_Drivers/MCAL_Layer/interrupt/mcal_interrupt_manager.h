/* 
 * File:   mcal_interrupt_manager.h
 * Author: yossef
 *
 * Created on April 5, 2023, 10:47 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/*----------includes------------*/
#include "mcal_interrupt_cfg.h"
/*--------------Macros---------------*/

/*--------function-Macro--------------*/


/*----------user-datatypes------------*/

/*------------interfaces-prototype-----*/
void INTO_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8_t RB4_src);
void RB5_ISR(uint8_t RB5_src);
void RB6_ISR(uint8_t RB6_src);
void RB7_ISR(uint8_t RB7_src);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_interruptHandler(void);
void EUSART_RX_interruptHandler(void);
void SPI_ISR(void);
void I2C_MSSP_ISR(void);
void I2C_BusCollision_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

