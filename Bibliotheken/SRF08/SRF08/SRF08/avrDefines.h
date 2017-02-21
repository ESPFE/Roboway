/*!
    \file   avrDefines.h

    \brief  Here are many definitions needed by varius modules written by André Sünnemann

            Version: 1.0    14.11.2013\n
            Author:  André Sünnemann    a.suennemann@edv-peuker.de      EDV-Systeme Peuker KG

*/


#ifndef AVRDEFINES_H_INCLUDED
#define AVRDEFINES_H_INCLUDED



#include <avr/io.h>

/*!
    \def byte
    \def BYTE
*/
#define byte uint8_t
#define BYTE byte

/*!
    \def bool
    \def BOOL
*/
#define bool uint8_t
#define BOOL bool

/*!
    \def boolean
    \def BOOLEAN
*/
#define boolean bool
#define BOOLEAN boolean

/*!
    \def true
    \def TRUE
    \def false
    \def FALSE
*/
#define true 1
#define TRUE true
#define false 0
#define FALSE false

/*!
    \def HIGH
    \def LOW
*/
#define HIGH 1
#define LOW 0


char iToC( int8_t i );

char* i8ToStr( int8_t i, char *buffer, uint8_t len );

char* i16ToStr( int16_t i, char *buffer, uint8_t len );

#endif // AVRDEFINES_H_INCLUDED
