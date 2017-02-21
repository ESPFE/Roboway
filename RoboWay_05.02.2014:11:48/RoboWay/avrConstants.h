/*!
	\file		avrConstants.h
	\brief		Global constants and settings for AtMega 8 bit micro controllers
	\author		Andre Suennemann ( a.suennemann@edv-peuker.de | www.edv-peuker.de )
	\date		11.02.2014
	\version	0.0.1
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
	\defgroup	ATMEGA_CONSTANTS		Settings for AtMega 8 bit micro controllers
	@{
	\def		false
	\brief		Boolean false
	\def		FALSE
	\brief		Boolean false
	\def		true
	\brief		Boolean true
	\def		TRUE
	\brief		Boolean true
	\def		high
	\brief		Signal high (a.e. for an IO-Pin)
	\def		HIGH
	\brief		Signal high (a.e. for an IO-Pin)
	\def		low
	\brief		Signal low (a.e. for an IO-Pin)
	\def		LOW
	\brief		Signal low (a.e. for an IO-Pin)
*/
#define false       0
#define FALSE       false

#define true        1
#define TRUE        true

#define high        1
#define HIGH        high

#define low         0
#define LOW         low
/* @} */


#define INT16_T_MAX_VAL	0x7FFF
#define UINT8_T_MAX_VAL	0xFF

#endif // AVRCONSTANTS_H_INCLUDED
