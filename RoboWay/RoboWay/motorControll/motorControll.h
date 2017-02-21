/*!
    \file       motorControll.h
    \brief      Header file for motor control of RoboWay

                This implementation of a motor control with PWM is very efficient, because it uses the output compare match interrupt to generate the PWM output.
				Only when you configure the motor control it needs cpu time.
				
    \version    1.2.5
    \author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
    \date       27.01.2014
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#ifndef MOTORCONTROLL_H_INCLUDED
#define MOTORCONTROLL_H_INCLUDED

#include <avr/io.h>

/*!
    \defgroup   MC_PINS   Pins used for controlling left and right wheel
    @{
	\def		MC_PORT
	\brief		AVR PORT used for motor control pins

	\def		MC_DDR
	\brief		AVR DDR used for motor control pins

    \def        MC_LEFT
    \brief      Pin for speed left wheel

	\def		MC_LEFT_FW
	\brief		Left wheel drives in forward direction if this pin is set to high

	\def		MC_LEFT_BW
	\brief		Left wheel drives in backward direction if this pin is set to high

    \def        MC_RIGHT
    \brief      Pin for speed right wheel

	\def		MC_RIGHT_FW
	\brief		right wheel drives in forward direction if this pin is set to high

	\def		MC_RIGHT_BW
	\brief		Right wheel drives in forward direction if this pin is set to high
*/
#define MC_PORT			PORTD
#define MC_DDR			DDRD
#define MC_LEFT         PD5
#define MC_LEFT_FW		PD2
#define MC_LEFT_BW		PD3
#define MC_RIGHT        PD6
#define MC_RIGHT_FW		PD4
#define MC_RIGHT_BW		PD7
/*! @} */

/*!
    \defgroup   MC_OCR    Registers for output compare match ( 0 -> 0% PWM  |  255 -> 100% PWM )
    @{
    \def        MC_LEFT_OCR
    \brief      Output compare register for left wheel

    \def        MC_RIGHT_OCR
    \brief      Output compare register for right wheel
*/
#define MC_LEFT_OCR     OCR0B
#define MC_RIGHT_OCR    OCR0A
/*! @} */


/*!
    \fn         void mCInit( void )
    \brief      Initialize motor control
*/
void mCInit( void );

/*!
    \fn         void mCSetSpeedLeft( uint8_t val )
    \brief      Set speed of the left wheel
    \param      val
    \brief      0 => 0% PWM => 0% Voltage\n
                255 => 100% PWM => 100% Voltage
*/
void mCSetSpeedLeft( uint8_t val );

/*!
    \fn         void mCSetSpeedRight( uint8_t val )
    \brief      Set speed of the right wheel
    \param      val
    \brief      0 => 0% PWM => 0% Voltage\n
                255 => 100% PWM => 100% Voltage
*/
void mCSetSpeedRight( uint8_t val );

/*!
	\fn			void mCRightFW( void )
	\brief		Set direction of right wheel to forward
*/
void mCRightFW( void );

/*!
	\fn			void mCRightBW( void )
	\brief		Set direction of right wheel to backward
*/
void mCRightBW( void );

/*!
	\fn			void mCLeftFW( void )
	\brief		Set direction of left wheel to forward
*/
void mCLeftFW( void );

/*!
	\fn			void mCLeftBW( void )
	\brief		Set direction of right wheel to backward
*/
void mCLeftBW( void );


#endif // MOTORCONTROLL_H_INCLUDED
