/* 
 * File:   app.c
 * Author: yossef
 *
 * Created on January 30, 2023, 11:16 PM
 */

#include "app.h"

uint8_t str[] = "AT\r\n";
void main(void)
{
    Std_ReturnType ret = app_inisialize();
     ret &= EUSART_WriteStr_Blocking(str);
    while(1)
    {
        
    }
}