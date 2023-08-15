/* 
 * File:   applications.h
 * Author: Ammar.Yasser
 *
 * Created on 21 ?????, 2023, 06:18 ?
 */

#ifndef APPLICATIONS_H
#define	APPLICATIONS_H


/******Includes**********/
#include "ECU_layer/ecu_initialize.h"
/*********Macro Declaration***********/
extern lcd_4bit_t lcd_1;
extern keypad_t kp1;
/*********Macro Function Declaration***********/
#define DEBOUNE_TIME  200
/*********Data Types Declaration***********/

        
/*********Function Declaration***********/
void application_initialize (void);
void ecu_initialize (void);

#endif	/* APPLICATIONS_H */

