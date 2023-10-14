
# Pic 18f4620 MCU Drivers 


## Description
Drivers for pic18f4620 MCU 

all drivers written in C
 
Based on  layred architecture
## MCAL Layer (Microcontroller Abstraction Layer)
1.GPIO Driver\
interrupt Driver: (internal and external interrupt) please read carefully this file before using interrupt drivers:\
mcal_interrupt_gen_cfg: use precompiled configuration to enable or disable the interrupt feature for any peripheral and chose interrupt priority\
2.ADC Driver\
3.timers drivers : timer0,timer1,timer2.timer3\
4.internal EEPROM Driver\
5.CCP Module:\
6- EUSART\
7- SPI\
8-I2C\

## ECU Layer (Electronic Control Unit)
1. LCD (4x16)
2. Keypad
3. led
4. Dc Motor
5. Relay
6. Button
7. 7 Segment