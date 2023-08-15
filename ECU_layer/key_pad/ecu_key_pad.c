/* 
 * File:   ecu_key_pad.h
 * Author: ammar.yasser
 *
 * Created on 06 ?????, 2023, 04:57 ?
 */  
#include "ecu_key_pad.h"

static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COULMNS] = {{'7','8','9','/'}
                                                             ,{'4','5','6','*'}
                                                             ,{'1','2','3','-'}
                                                             ,{'#','0','=','+'}
};







/**
 * @brief initialize the keypad
 * @param keypad a pointer to keypad
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType keypad_initialize(const keypad_t *keypad)
{
    Std_ReturnType ret = E_OK;
    if(keypad==NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(uint8 i=0;i<KEYPAD_ROWS;i++)
        {
            ret = gpio_pin_initialize(&(keypad->keypad_ROWS_pins[i]));
        }
        for(uint8 i=0;i<KEYPAD_ROWS;i++)
        {
            ret = gpio_pin_direction_initialize(&(keypad->keypad_coulmns_pins[i]));
        }

    }
     return ret;
}

/**
 * @brief get the value from keypad
 * @param keypad a pointer to keypad
 * @param value
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue
 */
Std_ReturnType keypad_get_value(const keypad_t *keypad,uint8 *value)
{
    Std_ReturnType ret = E_OK;
    logic_t log = GPIO_LOW;
    uint8 row_counter=0,counter=0,coulmn_counter=0; 
    if((keypad==NULL)||(value==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(row_counter=0;row_counter<KEYPAD_ROWS;row_counter++)
        {
            for(counter=0;counter<KEYPAD_ROWS;counter++)
            {
                ret = gpio_pin_write_logic(&(keypad->keypad_ROWS_pins[counter]),GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_ROWS_pins[row_counter]),GPIO_HIGH);
            for(coulmn_counter=0;coulmn_counter<KEYPAD_COULMNS;coulmn_counter++)
            {
                ret = gpio_pin_read_logic(&(keypad->keypad_coulmns_pins[coulmn_counter]),&log);
                if(log == GPIO_HIGH)
                {
                    *value = btn_values [row_counter][coulmn_counter];
                }
                
            }
        }
    }
     return ret;
}
        