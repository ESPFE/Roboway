/*!
	\file		roboWay.h
	\brief		This is the main header file for RoboWay
	\author		Andre Suennemann ( a.suennemann@edv-peuker.de | www.edv-peuker.de )
	\date		3.02.2014
	\version	0.0.1
*/

#ifndef ROBOWAY_H_
#define ROBOWAY_H_


// include all necessary libraries
#include <avr/interrupt.h>

#include "../adxl354/adxl354.h"
#include "../l3g4200d/l3g4200d.h"
#include "../motorControll/motorControll.h"
#include "../avrConstants.h"
#include "../usart/usart.h"
#include "../srf08/srf08.h"
#include "../pid/pid.h"
#include "../kalman/kalman.h"

#include <util/delay.h>

/*!
	\def		SRFF
	\brief		Address of the front srf
	\def		SRFB
	\brief		Address of the back srf
*/
#define SRFF		SRF08_ADDR_00
#define SRFB		SRF08_ADDR_01

/*!
	\def		ACC_ADDR
	\brief		Address of the Accelerometer
*/
#define ACC_ADDR		ADXL354_STD_DEVID

/*!
	\def		GYRO_ADDR
	\brief		Address of the gyroscope
*/
#define GYRO_ADDR		L3G4200D_DEVID_1


/*!
	\def		LED_FAILURE
	\brief		Output for Errors
	
	\def		LED_OK_MODE
	\brief		Output for Status
*/
#define LED_FAILURE		PB5
#define LED_OK_MODE		PB4


/*!
	\def		BT_START_STOP
	\brief		Button for Start / Stop
*/
#define BT_START_STOP	PB3

#define ACC_LIMIT		200


#define K_P_STAB	1.50
#define K_I_STAB	1.80
#define K_D_STAB	0.35

#define ACC_MAX		32768


/*!
    \fn         void roboWayInit( void )
    \brief      Initial setup of RoboWay - need to be called only once
*/
void roboWayInit( void );


/*!
    \fn         void roboWayLoop( void )
    \brief      Main function of RoboWay - need to be called only once
                There is a never ending while loop inside
*/
void roboWayLoop( void );



#endif
