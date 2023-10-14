/* 
 * File:   lcd.c
 * Author: yossef
 *
 * Created on March 4, 2023, 4:12 AM
 */
#include "lcd.h"

/*-----------static Functions----------*/
static Std_ReturnType lcd_4bit_send_en_signal(const lcd_4bit_t* _lcd);
static Std_ReturnType lcd_8bit_send_en_signal(const lcd_8bit_t* _lcd);
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* _lcd , uint8_t val);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* _lcd , uint8_t row , uint8_t colum);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* _lcd , uint8_t row , uint8_t colum);

/*------------helper func--------------------------------------*/

/*------------4bit interface-----------------------------------------------------------------*/
Std_ReturnType lcd_4bit_init(const lcd_4bit_t* _lcd){
  Std_ReturnType ret = E_OK;
  uint8_t l_pin_count = 0;
  if(!(_lcd))
    ret = E_NOT;
  else{
      ret = gpio_pin_intialize (&(_lcd->lcd_RS));
      ret = gpio_pin_intialize (&(_lcd->lcd_en));
      for(l_pin_count = 0; l_pin_count<4 ; l_pin_count++)
        ret = gpio_pin_intialize (&(_lcd->lcd_data[l_pin_count]));
      
      __delay_ms(20);
      ret = lcd_4bit_send_command (_lcd , _LCD_FUN_SET_8BIT_2LINE_5X8);
      __delay_ms(5);
      ret = lcd_4bit_send_command (_lcd , _LCD_FUN_SET_8BIT_2LINE_5X8);
      __delay_us(150);
      ret = lcd_4bit_send_command (_lcd , _LCD_FUN_SET_8BIT_2LINE_5X8);
      
      ret = lcd_4bit_send_command (_lcd , _LCD_CLEAR);
      ret = lcd_4bit_send_command (_lcd , _LCD_RE_HOME);
      ret = lcd_4bit_send_command (_lcd , _LCD_FUN_SET_4BIT_2LINE_5X8);
      ret = lcd_4bit_send_command (_lcd , _LCD_ENTRY_MODE_AC_INC_SH_OFF);
      ret = lcd_4bit_send_command (_lcd , _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
      ret = lcd_4bit_send_command (_lcd , _LCD_DDRAM_START);
    }
  return ret;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* _lcd , uint8_t comm){
  Std_ReturnType ret = E_OK;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      /*------Dont Forget to set RS pin to low to send command-------*/
      ret = gpio_pin_write_logic (&(_lcd->lcd_RS), _LCD_RS_SEND_INST);
      /*---send High bits first---*/
      ret = lcd_send_4bits (_lcd , (comm >> 4)); // 0100
      ret = lcd_4bit_send_en_signal ((_lcd)); // send enable signal to send high bits
      ret = lcd_send_4bits (_lcd , comm); // 0001
      ret = lcd_4bit_send_en_signal ((_lcd));
    }
  return ret;
}

Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t* _lcd ,uint8_t data){
  Std_ReturnType ret = E_OK;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      /*------Dont Forget to set RS pin to high to send data-------*/
      ret = gpio_pin_write_logic (&(_lcd->lcd_RS), _LCD_RS_SEND_DATA);
      /*---send High bits first---*/
      ret = lcd_send_4bits (_lcd , (data >> 4));
      ret = lcd_4bit_send_en_signal ((_lcd)); // send enable signal to send high bits
      ret = lcd_send_4bits (_lcd , data);
      ret = lcd_4bit_send_en_signal ((_lcd));
    }
  return ret;
}

Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t* _lcd ,uint8_t data , uint8_t row , uint8_t col){
  Std_ReturnType ret = E_OK;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      ret = lcd_4bit_set_cursor (_lcd , row , col);
      ret = lcd_4bit_send_char (_lcd , data);
    }
  return ret;
}
Std_ReturnType lcd_4bit_send_str(const lcd_4bit_t* _lcd ,uint8_t* str){
  Std_ReturnType ret = E_OK;
  uint8_t l_str_count = 0;
  if((!(_lcd)) || (!(str)))
    ret = E_NOT;
  else{
      while(*str)
        ret = lcd_4bit_send_char (_lcd , *str++);
    }
  return ret;
}
Std_ReturnType lcd_4bit_send_str_pos(const lcd_4bit_t* _lcd ,uint8_t* str, uint8_t row , uint8_t col){
  Std_ReturnType ret = E_OK;
  uint8_t l_str_count = 0;
  if((!(_lcd)) || (!(str)))
    ret = E_NOT;
  else{
      ret = lcd_4bit_set_cursor (_lcd , row , col);
      while(*str)
        ret = lcd_4bit_send_char (_lcd , *str++);
    }
  return ret;
}
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* _lcd , uint8_t row , uint8_t col , const uint8_t _chr[] , uint8_t mem_pos){
  Std_ReturnType ret = E_OK;
  uint8_t l_chr_count = 0;
  if((!(_lcd)))
    ret = E_NOT;
  else
    {
      ret = lcd_4bit_send_command (_lcd ,(_LCD_CGRAM_START + (mem_pos*8)));
      for(;l_chr_count < _CUSTOM_CHAR_SIZE ;++l_chr_count)
        ret = lcd_4bit_send_char (_lcd , _chr[l_chr_count]);
      ret = lcd_4bit_send_char_pos (_lcd , mem_pos , row , col);
    }
  return ret;
}

/*---------------8bit interface------------------------------------------------*/
Std_ReturnType lcd_8bit_init(const lcd_8bit_t* _lcd){
  Std_ReturnType ret = E_OK;
  uint8_t l_pin_count = 0;
  if(!(_lcd))
    ret = E_NOT;
  else{
      ret = gpio_pin_intialize (&(_lcd->lcd_RS));
      ret = gpio_pin_intialize (&(_lcd->lcd_en));
      for(l_pin_count = 0; l_pin_count<8 ; l_pin_count++)
        ret = gpio_pin_intialize (&(_lcd->lcd_data[l_pin_count]));
      __delay_ms(20);
      ret = lcd_8bit_send_command (_lcd , _LCD_FUN_SET_8BIT_2LINE_5X8);
      __delay_ms(5);
      ret = lcd_8bit_send_command (_lcd , _LCD_FUN_SET_8BIT_2LINE_5X8);
      __delay_us(150);
      ret = lcd_8bit_send_command (_lcd , _LCD_FUN_SET_8BIT_2LINE_5X8);
      ret = lcd_8bit_send_command (_lcd , _LCD_CLEAR);
      ret = lcd_8bit_send_command (_lcd , _LCD_RE_HOME);
      ret = lcd_8bit_send_command (_lcd , _LCD_ENTRY_MODE_AC_INC_SH_OFF);
      ret = lcd_8bit_send_command (_lcd , _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
      ret = lcd_8bit_send_command (_lcd , _LCD_DDRAM_START);
    }
  return ret;
}
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* _lcd , uint8_t comm){
  Std_ReturnType ret = E_OK;
  uint8_t l_pin_count = 0;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      ret = gpio_pin_write_logic (&(_lcd->lcd_RS), _LCD_RS_SEND_INST);
      /*---send High bits first---*/
      for(l_pin_count = 0 ; l_pin_count <8 ; l_pin_count++)
        ret = gpio_pin_write_logic (&(_lcd->lcd_data[l_pin_count]) , (BIT_READ(comm , l_pin_count)));
  
      ret = lcd_8bit_send_en_signal ((_lcd));
    }
  return ret;
}
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t* _lcd ,uint8_t data){
  Std_ReturnType ret = E_OK;
    uint8_t l_pin_count = 0;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      /*------Dont Forget to set RS pin to low to send data-------*/
      ret = gpio_pin_write_logic (&(_lcd->lcd_RS), _LCD_RS_SEND_DATA);
      for(l_pin_count = 0 ; l_pin_count <8 ; l_pin_count++)
        ret = gpio_pin_write_logic (&(_lcd->lcd_data[l_pin_count]) , (BIT_READ(data , l_pin_count)));
      
      ret = lcd_8bit_send_en_signal (_lcd);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t* _lcd ,uint8_t data , uint8_t row , uint8_t col){
  Std_ReturnType ret = E_OK;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      ret = lcd_8bit_set_cursor (_lcd , row , col);
      ret = lcd_8bit_send_char (_lcd , data);
    }
  return ret;
}
Std_ReturnType lcd_8bit_send_str(const lcd_8bit_t* _lcd ,uint8_t* str){
  Std_ReturnType ret = E_OK;
  if((!(_lcd)) || (!(str)))
    ret = E_NOT;
  else{
      while (*str)
          lcd_8bit_send_char (_lcd , (*str++));
    }
  return ret;
}
Std_ReturnType lcd_8bit_send_str_pos(const lcd_8bit_t* _lcd ,uint8_t* str, uint8_t row , uint8_t col){
  Std_ReturnType ret = E_OK;
  if((!(_lcd)) || (!(str)))
    ret = E_NOT;
  else{
      ret = lcd_8bit_set_cursor (_lcd , row , col);
      ret = lcd_8bit_send_str (_lcd , str);
    }
  return ret;
}
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t* _lcd , uint8_t row , uint8_t col , const uint8_t _chr[] , uint8_t mem_pos){
  Std_ReturnType ret = E_OK;
  uint8_t l_chr_count = 0;
  if((!(_lcd)))
    ret = E_NOT;
  else{
      ret = lcd_8bit_send_command (_lcd ,(_LCD_CGRAM_START + (mem_pos*8)));
      for(;l_chr_count < _CUSTOM_CHAR_SIZE ;++l_chr_count)
        ret = lcd_8bit_send_char (_lcd , _chr[l_chr_count]);
      ret = lcd_8bit_send_char_pos (_lcd , mem_pos , row , col);
    }
  return ret;
}


/*------STATIC FUNCTION DEF------------- */
static Std_ReturnType lcd_4bit_send_en_signal(const lcd_4bit_t* _lcd){
  Std_ReturnType ret = E_OK;
  if(!(_lcd))
    ret = E_NOT;
  else{
      ret = gpio_pin_write_logic (&(_lcd->lcd_en) , high);
      __delay_us(5);
      ret = gpio_pin_write_logic (&(_lcd->lcd_en) , low);
    }
  return ret;
}
static Std_ReturnType lcd_8bit_send_en_signal(const lcd_8bit_t* _lcd){
  Std_ReturnType ret = E_OK;

  if(!(_lcd))
    ret = E_NOT;
  else{
      ret = gpio_pin_write_logic (&(_lcd->lcd_en) , high);
      __delay_us(5);
      ret = gpio_pin_write_logic (&(_lcd->lcd_en) , low);     
    }
  return ret;
}
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* _lcd , uint8_t val){
  Std_ReturnType ret = E_OK;
  uint8_t l_count = 0;
  for(;l_count < 4 ; l_count++)
    ret = gpio_pin_write_logic (&(_lcd->lcd_data[l_count]) , (BIT_READ(val ,l_count)));
  return ret; 
}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* _lcd , uint8_t row , uint8_t colum){
  Std_ReturnType ret = E_OK;
  if(!(_lcd))
    ret = E_NOT;
  else
    {
      --colum;
      switch(row)
        {
        case ROW1: ret = lcd_8bit_send_command (_lcd , _LCD_DDRAM_ROW1 + colum);break;
        case ROW2: ret = lcd_8bit_send_command (_lcd , _LCD_DDRAM_ROW2 + colum);break;
        case ROW3: ret = lcd_8bit_send_command (_lcd , _LCD_DDRAM_ROW3 + colum);break;
        case ROW4: ret = lcd_8bit_send_command (_lcd , _LCD_DDRAM_ROW4 + colum);break;
        default: ret = E_NOT;
        }
    }
  return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* _lcd , uint8_t row , uint8_t colum){
  Std_ReturnType ret = E_OK;
  if(!(_lcd))
    ret = E_NOT;
  else
    {
      --colum;
      switch(row)
        {
        case ROW1: ret = lcd_4bit_send_command (_lcd , (_LCD_DDRAM_ROW1 + colum));break;
        case ROW2: ret = lcd_4bit_send_command (_lcd , ((_LCD_DDRAM_ROW2) + colum));break;
        case ROW3: ret = lcd_4bit_send_command (_lcd , (_LCD_DDRAM_ROW3 + colum));break;
        case ROW4: ret = lcd_4bit_send_command (_lcd , (_LCD_DDRAM_ROW4 + colum));break;
        default: ret = E_NOT;
        }
    }
  return ret;
}

/*----------------------HELPER FUNCTION DEF --------------*/

void convert_byte_to_str(uint8_t val , uint8_t* str){
  uint8_t Temp_str[4] = {0};
  uint8_t l_counter = 0;
    if(!(str))
        return;
  else{
      memset (str , '\0' ,3);
      str[3] = '\0';
      snprintf((char*)Temp_str , 4 ,"%u" , val);
      while(Temp_str[l_counter])
        {
            str[l_counter] = Temp_str[l_counter];
            ++l_counter;
        }  
    }
  return;
}
void convert_ushort_to_str(uint16_t val , uint8_t* str){
  uint8_t Temp_str[6] = {0};
  uint8_t l_counter = 0;
    if(!(str))
        return;
  else{
      memset (str , ' ' , 5);
      str[5] = '\0';
      snprintf((char*)Temp_str ,6 ,"%u" , val);
      while(Temp_str[l_counter])
        {
            str[l_counter] = Temp_str[l_counter];
            ++l_counter;
        }  
    }
  return;
}
void convert_uint_to_str(uint32_t val , uint8_t* str){
  uint8_t Temp_str[11] = {0};
  uint8_t l_counter = 0;
    if(!(str))
        return;
  else{
      memset (str , '\0' , 10);
      str[10] = '\0';
      snprintf((char*)Temp_str , 11 ,"%lu" , val);
      while(Temp_str[l_counter])
        {
            str[l_counter] = Temp_str[l_counter];
            ++l_counter;
        }  
    }
  return;
}
void convert_float_to_str(float val , uint8_t* str , uint8_t str_size)
{
  uint8_t* Temp_str = (uint8_t*)calloc(str_size , sizeof(uint8_t));
  uint8_t l_counter = 0;
    if(!(str))
        return;
  else{
      memset (str , ' ' , str_size-1);
      str[str_size-1] = '\0';
      snprintf((char*)Temp_str , str_size ,"%.2f" , val);
      while(Temp_str[l_counter])
        {
            str[l_counter] = Temp_str[l_counter];
            ++l_counter;
        }
      free(Temp_str);
      Temp_str = NULL;
    }
  return;  
}