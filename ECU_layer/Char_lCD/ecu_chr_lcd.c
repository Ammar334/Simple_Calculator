/* 
 * File:   ecu_chr_lcd_cfg.h
 * Author: ammar.yasser
 *
 * Created on 13 ?????, 2023, 02:18 ?
 */

#include "ecu_chr_lcd.h"
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column);
static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd_obj,uint8 data_command);
static Std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t *lcd_obj);

static Std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t *lcd_obj);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column);


/**
 * 
 * @param lcd_obj
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd_obj)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(lcd_obj->lcd_enable));
        ret = gpio_pin_initialize(&(lcd_obj->lcd_rs));
        
        for(int i=0;i<4;i++)
        {
            ret = gpio_pin_initialize(&(lcd_obj->lcd_data[i]));
        }
         __delay_ms(20);
        ret = lcd_4bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd_obj,LCD_CLEAR_DISPLAY);
        ret = lcd_4bit_send_command(lcd_obj,LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd_obj,LCD_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd_obj,DISPLAY_ON_UNDERLINE_OFF_BLOCK_OFF);
        ret = lcd_4bit_send_command(lcd_obj,LCD_4BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd_obj,LCD_DDRAM_START);
        
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param command
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd_obj,uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_rs),GPIO_LOW);
        ret = lcd_send_4bit(lcd_obj,(command>>4));
        ret = lcd_4bit_send_enable(lcd_obj);
        ret = lcd_send_4bit(lcd_obj,command);
        ret = lcd_4bit_send_enable(lcd_obj);
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param chr
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd_obj,uint8 chr)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_rs),GPIO_HIGH);
        ret = lcd_send_4bit(lcd_obj,(chr>>4));
        ret = lcd_4bit_send_enable(lcd_obj);
        ret = lcd_send_4bit(lcd_obj,chr);
        ret = lcd_4bit_send_enable(lcd_obj);
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param chr
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column,uint8 chr)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd_obj,row,column);
        ret = lcd_4bit_send_char(lcd_obj,chr);
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param string
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd_obj,uint8 *string)
{
    Std_ReturnType ret = E_OK;
    if((lcd_obj == NULL)||(string==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*string)
        {
            ret = lcd_4bit_send_char(lcd_obj,*string++);

        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param string
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column,uint8 *string)
{
    Std_ReturnType ret = E_OK;
    if((lcd_obj == NULL)||(string==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd_obj,row,column);
        ret = lcd_4bit_send_string(lcd_obj,string);
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param chr
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_4bit_send_custome_chr(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column,uint8 *chr,uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_send_command(lcd_obj,(LCD_CGRAM_START +(mem_pos*8)));
        for(int i=0;i<8;i++)
        {
            ret = lcd_4bit_send_char(lcd_obj,chr[i]);
        }
        ret = lcd_4bit_send_char_pos(lcd_obj,row,column,mem_pos);
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd_obj)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(lcd_obj->lcd_enable));
        ret = gpio_pin_initialize(&(lcd_obj->lcd_rs));

        for(int i=0;i<8;i++)
        {
            ret = gpio_pin_initialize(&(lcd_obj->lcd_data[i]));
        }
        
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd_obj,LCD_CLEAR_DISPLAY);
        ret = lcd_8bit_send_command(lcd_obj,LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd_obj,LCD_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd_obj,DISPLAY_ON_UNDERLINE_OFF_BLOCK_OFF);
        ret = lcd_8bit_send_command(lcd_obj,LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd_obj,LCD_DDRAM_START);
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param command
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd_obj,uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_rs),GPIO_LOW);
        for(int i=0;i<8;i++)
        {
            ret = gpio_pin_write_logic(&(lcd_obj->lcd_data[i]),(command>>i)& (uint8)0x01);
        }
        ret = lcd_8bit_send_enable(lcd_obj);
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param chr
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t *lcd_obj,uint8 chr)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_rs),GPIO_HIGH);
        for(int i=0;i<8;i++)
        {
            ret = gpio_pin_write_logic(&(lcd_obj->lcd_data[i]),(chr>>i)& (uint8)0x01);
        }
        ret = lcd_8bit_send_enable(lcd_obj);
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param chr
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 chr)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd_obj,row,column);
        ret = lcd_8bit_send_char(lcd_obj,chr);
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param string
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd_obj,uint8 *string)
{
    Std_ReturnType ret = E_OK;
    if((lcd_obj == NULL)||(string==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*string)
        {
            ret = lcd_8bit_send_char(lcd_obj,*string++);
        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param string
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 *string)
{
    Std_ReturnType ret = E_OK;
    if((lcd_obj == NULL)||(string==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd_obj,row,column);
        ret = lcd_8bit_send_string(lcd_obj,string);
        
    }
    return ret;
}

/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType lcd_8bit_send_custome_chr(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 *chr,uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_command(lcd_obj,(LCD_CGRAM_START +(mem_pos*8)));
        for(int i=0;i<8;i++)
        {
            ret = lcd_8bit_send_char(lcd_obj,chr[i]);
        }
        ret = lcd_8bit_send_char_pos(lcd_obj,row,column,mem_pos);
        
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_byte_to_string(uint8 value,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_short_to_string(uint16 value,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'\0',6);
        sprintf(str,"%i",value);
        
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_int_to_string(uint32 value,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }
    return ret;
}


static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd_obj,uint8 data_command)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            ret = gpio_pin_write_logic(&(lcd_obj->lcd_data[i]),(data_command >> i) & (uint8)0x01);
        }
        
    }
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t *lcd_obj)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_enable),GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_enable),GPIO_LOW);
        
    }
    return ret;
}

static Std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t *lcd_obj)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_enable),GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd_obj->lcd_enable),GPIO_LOW);
        
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd_obj,uint8 row,uint8 column)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        column--;
        switch (row)
        {
            case ROW_1:
                ret = lcd_8bit_send_command(lcd_obj,(0x80 + column));
            break;
            case ROW_2:
                ret = lcd_8bit_send_command(lcd_obj,(0xC0 + column));
            break;
            case ROW_3:
                ret = lcd_8bit_send_command(lcd_obj,(0x94 + column));
            break;
            case ROW_4:
                ret = lcd_8bit_send_command(lcd_obj,(0xD4 + column));
            break;
            default: ;
        }
        
        
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd_obj,uint8 row,uint8 column)
{
    Std_ReturnType ret = E_OK;
    if(lcd_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        column--;
        switch (row)
        {
            case ROW_1:
                ret = lcd_4bit_send_command(lcd_obj,(0x80 + column));
            break;
            case ROW_2:
                ret = lcd_4bit_send_command(lcd_obj,(0xC0 + column));
            break;
            case ROW_3:
                ret = lcd_4bit_send_command(lcd_obj,(0x94 + column));
            break;
            case ROW_4:
                ret = lcd_4bit_send_command(lcd_obj,(0xD4 + column));
            break;
            default: ;
        }
        
        
    }
    return ret;
}