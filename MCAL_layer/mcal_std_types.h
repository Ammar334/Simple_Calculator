/* 
 * File:   mcal_std_types.h
 * Author: Ammar.Yasser
 *
 * Created on 21 ?????, 2023, 03:31 ?
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/******Includes**********/
#include "compiler.h"
#include "std_libraries.h"

/*********Data Types Declaration***********/
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef signed int sint32;
typedef signed short sint16;
typedef signed char sint8;

typedef uint8 Std_ReturnType; 
/*********Macro Declaration***********/
#define STD_HIGH         0x01
#define STD_low          0x00

#define STD_ON           0x01
#define STD_OFF          0x00

#define STD_ACTIVE       0x01
#define STD_IDLE         0x00

#define E_OK             (Std_ReturnType)0x01
#define E_NOT_OK         (Std_ReturnType)0x00

/*********Macro Function Declaration***********/

/*********Function Declaration***********/

#endif	/* MCAL_STD_TYPES_H */

