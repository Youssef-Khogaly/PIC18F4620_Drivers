#include "keypad.h"
/*--------Static Global Variable---------*/
const static uint8_t keypad_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_ROWS] = {
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'#','0','=','+'}
};
/*---------------------------------------*/

/**
 * @brief
 * @param _keypad
 * @return 
 */
Std_ReturnType ecu_keypad_inisialize(const keypad_t* _keypad)
{
  Std_ReturnType ret = E_OK;
  uint32_t count = 0;
  if(!(_keypad))
    ret = E_NOT;
  else
    {
      for(;count < ECU_KEYPAD_ROWS ; count++)
        ret = gpio_pin_intialize (&(_keypad->keypad_rows_pins[count]));
      for(count = 0 ; count < ECU_KEYPAD_COL ; count++)
        ret = gpio_pin_intialize (&(_keypad->keypad_col_pins[count]));
    }
  return ret;
}
/**
 * @brief
 * @param _keypad
 * @param value
 * @return 
 */
Std_ReturnType ecu_keypad_scan_value(const keypad_t* _keypad , uint8_t* value)
{
  Std_ReturnType ret = E_OK;
  uint32_t rows = 0, cols = 0;
  logic_t col_logic = low;
  if((!(_keypad)) || (!(value)))
    ret = E_NOT;
  else
    {
      for(rows = 0 ; rows < ECU_KEYPAD_ROWS && !(col_logic); rows++)
        {
          ret = gpio_pin_write_logic (&(_keypad->keypad_rows_pins[rows]) , high);
          for(cols = 0 ; cols < ECU_KEYPAD_COL && !(col_logic) ; cols++)
            {
              ret = gpio_pin_read_logic (&(_keypad->keypad_col_pins[cols]) , &col_logic);
              if(col_logic)
                *value = keypad_values[rows][cols];
            }
          ret = gpio_pin_write_logic (&(_keypad->keypad_rows_pins[rows]) , low);
        }
    }
  return ret;
}
