/* 
 * File:   application.c
 * Author: Ammar.Yasser
 *
 * Created on 21 ?????, 2023, 06:12 ?
 */

#include "applications.h"

Std_ReturnType ret = E_NOT_OK;


uint8 keypad_value=0;
uint8 a[20];
sint32 res=0;
float32 result=0;
uint8 num1[20]={0};
uint8 num2[20]={0};
uint8 l=0;
sint32 num1_counter=0;
sint32 num2_counter=0;
uint8 operatoin;
int main(){
    application_initialize();
    while(1)
    {
        ret = keypad_get_value(&kp1,&keypad_value);
        __delay_ms(DEBOUNE_TIME);
        if(keypad_value == '=')
        {
            ret = lcd_4bit_send_char_pos(&lcd_1,3,1,keypad_value);
            num1_counter = atoi(num1);
            num2_counter = atoi(num2);
            if(operatoin == '+' )
            {
                res = num1_counter + num2_counter;
            }else if(operatoin == '-' )
            {
                res = num1_counter - num2_counter;
               
            }else if(operatoin == '*' )               
            {
                res = num1_counter * num2_counter;
                
            
            }else if(operatoin == '/' )
            {
                result = (float)num1_counter / (float)num2_counter;
                
            }
            if( operatoin == '/')
            {
                sprintf(a, "%g", result);
                ret = lcd_4bit_send_string_pos(&lcd_1, 3,3, a);
            }
            else
            {
                ret = convert_int_to_string(res,a);
                ret = lcd_4bit_send_string_pos(&lcd_1, 3,3, a);
            }
            num1_counter=0;
            num2_counter=0;
            operatoin=0;
            l=0;  
            memset(num1,'\0',10);
            memset(num2,'\0',10);
            keypad_value=0;
        } 
        else if(keypad_value=='#')
         {
            ret = lcd_4bit_send_command(&lcd_1,LCD_CLEAR_DISPLAY);
            keypad_value=0;
            num1_counter=0;
            num2_counter=0;
            l=0;
            operatoin=0;
            memset(num1,'\0',10);
            memset(num2,'\0',10);
         }
         else if(keypad_value!=0)
        {
            ret = lcd_4bit_send_char(&lcd_1,keypad_value);
            if((l==0)&&(keypad_value!='*')&&((keypad_value!='-')||(num1_counter==0))&&(keypad_value!='+')&&(keypad_value!='/'))
            {
                num1[num1_counter]=keypad_value;
                num1_counter++;;
            }
            else if((l==1)&&(keypad_value!='*')&&((keypad_value!='-')||(num2_counter==0))&&(keypad_value!='+')&&(keypad_value!='/'))
            {
               num2[num2_counter] = keypad_value;
                num2_counter++;
            }
            else
            {
                if(operatoin == 0)
                {
                    operatoin = keypad_value;
                    if(l==1)
                    {
                        l=0;
                    }
                    else
                    {
                        l=1;
                    }
                }
                else
                {
                    ret = lcd_4bit_send_string_pos(&lcd_1,1,1,"To Much Operations");
                }
                
            }
            keypad_value=0;
            if((num2_counter==10)||(num1_counter==10))
            {
                ret = lcd_4bit_send_command(&lcd_1,LCD_CLEAR_DISPLAY);
                ret = lcd_4bit_send_string_pos(&lcd_1,1,1,"Out Of Space");
            }

                
        }
         else
         {}
    }

    return (EXIT_SUCCESS);
}

void application_initialize (void)
{
    ecu_initialize();
}