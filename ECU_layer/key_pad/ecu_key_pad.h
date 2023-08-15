/* 
 * File:   ecu_key_pad.h
 * Author: ammar.yasser
 *
 * Created on 06 ?????, 2023, 04:57 ?
 */

#ifndef ECU_KEY_PAD_H
#define	ECU_KEY_PAD_H

/******Includes**********/
#include "ecu_key_pad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*********Macro Declaration***********/

#define KEYPAD_ROWS      4
#define KEYPAD_COULMNS   4


/*********Macro Function Declaration***********/

/*********Data Types Declaration***********/
typedef struct
{
    pin_config  keypad_ROWS_pins[KEYPAD_ROWS];
    pin_config  keypad_coulmns_pins[KEYPAD_COULMNS];
}keypad_t;
/*********Function Declaration***********/

Std_ReturnType keypad_initialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad,uint8 *value);



#endif	/* ECU_KEY_PAD_H */

