/* 
 * File:   hal_gpio.h
 * Author: Ammar.Yasser
 *
 * Created on 21 ?????, 2023, 03:28 ?
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/******Includes**********/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
/*********Macro Declaration***********/
#define _XTAL_FREQ        4000000UL
#define BIT_MASK   (uint8)1
#define PORT_MAX_NUMPER   5
#define PIN_MAX_NUMPER    8
#define TOGGLR_MASK       0xFF

/*********Macro Function Declaration***********/
#define HWREG8(_x) (*((volatile uint8*)(_x)))
#define SET_BIT(REG,BIT_POS)    (REG |= (BIT_MASK << BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)  (REG &= ~(BIT_MASK << BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS) (REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(REG,BIT_POS)   ((REG >> BIT_POS) & BIT_MASK)

/*********Data Types Declaration***********/
typedef enum
{
    GPIO_PIN0 =0,
    GPIO_PIN1 ,
    GPIO_PIN2, 
    GPIO_PIN3, 
    GPIO_PIN4, 
    GPIO_PIN5 ,
    GPIO_PIN6, 
    GPIO_PIN7 

}pin_index;

typedef enum
{
    GPIO_PORT_A =0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E

}port_index;

typedef enum
{
    GPIO_LOW=0,
    GPIO_HIGH
}logic_t;

typedef enum
{
    GPIO_OUTPUT=0,
    GPIO_INPUT
}direction;

typedef struct
{
    uint8 port :3 ;     /*@ref port_index*/
    uint8 pin :3 ;      /*@ref pin_index*/
    uint8 direction :1 ;/*@ref direction*/
    uint8 logic :1 ;    /*@ref logic_t*/
}pin_config;
/*********Function Declaration***********/
Std_ReturnType gpio_pin_direction_initialize(const pin_config *pin);
Std_ReturnType gpio_pin_get_direction(const pin_config *pin,direction* dir_status);
Std_ReturnType gpio_pin_read_logic(const pin_config *pin,logic_t *log);
Std_ReturnType gpio_pin_write_logic(const pin_config *pin,logic_t log);
Std_ReturnType gpio_pin_toggle_logic(const pin_config *pin);
Std_ReturnType gpio_pin_initialize(const pin_config *pin);


Std_ReturnType gpio_port_direction_initialize(port_index port,uint8 dir);
Std_ReturnType gpio_port_get_direction(port_index port,uint8 *dir_status);
Std_ReturnType gpio_port_read_logic(port_index port,uint8 *log);
Std_ReturnType gpio_port_write_logic(port_index port,uint8 log);
Std_ReturnType gpio_port_toggle_logic(port_index port);





#endif	/* HAL_GPIO_H */

