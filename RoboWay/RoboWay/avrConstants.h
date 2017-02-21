/*!
	\file		avrConstants.h
	\brief		Global constants and settings for AtMega 8 bit micro controllers
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		11.02.2014
	\version	2.1.5
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#ifndef AVRCONSTANTS_H_INCLUDED
#define AVRCONSTANTS_H_INCLUDED


/*!
	\defgroup	ATMEGA_SETTINGS			Settings for AtMega 8 bit micro controllers
	@{
	\def		F_CPU
	\brief		Clockrate of the CPU
*/
#define F_CPU 16000000UL
/*!	@} */


/*!
	\defgroup	ATMEGA_CONSTANTS		Constants for AtMega 8 bit micro controllers
	@{
	\def		false
	\brief		Boolean false
	
	\def		FALSE
	\see		false
	
	\def		true
	\brief		Boolean true
	
	\def		TRUE
	\see		true
	
	\def		high
	\brief		Signal high (a.e. for an IO-Pin)
	
	\def		HIGH
	\see		high
	
	\def		low
	\brief		Signal low (a.e. for an IO-Pin)
	
	\def		LOW
	\see		low
	
	\def		bool
	\brief		Data type for boolean variables
	
	\def		BOOL
	\see		bool
*/
#define false       0
#define FALSE       false

#define true        1
#define TRUE        true

#define bool		uint8_t
#define BOOL		bool

#define high        1
#define HIGH        high

#define low         0
#define LOW         low
/* @} */


/*!
	\defgroup		ATMEGE_MACROS	Useful macros for AtMega 8 bit micro controllers
	@{
	\def			RAD_TO_DEG(x)
	\brief			Converts an angle from rad to deg
	
	\def			LOW_BYTE(x)
	\brief			Returns low byte as uint8_t \n
					x should be 2 bytes
					
	\def			HIGH_BYTE(x)
	\brief			Returns high byte as uint8_t\n
					x should be 2 bytes
	
*/
#define RAD_TO_DEG(x)		( ( x ) * 57.295779513082320876798154814105 )
#define LOW_BYTE(x)			( (uint8_t)( ( x ) & 0xFF ) )
#define HIGH_BYTE(x)		( (uint8_t)( ( ( x ) >> 8 ) & 0xFF ) )
/*! @} */


/*!
	\fn			double constrainD( double val, double min, double max )
	\brief		Restricts a number to a certain interval
	\param		val
	\brief		Limiting number
	\param		min
	\brief		lower limit
	\param		max
	\brief		higher limit
	\return		double
	\retval		val
	\brief		if min < val < max
	\retval		min
	\brief		if val < min
	\retval		max
	\brief		if max < val
*/
double constrainD( double val, double min, double max );


#endif // AVRCONSTANTS_H_INCLUDED
