/* 
 * File:   ecu_chr_lcd_cfg.h
 * Author: ammar.yasser
 *
 * Created on 13 ?????, 2023, 02:18 ?
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/******Includes**********/
#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/*********Macro Declaration***********/


#define LCD_CLEAR_DISPLAY                   0x01
#define LCD_RETURN_HOME                     0x02
#define LCD_INC_SHIFT_OFF                   0x06
#define LCD_INC_SHIFT_ON                    0x07
#define LCD_DEC_SHIFT_OFF                   0x04
#define LCD_DEC_SHIFT_ON                    0x05

#define CURSOR_MOVE_SHIFT_LEFT              0x10
#define CURSOR_MOVE_SHIFT_RIGHT             0x14 
#define DISBLAY_SHIFT_LEFT                  0x18
#define DISBLAY_SHIFT_RIGHT                 0x1C

#define DISBLAY_OFF                         0x08
#define DISPLAY_ON_UNDERLINE_ON_BLOCK_ON    0x0F
#define DISPLAY_ON_UNDERLINE_OFF_BLOCK_ON   0x0D
#define DISPLAY_ON_UNDERLINE_OFF_BLOCK_OFF  0x0C
#define DISPLAY_ON_UNDERLINE_ON_BLOCK_OFF   0x0E

#define LCD_4BIT_MODE_2LINE                 0x28
#define LCD_8BIT_MODE_2LINE                 0x38

#define LCD_CGRAM_START                     0x40
#define LCD_DDRAM_START                     0x80

#define ROW_1                               (uint8)1
#define ROW_2                               (uint8)2
#define ROW_3                               (uint8)3
#define ROW_4                               (uint8)4





/*********Macro Function Declaration***********/

/*********Data Types Declaration***********/

typedef struct
{
    pin_config lcd_data[4];
    pin_config lcd_enable;
    pin_config lcd_rs;
}lcd_4bit_t;
typedef struct
{
    pin_config lcd_data[8];
    pin_config lcd_enable;
    pin_config lcd_rs;
}lcd_8bit_t;

/*********Function Declaration***********/

Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd_obj);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd_obj,uint8 command);
Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd_obj,uint8 chr);
Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column,uint8 chr);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd_obj,uint8 *string);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column,uint8 *string);
Std_ReturnType lcd_4bit_send_custome_chr(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column,uint8 *chr,uint8 mem_pos);

Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd_obj);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd_obj,uint8 command);
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t *lcd_obj,uint8 chr);
Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 chr);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd_obj,uint8 *string);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 *string);
Std_ReturnType lcd_8bit_send_custome_chr(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 *chr,uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value,uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value,uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value,uint8 *str);

#endif	/* ECU_CHR_LCD_H */

