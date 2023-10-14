/* 
 * File:   lcd.h
 * Author: yossef
 *
 * Created on March 4, 2023, 4:12 AM
 */

#ifndef LCD_H
#define	LCD_H

/*------------ includes-------------------*/
#include"../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "lcd_cfg.h"
/*-----------Macros-------------------------*/
/*lcd_command*/
#define _LCD_CLEAR                                              0x01
#define _LCD_RE_HOME                                            0x02

#define _LCD_DISPLAY_OFF                                        0x08
#define _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF                    0x0C
#define _LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF                     0x0E
#define _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON                     0x0D
#define _LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON                      0x0F

#define _LCD_ENTRY_MODE_AC_INC_SH_OFF                           0x06
#define _LCD_ENTRY_MODE_AC_DEC_SH_OFF                           0x04
#define _LCD_ENTRY_MODE_AC_INC_SH_R                             0x07
#define _LCD_ENTRY_MODE_AC_DEC_SH_L                             0x05

#define _LCD_SHIFT_CURSOR_LEFT                                  0x10
#define _LCD_SHIFT_CURSOR_RIGHT                                 0x14
#define _LCD_SHIFT_ALL_LEFT                                     0x18
#define _LCD_SHIFT_ALL_RIGHT                                    0x1C

#define _LCD_FUN_SET_4BIT_1LINE_5X8                             0x20
#define _LCD_FUN_SET_4BIT_2LINE_5X8                             0x28
#define _LCD_FUN_SET_4BIT_2LINE_5X11                            0x2C
#define _LCD_FUN_SET_8BIT_1LINE_5X8                             0x30
#define _LCD_FUN_SET_8BIT_2LINE_5X8                             0x38
#define _LCD_FUN_SET_8BIT_2LINE_5X11                            0x3C

#define _LCD_RS_SEND_DATA                                       high
#define _LCD_RS_SEND_INST                                       low

#define _LCD_CGRAM_START                                        0x40
#define _LCD_DDRAM_START                                        0x80

#define _LCD_DDRAM_ROW1                                         0x80
#define _LCD_DDRAM_ROW2                                         0xC0
#define _LCD_DDRAM_ROW3                                         0x94
#define _LCD_DDRAM_ROW4                                         0xd4

#define ROW1                                                    1
#define ROW2                                                    2
#define ROW3                                                    3
#define ROW4                                                    4

#define _CUSTOM_CHAR_SIZE                                       8


/*-----------Macro_functions-----------------*/


/*-----------user data types-----------------*/
typedef struct {
    pinConfig_t lcd_data[8];
    pinConfig_t lcd_RS;
    pinConfig_t lcd_en;
}lcd_8bit_t;

typedef struct{
    pinConfig_t lcd_data[4];
    pinConfig_t lcd_RS;
    pinConfig_t lcd_en;
}lcd_4bit_t;
/*----------------interfaces prototypes-------*/


/*------------4bit-------------*/
Std_ReturnType lcd_4bit_init(const lcd_4bit_t* _lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* _lcd , uint8_t comm);
Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t* _lcd ,uint8_t data);
Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t* _lcd ,uint8_t data , uint8_t row , uint8_t col);
Std_ReturnType lcd_4bit_send_str(const lcd_4bit_t* _lcd ,uint8_t* str);
Std_ReturnType lcd_4bit_send_str_pos(const lcd_4bit_t* _lcd ,uint8_t* str, uint8_t row , uint8_t col);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* _lcd , uint8_t row , uint8_t col , const uint8_t _chr[] , uint8_t mem_pos);







/*--------8bit----------------*/
Std_ReturnType lcd_8bit_init(const lcd_8bit_t* _lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* _lcd , uint8_t comm);
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t* _lcd ,uint8_t data);
Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t* _lcd ,uint8_t data , uint8_t row , uint8_t col);
Std_ReturnType lcd_8bit_send_str(const lcd_8bit_t* _lcd ,uint8_t* str);
Std_ReturnType lcd_8bit_send_str_pos(const lcd_8bit_t* _lcd ,uint8_t* str, uint8_t row , uint8_t col);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t* _lcd, uint8_t row , uint8_t col , const uint8_t _chr[] , uint8_t mem_pos);

/*---------helper---------*/
void convert_byte_to_str(uint8_t val , uint8_t* str);
void convert_ushort_to_str(uint16_t val , uint8_t* str);
void convert_uint_to_str(uint32_t val , uint8_t* str);
void convert_float_to_str(float val , uint8_t* str , uint8_t str_size);
#endif	/* LCD_H */

