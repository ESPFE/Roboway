/*!
	\file		usart.h
	\brief		Header file for USART (RS232)
	\author		Andre Suennemann ( a.suennemann@edv-peuker.de | www.edv-peuker.de )
	\date		12.08.2013
	\version	0.0.1
*/

#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED


#include <avr/io.h>
#include <avr/interrupt.h>
#include "../avrConstants.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#define USART_BAUD_CALC(x) ( ( F_CPU / ( 16UL * ( x ) ) ) - 1 )
#define USART_DOUBLE_BAUD_CALC(x) ( ( F_CPU / ( 8UL * ( x ) ) ) - 1 )


#define LOW_BYTE(x) ( (uint8_t)( ( x ) & 0xFF ) )
#define HIGH_BYTE(x) ( (uint8_t)( ( ( x ) >> 8 ) & 0xFF ) )


void setUsartBaudRate( uint32_t baudRate );

void setupUsart0( uint32_t baudRate );

void usart0Transmit( uint8_t data );

void usart0PrintStr( char str[] );

#endif // USART_H_INCLUDED
