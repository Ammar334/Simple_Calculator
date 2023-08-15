/* 
 * File:   application.c
 * Author: Ammar.Yasser
 *
 * Created on 21 ?????, 2023, 06:12 ?
 */
#include "hal_gpio.h"
/*Reference to data direction control register*/
volatile uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*Reference to Port statues register*/
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/*Reference to data latch register ( REAd and Write*/
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};

/**
 * @brif  initialize the direction of a specific pin  (@ref direction)
 * @param pin : pointer to the configuration          (@ref pin_config)
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config *pin)
{
    Std_ReturnType ret = E_OK;
    if((pin==NULL)||(pin->pin>=PIN_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(pin->direction)
        {
            case GPIO_OUTPUT :
                CLEAR_BIT(*tris_registers[pin->port],pin->pin);
                break;
            case GPIO_INPUT :
                SET_BIT(*tris_registers[pin->port],pin->pin);
                break;
            default :
            ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * @brif  Get the direction of specific pin   (@ref direction)
 * @param pin : pointer to the configuration  (@ref pin_config)
 * @param dir_status
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue
 */
Std_ReturnType gpio_pin_get_direction(const pin_config *pin,direction* dir_status)
{
    Std_ReturnType ret = E_OK;
    if((pin==NULL)||(pin->pin>=PIN_MAX_NUMPER)||(dir_status==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *dir_status = READ_BIT(*tris_registers[pin->port],pin->pin);
    }
    return ret;
    
}
/**
 * @brif  Get the logic on a specific pin     (@ref logic_t)
 * @param pin : pointer to the configuration  (@ref pin_config)
 * @param log
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_pin_read_logic(const pin_config *pin,logic_t *log)
{
    Std_ReturnType ret = E_OK;
    if((pin==NULL)||(pin->pin>=PIN_MAX_NUMPER)||(log==NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *log = READ_BIT(*port_registers[pin->port],pin->pin);
    }
     return ret;
}
/**
 * @brif  Write the logic on a specific pin   (@ref logic_t)
 * @param pin : pointer to the configuration  (@ref pin_config)
 * @param log
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_pin_write_logic(const pin_config *pin,logic_t log)
{
    Std_ReturnType ret = E_OK;
    if((pin==NULL)||(pin->pin>=PIN_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(log)
        {
            case GPIO_LOW :
                CLEAR_BIT(*lat_registers[pin->port],pin->pin);
                break;
            case GPIO_HIGH :
                SET_BIT(*lat_registers[pin->port],pin->pin);
                break;
            default :
            ret = E_NOT_OK;
        }
    }
     return ret;
}
/**
 * @brif  Toggle the logic on a specific pin  (@ref logic_t)
 * @param pin : pointer to the configuration  (@ref pin_config)
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config *pin)
{
    Std_ReturnType ret = E_OK;
    if((pin==NULL)||(pin->pin>=PIN_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[pin->port],pin->pin);
    }
    return ret;
}
/**
 * 
 * @param pin : pointer to the configuration   (@ref pin_config)
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_pin_initialize(const pin_config *pin)
{
    Std_ReturnType ret = E_OK;
    if((pin==NULL)||(pin->pin>=PIN_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(pin);
        ret = gpio_pin_write_logic(pin,pin->logic);
    }
    return ret;
}

/**
 * 
 * @param port
 * @param dir
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_port_direction_initialize(port_index port,uint8 dir)
{
    Std_ReturnType ret = E_OK;
    if((port>=PORT_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = dir;
    }
    
    return ret;
}
/**
 * 
 * @param port
 * @param dir_status
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue
 */
Std_ReturnType gpio_port_get_direction(port_index port,uint8 *dir_status)
{
    Std_ReturnType ret = E_OK;
    if((dir_status==NULL) ||(port>=PORT_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *dir_status = *tris_registers[port];
    }
    return ret;
}
/**
 * 
 * @param port
 * @param log
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_port_read_logic(port_index port,uint8 *log)
{
    Std_ReturnType ret = E_OK;
    if((log==NULL) ||(port>=PORT_MAX_NUMPER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *log = *lat_registers[port];
    }
    return ret;
}
/**
 * 
 * @param port
 * @param log
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_port_write_logic(port_index port,uint8 log)
{
    Std_ReturnType ret = E_OK;
    if(port>=PORT_MAX_NUMPER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = log;
    }
    return ret;
}
/**
 * 
 * @param port
 * @return statues of the function
 *         (E_OK) : function done successfully
 *         (E_NOT_OK) : the function has issue 
 */
Std_ReturnType gpio_port_toggle_logic(port_index port)
{
    Std_ReturnType ret = E_OK;
        if(port>=PORT_MAX_NUMPER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] ^= TOGGLR_MASK;
    }
    
    return ret;
}