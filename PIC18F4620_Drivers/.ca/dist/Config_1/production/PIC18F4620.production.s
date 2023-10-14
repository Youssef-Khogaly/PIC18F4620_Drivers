subtitle "Microchip MPLAB XC8 C Compiler v2.40 (Free license) build 20220703182018 Og1 "

pagewidth 120

	opt flic

	processor	18F4620
include "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\18f4620.cgen.inc"
getbyte	macro	val,pos
	(((val) >> (8 * pos)) and 0xff)
endm
byte0	macro	val
	(getbyte(val,0))
endm
byte1	macro	val
	(getbyte(val,1))
endm
byte2	macro	val
	(getbyte(val,2))
endm
byte3	macro	val
	(getbyte(val,3))
endm
byte4	macro	val
	(getbyte(val,4))
endm
byte5	macro	val
	(getbyte(val,5))
endm
byte6	macro	val
	(getbyte(val,6))
endm
byte7	macro	val
	(getbyte(val,7))
endm
getword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffff)
endm
word0	macro	val
	(getword(val,0))
endm
word1	macro	val
	(getword(val,2))
endm
word2	macro	val
	(getword(val,4))
endm
word3	macro	val
	(getword(val,6))
endm
gettword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffffff)
endm
tword0	macro	val
	(gettword(val,0))
endm
tword1	macro	val
	(gettword(val,3))
endm
tword2	macro	val
	(gettword(val,6))
endm
getdword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffffffff)
endm
dword0	macro	val
	(getdword(val,0))
endm
dword1	macro	val
	(getdword(val,4))
endm
clrc   macro
	bcf	status,0
endm
setc   macro
	bsf	status,0
endm
clrz   macro
	bcf	status,2
endm
setz   macro
	bsf	status,2
endm
skipnz macro
	btfsc	status,2
endm
skipz  macro
	btfss	status,2
endm
skipnc macro
	btfsc	status,0
endm
skipc  macro
	btfss	status,0
endm
pushw macro
	movwf postinc1
endm
pushf macro arg1
	movff arg1, postinc1
endm
popw macro
	movf postdec1,f
	movf indf1,w
endm
popf macro arg1
	movf postdec1,f
	movff indf1,arg1
endm
popfc macro arg1
	movff plusw1,arg1
	decfsz fsr1,f
endm
	global	__ramtop
	global	__accesstop
# 55 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTA equ 0F80h ;# 
# 192 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTB equ 0F81h ;# 
# 363 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTC equ 0F82h ;# 
# 538 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTD equ 0F83h ;# 
# 680 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTE equ 0F84h ;# 
# 883 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATA equ 0F89h ;# 
# 995 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATB equ 0F8Ah ;# 
# 1107 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATC equ 0F8Bh ;# 
# 1219 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATD equ 0F8Ch ;# 
# 1331 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATE equ 0F8Dh ;# 
# 1383 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISA equ 0F92h ;# 
# 1388 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRA equ 0F92h ;# 
# 1605 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISB equ 0F93h ;# 
# 1610 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRB equ 0F93h ;# 
# 1827 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISC equ 0F94h ;# 
# 1832 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRC equ 0F94h ;# 
# 2049 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISD equ 0F95h ;# 
# 2054 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRD equ 0F95h ;# 
# 2271 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISE equ 0F96h ;# 
# 2276 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRE equ 0F96h ;# 
# 2435 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
OSCTUNE equ 0F9Bh ;# 
# 2500 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIE1 equ 0F9Dh ;# 
# 2577 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIR1 equ 0F9Eh ;# 
# 2654 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
IPR1 equ 0F9Fh ;# 
# 2731 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIE2 equ 0FA0h ;# 
# 2797 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIR2 equ 0FA1h ;# 
# 2863 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
IPR2 equ 0FA2h ;# 
# 2929 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EECON1 equ 0FA6h ;# 
# 2995 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EECON2 equ 0FA7h ;# 
# 3002 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEDATA equ 0FA8h ;# 
# 3009 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEADR equ 0FA9h ;# 
# 3016 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEADRH equ 0FAAh ;# 
# 3023 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCSTA equ 0FABh ;# 
# 3028 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCSTA1 equ 0FABh ;# 
# 3233 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXSTA equ 0FACh ;# 
# 3238 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXSTA1 equ 0FACh ;# 
# 3489 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXREG equ 0FADh ;# 
# 3494 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXREG1 equ 0FADh ;# 
# 3501 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCREG equ 0FAEh ;# 
# 3506 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCREG1 equ 0FAEh ;# 
# 3513 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRG equ 0FAFh ;# 
# 3518 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRG1 equ 0FAFh ;# 
# 3525 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRGH equ 0FB0h ;# 
# 3532 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T3CON equ 0FB1h ;# 
# 3644 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3 equ 0FB2h ;# 
# 3651 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3L equ 0FB2h ;# 
# 3658 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3H equ 0FB3h ;# 
# 3665 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CMCON equ 0FB4h ;# 
# 3755 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CVRCON equ 0FB5h ;# 
# 3834 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ECCP1AS equ 0FB6h ;# 
# 3916 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PWM1CON equ 0FB7h ;# 
# 3986 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BAUDCON equ 0FB8h ;# 
# 3991 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BAUDCTL equ 0FB8h ;# 
# 4158 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCP2CON equ 0FBAh ;# 
# 4237 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2 equ 0FBBh ;# 
# 4244 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2L equ 0FBBh ;# 
# 4251 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2H equ 0FBCh ;# 
# 4258 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCP1CON equ 0FBDh ;# 
# 4355 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1 equ 0FBEh ;# 
# 4362 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1L equ 0FBEh ;# 
# 4369 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1H equ 0FBFh ;# 
# 4376 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON2 equ 0FC0h ;# 
# 4447 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON1 equ 0FC1h ;# 
# 4532 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON0 equ 0FC2h ;# 
# 4651 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRES equ 0FC3h ;# 
# 4658 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRESL equ 0FC3h ;# 
# 4665 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRESH equ 0FC4h ;# 
# 4672 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPCON2 equ 0FC5h ;# 
# 4734 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPCON1 equ 0FC6h ;# 
# 4804 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPSTAT equ 0FC7h ;# 
# 5025 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPADD equ 0FC8h ;# 
# 5032 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPBUF equ 0FC9h ;# 
# 5039 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T2CON equ 0FCAh ;# 
# 5110 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PR2 equ 0FCBh ;# 
# 5115 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
MEMCON equ 0FCBh ;# 
# 5220 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR2 equ 0FCCh ;# 
# 5227 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T1CON equ 0FCDh ;# 
# 5330 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1 equ 0FCEh ;# 
# 5337 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1L equ 0FCEh ;# 
# 5344 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1H equ 0FCFh ;# 
# 5351 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCON equ 0FD0h ;# 
# 5484 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
WDTCON equ 0FD1h ;# 
# 5512 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
HLVDCON equ 0FD2h ;# 
# 5517 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LVDCON equ 0FD2h ;# 
# 5782 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
OSCCON equ 0FD3h ;# 
# 5859 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T0CON equ 0FD5h ;# 
# 5936 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0 equ 0FD6h ;# 
# 5943 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0L equ 0FD6h ;# 
# 5950 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0H equ 0FD7h ;# 
# 5957 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
STATUS equ 0FD8h ;# 
# 6028 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2 equ 0FD9h ;# 
# 6035 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2L equ 0FD9h ;# 
# 6042 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2H equ 0FDAh ;# 
# 6049 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW2 equ 0FDBh ;# 
# 6056 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC2 equ 0FDCh ;# 
# 6063 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC2 equ 0FDDh ;# 
# 6070 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC2 equ 0FDEh ;# 
# 6077 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF2 equ 0FDFh ;# 
# 6084 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BSR equ 0FE0h ;# 
# 6091 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1 equ 0FE1h ;# 
# 6098 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1L equ 0FE1h ;# 
# 6105 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1H equ 0FE2h ;# 
# 6112 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW1 equ 0FE3h ;# 
# 6119 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC1 equ 0FE4h ;# 
# 6126 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC1 equ 0FE5h ;# 
# 6133 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC1 equ 0FE6h ;# 
# 6140 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF1 equ 0FE7h ;# 
# 6147 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
WREG equ 0FE8h ;# 
# 6159 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0 equ 0FE9h ;# 
# 6166 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0L equ 0FE9h ;# 
# 6173 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0H equ 0FEAh ;# 
# 6180 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW0 equ 0FEBh ;# 
# 6187 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC0 equ 0FECh ;# 
# 6194 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC0 equ 0FEDh ;# 
# 6201 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC0 equ 0FEEh ;# 
# 6208 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF0 equ 0FEFh ;# 
# 6215 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON3 equ 0FF0h ;# 
# 6307 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON2 equ 0FF1h ;# 
# 6377 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON equ 0FF2h ;# 
# 6494 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PROD equ 0FF3h ;# 
# 6501 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PRODL equ 0FF3h ;# 
# 6508 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PRODH equ 0FF4h ;# 
# 6515 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TABLAT equ 0FF5h ;# 
# 6524 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTR equ 0FF6h ;# 
# 6531 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRL equ 0FF6h ;# 
# 6538 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRH equ 0FF7h ;# 
# 6545 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRU equ 0FF8h ;# 
# 6554 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLAT equ 0FF9h ;# 
# 6561 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PC equ 0FF9h ;# 
# 6568 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCL equ 0FF9h ;# 
# 6575 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLATH equ 0FFAh ;# 
# 6582 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLATU equ 0FFBh ;# 
# 6589 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
STKPTR equ 0FFCh ;# 
# 6695 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOS equ 0FFDh ;# 
# 6702 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSL equ 0FFDh ;# 
# 6709 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSH equ 0FFEh ;# 
# 6716 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSU equ 0FFFh ;# 
# 55 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTA equ 0F80h ;# 
# 192 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTB equ 0F81h ;# 
# 363 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTC equ 0F82h ;# 
# 538 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTD equ 0F83h ;# 
# 680 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTE equ 0F84h ;# 
# 883 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATA equ 0F89h ;# 
# 995 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATB equ 0F8Ah ;# 
# 1107 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATC equ 0F8Bh ;# 
# 1219 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATD equ 0F8Ch ;# 
# 1331 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATE equ 0F8Dh ;# 
# 1383 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISA equ 0F92h ;# 
# 1388 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRA equ 0F92h ;# 
# 1605 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISB equ 0F93h ;# 
# 1610 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRB equ 0F93h ;# 
# 1827 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISC equ 0F94h ;# 
# 1832 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRC equ 0F94h ;# 
# 2049 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISD equ 0F95h ;# 
# 2054 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRD equ 0F95h ;# 
# 2271 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISE equ 0F96h ;# 
# 2276 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRE equ 0F96h ;# 
# 2435 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
OSCTUNE equ 0F9Bh ;# 
# 2500 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIE1 equ 0F9Dh ;# 
# 2577 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIR1 equ 0F9Eh ;# 
# 2654 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
IPR1 equ 0F9Fh ;# 
# 2731 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIE2 equ 0FA0h ;# 
# 2797 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIR2 equ 0FA1h ;# 
# 2863 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
IPR2 equ 0FA2h ;# 
# 2929 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EECON1 equ 0FA6h ;# 
# 2995 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EECON2 equ 0FA7h ;# 
# 3002 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEDATA equ 0FA8h ;# 
# 3009 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEADR equ 0FA9h ;# 
# 3016 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEADRH equ 0FAAh ;# 
# 3023 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCSTA equ 0FABh ;# 
# 3028 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCSTA1 equ 0FABh ;# 
# 3233 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXSTA equ 0FACh ;# 
# 3238 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXSTA1 equ 0FACh ;# 
# 3489 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXREG equ 0FADh ;# 
# 3494 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXREG1 equ 0FADh ;# 
# 3501 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCREG equ 0FAEh ;# 
# 3506 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCREG1 equ 0FAEh ;# 
# 3513 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRG equ 0FAFh ;# 
# 3518 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRG1 equ 0FAFh ;# 
# 3525 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRGH equ 0FB0h ;# 
# 3532 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T3CON equ 0FB1h ;# 
# 3644 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3 equ 0FB2h ;# 
# 3651 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3L equ 0FB2h ;# 
# 3658 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3H equ 0FB3h ;# 
# 3665 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CMCON equ 0FB4h ;# 
# 3755 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CVRCON equ 0FB5h ;# 
# 3834 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ECCP1AS equ 0FB6h ;# 
# 3916 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PWM1CON equ 0FB7h ;# 
# 3986 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BAUDCON equ 0FB8h ;# 
# 3991 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BAUDCTL equ 0FB8h ;# 
# 4158 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCP2CON equ 0FBAh ;# 
# 4237 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2 equ 0FBBh ;# 
# 4244 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2L equ 0FBBh ;# 
# 4251 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2H equ 0FBCh ;# 
# 4258 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCP1CON equ 0FBDh ;# 
# 4355 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1 equ 0FBEh ;# 
# 4362 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1L equ 0FBEh ;# 
# 4369 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1H equ 0FBFh ;# 
# 4376 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON2 equ 0FC0h ;# 
# 4447 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON1 equ 0FC1h ;# 
# 4532 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON0 equ 0FC2h ;# 
# 4651 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRES equ 0FC3h ;# 
# 4658 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRESL equ 0FC3h ;# 
# 4665 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRESH equ 0FC4h ;# 
# 4672 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPCON2 equ 0FC5h ;# 
# 4734 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPCON1 equ 0FC6h ;# 
# 4804 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPSTAT equ 0FC7h ;# 
# 5025 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPADD equ 0FC8h ;# 
# 5032 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPBUF equ 0FC9h ;# 
# 5039 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T2CON equ 0FCAh ;# 
# 5110 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PR2 equ 0FCBh ;# 
# 5115 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
MEMCON equ 0FCBh ;# 
# 5220 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR2 equ 0FCCh ;# 
# 5227 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T1CON equ 0FCDh ;# 
# 5330 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1 equ 0FCEh ;# 
# 5337 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1L equ 0FCEh ;# 
# 5344 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1H equ 0FCFh ;# 
# 5351 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCON equ 0FD0h ;# 
# 5484 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
WDTCON equ 0FD1h ;# 
# 5512 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
HLVDCON equ 0FD2h ;# 
# 5517 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LVDCON equ 0FD2h ;# 
# 5782 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
OSCCON equ 0FD3h ;# 
# 5859 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T0CON equ 0FD5h ;# 
# 5936 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0 equ 0FD6h ;# 
# 5943 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0L equ 0FD6h ;# 
# 5950 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0H equ 0FD7h ;# 
# 5957 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
STATUS equ 0FD8h ;# 
# 6028 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2 equ 0FD9h ;# 
# 6035 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2L equ 0FD9h ;# 
# 6042 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2H equ 0FDAh ;# 
# 6049 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW2 equ 0FDBh ;# 
# 6056 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC2 equ 0FDCh ;# 
# 6063 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC2 equ 0FDDh ;# 
# 6070 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC2 equ 0FDEh ;# 
# 6077 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF2 equ 0FDFh ;# 
# 6084 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BSR equ 0FE0h ;# 
# 6091 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1 equ 0FE1h ;# 
# 6098 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1L equ 0FE1h ;# 
# 6105 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1H equ 0FE2h ;# 
# 6112 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW1 equ 0FE3h ;# 
# 6119 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC1 equ 0FE4h ;# 
# 6126 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC1 equ 0FE5h ;# 
# 6133 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC1 equ 0FE6h ;# 
# 6140 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF1 equ 0FE7h ;# 
# 6147 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
WREG equ 0FE8h ;# 
# 6159 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0 equ 0FE9h ;# 
# 6166 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0L equ 0FE9h ;# 
# 6173 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0H equ 0FEAh ;# 
# 6180 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW0 equ 0FEBh ;# 
# 6187 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC0 equ 0FECh ;# 
# 6194 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC0 equ 0FEDh ;# 
# 6201 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC0 equ 0FEEh ;# 
# 6208 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF0 equ 0FEFh ;# 
# 6215 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON3 equ 0FF0h ;# 
# 6307 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON2 equ 0FF1h ;# 
# 6377 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON equ 0FF2h ;# 
# 6494 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PROD equ 0FF3h ;# 
# 6501 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PRODL equ 0FF3h ;# 
# 6508 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PRODH equ 0FF4h ;# 
# 6515 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TABLAT equ 0FF5h ;# 
# 6524 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTR equ 0FF6h ;# 
# 6531 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRL equ 0FF6h ;# 
# 6538 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRH equ 0FF7h ;# 
# 6545 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRU equ 0FF8h ;# 
# 6554 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLAT equ 0FF9h ;# 
# 6561 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PC equ 0FF9h ;# 
# 6568 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCL equ 0FF9h ;# 
# 6575 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLATH equ 0FFAh ;# 
# 6582 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLATU equ 0FFBh ;# 
# 6589 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
STKPTR equ 0FFCh ;# 
# 6695 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOS equ 0FFDh ;# 
# 6702 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSL equ 0FFDh ;# 
# 6709 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSH equ 0FFEh ;# 
# 6716 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSU equ 0FFFh ;# 
# 55 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTA equ 0F80h ;# 
# 192 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTB equ 0F81h ;# 
# 363 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTC equ 0F82h ;# 
# 538 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTD equ 0F83h ;# 
# 680 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PORTE equ 0F84h ;# 
# 883 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATA equ 0F89h ;# 
# 995 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATB equ 0F8Ah ;# 
# 1107 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATC equ 0F8Bh ;# 
# 1219 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATD equ 0F8Ch ;# 
# 1331 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LATE equ 0F8Dh ;# 
# 1383 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISA equ 0F92h ;# 
# 1388 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRA equ 0F92h ;# 
# 1605 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISB equ 0F93h ;# 
# 1610 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRB equ 0F93h ;# 
# 1827 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISC equ 0F94h ;# 
# 1832 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRC equ 0F94h ;# 
# 2049 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISD equ 0F95h ;# 
# 2054 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRD equ 0F95h ;# 
# 2271 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TRISE equ 0F96h ;# 
# 2276 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
DDRE equ 0F96h ;# 
# 2435 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
OSCTUNE equ 0F9Bh ;# 
# 2500 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIE1 equ 0F9Dh ;# 
# 2577 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIR1 equ 0F9Eh ;# 
# 2654 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
IPR1 equ 0F9Fh ;# 
# 2731 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIE2 equ 0FA0h ;# 
# 2797 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PIR2 equ 0FA1h ;# 
# 2863 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
IPR2 equ 0FA2h ;# 
# 2929 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EECON1 equ 0FA6h ;# 
# 2995 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EECON2 equ 0FA7h ;# 
# 3002 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEDATA equ 0FA8h ;# 
# 3009 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEADR equ 0FA9h ;# 
# 3016 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
EEADRH equ 0FAAh ;# 
# 3023 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCSTA equ 0FABh ;# 
# 3028 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCSTA1 equ 0FABh ;# 
# 3233 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXSTA equ 0FACh ;# 
# 3238 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXSTA1 equ 0FACh ;# 
# 3489 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXREG equ 0FADh ;# 
# 3494 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TXREG1 equ 0FADh ;# 
# 3501 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCREG equ 0FAEh ;# 
# 3506 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCREG1 equ 0FAEh ;# 
# 3513 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRG equ 0FAFh ;# 
# 3518 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRG1 equ 0FAFh ;# 
# 3525 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SPBRGH equ 0FB0h ;# 
# 3532 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T3CON equ 0FB1h ;# 
# 3644 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3 equ 0FB2h ;# 
# 3651 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3L equ 0FB2h ;# 
# 3658 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR3H equ 0FB3h ;# 
# 3665 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CMCON equ 0FB4h ;# 
# 3755 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CVRCON equ 0FB5h ;# 
# 3834 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ECCP1AS equ 0FB6h ;# 
# 3916 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PWM1CON equ 0FB7h ;# 
# 3986 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BAUDCON equ 0FB8h ;# 
# 3991 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BAUDCTL equ 0FB8h ;# 
# 4158 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCP2CON equ 0FBAh ;# 
# 4237 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2 equ 0FBBh ;# 
# 4244 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2L equ 0FBBh ;# 
# 4251 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR2H equ 0FBCh ;# 
# 4258 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCP1CON equ 0FBDh ;# 
# 4355 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1 equ 0FBEh ;# 
# 4362 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1L equ 0FBEh ;# 
# 4369 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
CCPR1H equ 0FBFh ;# 
# 4376 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON2 equ 0FC0h ;# 
# 4447 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON1 equ 0FC1h ;# 
# 4532 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADCON0 equ 0FC2h ;# 
# 4651 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRES equ 0FC3h ;# 
# 4658 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRESL equ 0FC3h ;# 
# 4665 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
ADRESH equ 0FC4h ;# 
# 4672 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPCON2 equ 0FC5h ;# 
# 4734 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPCON1 equ 0FC6h ;# 
# 4804 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPSTAT equ 0FC7h ;# 
# 5025 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPADD equ 0FC8h ;# 
# 5032 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
SSPBUF equ 0FC9h ;# 
# 5039 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T2CON equ 0FCAh ;# 
# 5110 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PR2 equ 0FCBh ;# 
# 5115 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
MEMCON equ 0FCBh ;# 
# 5220 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR2 equ 0FCCh ;# 
# 5227 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T1CON equ 0FCDh ;# 
# 5330 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1 equ 0FCEh ;# 
# 5337 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1L equ 0FCEh ;# 
# 5344 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR1H equ 0FCFh ;# 
# 5351 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
RCON equ 0FD0h ;# 
# 5484 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
WDTCON equ 0FD1h ;# 
# 5512 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
HLVDCON equ 0FD2h ;# 
# 5517 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
LVDCON equ 0FD2h ;# 
# 5782 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
OSCCON equ 0FD3h ;# 
# 5859 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
T0CON equ 0FD5h ;# 
# 5936 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0 equ 0FD6h ;# 
# 5943 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0L equ 0FD6h ;# 
# 5950 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TMR0H equ 0FD7h ;# 
# 5957 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
STATUS equ 0FD8h ;# 
# 6028 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2 equ 0FD9h ;# 
# 6035 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2L equ 0FD9h ;# 
# 6042 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR2H equ 0FDAh ;# 
# 6049 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW2 equ 0FDBh ;# 
# 6056 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC2 equ 0FDCh ;# 
# 6063 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC2 equ 0FDDh ;# 
# 6070 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC2 equ 0FDEh ;# 
# 6077 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF2 equ 0FDFh ;# 
# 6084 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
BSR equ 0FE0h ;# 
# 6091 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1 equ 0FE1h ;# 
# 6098 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1L equ 0FE1h ;# 
# 6105 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR1H equ 0FE2h ;# 
# 6112 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW1 equ 0FE3h ;# 
# 6119 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC1 equ 0FE4h ;# 
# 6126 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC1 equ 0FE5h ;# 
# 6133 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC1 equ 0FE6h ;# 
# 6140 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF1 equ 0FE7h ;# 
# 6147 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
WREG equ 0FE8h ;# 
# 6159 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0 equ 0FE9h ;# 
# 6166 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0L equ 0FE9h ;# 
# 6173 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
FSR0H equ 0FEAh ;# 
# 6180 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PLUSW0 equ 0FEBh ;# 
# 6187 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PREINC0 equ 0FECh ;# 
# 6194 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTDEC0 equ 0FEDh ;# 
# 6201 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
POSTINC0 equ 0FEEh ;# 
# 6208 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INDF0 equ 0FEFh ;# 
# 6215 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON3 equ 0FF0h ;# 
# 6307 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON2 equ 0FF1h ;# 
# 6377 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
INTCON equ 0FF2h ;# 
# 6494 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PROD equ 0FF3h ;# 
# 6501 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PRODL equ 0FF3h ;# 
# 6508 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PRODH equ 0FF4h ;# 
# 6515 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TABLAT equ 0FF5h ;# 
# 6524 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTR equ 0FF6h ;# 
# 6531 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRL equ 0FF6h ;# 
# 6538 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRH equ 0FF7h ;# 
# 6545 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TBLPTRU equ 0FF8h ;# 
# 6554 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLAT equ 0FF9h ;# 
# 6561 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PC equ 0FF9h ;# 
# 6568 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCL equ 0FF9h ;# 
# 6575 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLATH equ 0FFAh ;# 
# 6582 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
PCLATU equ 0FFBh ;# 
# 6589 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
STKPTR equ 0FFCh ;# 
# 6695 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOS equ 0FFDh ;# 
# 6702 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSL equ 0FFDh ;# 
# 6709 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSH equ 0FFEh ;# 
# 6716 "D:/MPLAP/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\pic\include\proc\pic18f4620.h"
TOSU equ 0FFFh ;# 
	debug_source C
	FNROOT	_main
; #config settings
	config pad_punits      = on
	config apply_mask      = off
	config ignore_cmsgs    = off
	config default_configs = off
	config default_idlocs  = off
	config OSC = "HS"
	config FCMEN = "OFF"
	config IESO = "OFF"
	config PWRT = "OFF"
	config BOREN = "OFF"
	config BORV = "1"
	config WDT = "OFF"
	config WDTPS = "32768"
	config CCP2MX = "PORTC"
	config PBADEN = "OFF"
	config LPT1OSC = "OFF"
	config MCLRE = "ON"
	config STVREN = "ON"
	config LVP = "OFF"
	config XINST = "OFF"
	config CP0 = "OFF"
	config CP1 = "OFF"
	config CP2 = "OFF"
	config CP3 = "OFF"
	config CPB = "OFF"
	config CPD = "OFF"
	config WRT0 = "OFF"
	config WRT1 = "OFF"
	config WRT2 = "OFF"
	config WRT3 = "OFF"
	config WRTC = "OFF"
	config WRTB = "OFF"
	config WRTD = "OFF"
	config EBTR0 = "OFF"
	config EBTR1 = "OFF"
	config EBTR2 = "OFF"
	config EBTR3 = "OFF"
	config EBTRB = "OFF"
	file	".ca/dist/Config_1/production\PIC18F4620.production.s"
	line	#
psect	cinit,class=CODE,delta=1,reloc=2
global __pcinit
__pcinit:
global start_initialization
start_initialization:

global __initialization
__initialization:
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
movlb 0
goto _main	;jump to C main() function
psect	cstackCOMRAM,class=COMRAM,space=1,noexec,lowdata
global __pcstackCOMRAM
__pcstackCOMRAM:
??_main:	; 1 bytes @ 0x0
?_main:	; 2 bytes @ 0x0
	global	main@i
main@i:	; 2 bytes @ 0x0
	ds   2
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    0
;!    Data        0
;!    BSS         0
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM          127      2       2
;!    BANK0           128      0       0
;!    BANK1           256      0       0
;!    BANK2           256      0       0
;!    BANK3           256      0       0
;!    BANK4           256      0       0
;!    BANK5           256      0       0
;!    BANK6           256      0       0
;!    BANK7           256      0       0
;!    BANK8           256      0       0
;!    BANK9           256      0       0
;!    BANK10          256      0       0
;!    BANK11          256      0       0
;!    BANK12          256      0       0
;!    BANK13          256      0       0
;!    BANK14          256      0       0
;!    BANK15          128      0       0

;!
;!Pointer List with Targets:
;!
;!    None.


;!
;!Critical Paths under _main in COMRAM
;!
;!    None.
;!
;!Critical Paths under _main in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _main in BANK8
;!
;!    None.
;!
;!Critical Paths under _main in BANK9
;!
;!    None.
;!
;!Critical Paths under _main in BANK10
;!
;!    None.
;!
;!Critical Paths under _main in BANK11
;!
;!    None.
;!
;!Critical Paths under _main in BANK12
;!
;!    None.
;!
;!Critical Paths under _main in BANK13
;!
;!    None.
;!
;!Critical Paths under _main in BANK14
;!
;!    None.
;!
;!Critical Paths under _main in BANK15
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 2     2      0      30
;!                                              0 COMRAM     2     2      0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 0
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BITCOMRAM           7F      0       0       0        0.0%
;!EEDATA             400      0       0       0        0.0%
;!NULL                 0      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!COMRAM              7F      2       2       1        1.6%
;!STACK                0      0       0       2        0.0%
;!DATA                 0      0       0       3        0.0%
;!BITBANK0            80      0       0       4        0.0%
;!BANK0               80      0       0       5        0.0%
;!BITBANK1           100      0       0       6        0.0%
;!BANK1              100      0       0       7        0.0%
;!BITBANK2           100      0       0       8        0.0%
;!BANK2              100      0       0       9        0.0%
;!BITBANK3           100      0       0      10        0.0%
;!BANK3              100      0       0      11        0.0%
;!ABS                  0      0       0      12        0.0%
;!BITBANK4           100      0       0      13        0.0%
;!BANK4              100      0       0      14        0.0%
;!BITBANK5           100      0       0      15        0.0%
;!BANK5              100      0       0      16        0.0%
;!BITBANK6           100      0       0      17        0.0%
;!BANK6              100      0       0      18        0.0%
;!BITBANK7           100      0       0      19        0.0%
;!BANK7              100      0       0      20        0.0%
;!BITBANK8           100      0       0      21        0.0%
;!BANK8              100      0       0      22        0.0%
;!BITBANK9           100      0       0      23        0.0%
;!BANK9              100      0       0      24        0.0%
;!BITBANK10          100      0       0      25        0.0%
;!BANK10             100      0       0      26        0.0%
;!BITBANK11          100      0       0      27        0.0%
;!BANK11             100      0       0      28        0.0%
;!BITBANK12          100      0       0      29        0.0%
;!BANK12             100      0       0      30        0.0%
;!BITBANK13          100      0       0      31        0.0%
;!BANK13             100      0       0      32        0.0%
;!BITBANK14          100      0       0      33        0.0%
;!BANK14             100      0       0      34        0.0%
;!BITBANK15           80      0       0      35        0.0%
;!BANK15              80      0       0      36        0.0%
;!BITBIGSFR           80      0       0      37        0.0%
;!BIGRAM             F7F      0       0      38        0.0%
;!BIGSFR               0      0       0     200        0.0%
;!BITSFR               0      0       0     200        0.0%
;!SFR                  0      0       0     200        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 14 in file "app.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               2    0[COMRAM] unsigned int 
;; Return value:  Size  Location     Type
;;                  2    4[None  ] int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14  BANK15
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2,group=0
	file	"app.c"
	line	14
global __ptext0
__ptext0:
psect	text0
	file	"app.c"
	line	14
	
_main:
;incstack = 0
	callstack 31
	line	15
	
l686:
;app.c: 15:     ((*((volatile uint8_t*)(0xF94)))) = 0x00;
	movlw	low(0)
	movwf	((c:3988))^0f00h,c	;volatile
	line	16
;app.c: 16:     while(1)
	
l5:
	line	18
;app.c: 17:     {;app.c: 18:         ((*((volatile uint8_t*)(0xF8B)))) = 0x55;
	movlw	low(055h)
	movwf	((c:3979))^0f00h,c	;volatile
	line	19
;app.c: 19:         for(unsigned int i = 0 ; i <1000 ; i++)
	movlw	high(0)
	movwf	((c:main@i+1))^00h,c
	movlw	low(0)
	movwf	((c:main@i))^00h,c
	line	20
	
l692:
;app.c: 20:             __asm("");
	infsnz	((c:main@i))^00h,c
	incf	((c:main@i+1))^00h,c
	
l694:
		movlw	232
	subwf	 ((c:main@i))^00h,c,w
	movlw	3
	subwfb	((c:main@i+1))^00h,c,w
	btfss	status,0
	goto	u11
	goto	u10

u11:
	goto	l692
u10:
	line	21
	
l696:
;app.c: 21:         ((*((volatile uint8_t*)(0xF8B)))) = 0xAA;
	movlw	low(0AAh)
	movwf	((c:3979))^0f00h,c	;volatile
	goto	l5
	global	start
	goto	start
	callstack 0
	line	25
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,90
	GLOBAL	__activetblptr
__activetblptr	EQU	0
	psect	intsave_regs,class=BIGRAM,space=1,noexec
	PSECT	rparam,class=COMRAM,space=1,noexec
	GLOBAL	__Lrparam
	FNCONF	rparam,??,?
	GLOBAL	___rparam_used
	___rparam_used EQU 1
	GLOBAL	___param_bank
	___param_bank EQU 0
GLOBAL	__Lparam, __Hparam
GLOBAL	__Lrparam, __Hrparam
__Lparam	EQU	__Lrparam
__Hparam	EQU	__Hrparam
	end
