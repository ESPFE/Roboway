/*!
	\file		usart.h
	\brief		Header file for USART (RS232)
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		12.08.2013
	\version	0.0.1
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED


#include <avr/io.h>
#include <avr/interrupt.h>
#include "../avrConstants.h"


#ifndef F_CPU
#define F_CPU 16000000UL
#endif



/*!
	\defgroup		USART_MACROS		Useful macros for atmega8 usart (RS232)
	@{
	\def			USART_BAUD_CALC(x)
	\brief			Calculate value for the prescaler of the usart depending on F_CPU and baud rate
	
	\def			USART_DOUBLE_BAUD_CALC(x)
	\brief			Calculate value for the prescaler of the usart\n
					It is used if the baud rate is out of range
					
	\def			
*/
#define USART_BAUD_CALC(x) ( ( F_CPU / ( 16UL * ( x ) ) ) - 1 )
#define USART_DOUBLE_BAUD_CALC(x) ( ( F_CPU / ( 8UL * ( x ) ) ) - 1 )
/*! @} */


/*!
	\fn				void setUsartBaudRate( uint32_t baudRate )
	\brief			Setup baudrate for usart
	\param			baudRate
	\brief			Baudrate in bit/sec\n
					Possible values: 2400; 4800; 9600; 19200; 57600; 115200
	\return			void 
*/
void setUsartBaudRate( uint32_t baudRate );


/*!
	\fn				void setupUsart0( uint32_t baudRate )
	\brief			Initial setup of the usart serial interface
	\param			baudRate
	\brief			Baudrate in bit/sec\n
					Possible values: 2400; 4800; 9600; 19200; 57600; 115200
	\return			void
*/
void setupUsart0( uint32_t baudRate );


/*!
	\fn				void usart0Transmit( uint8_t data )
	\brief			Send one byte over the usart
	\param			data
	\brief			Byte to send
*/
void usart0Transmit( uint8_t data );

/*!
	\fn				void usart0PrintStr( char str[] )
	\brief			Send a zero terminated string over the usart
	\param			str
	\brief			String to send
	\warning		str must be a zero terminated string
	\return			void
*/
void usart0PrintStr( char str[] );

#endif // USART_H_INCLUDED
