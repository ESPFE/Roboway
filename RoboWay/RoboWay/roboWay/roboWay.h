/*!
	\file		roboWay.h
	\brief		This is the main header file for RoboWay
				
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		3.02.2014
	\version	2.6.5
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#ifndef ROBOWAY_H_
#define ROBOWAY_H_


// include all necessary libraries
#include <avr/interrupt.h>
#include "../adxl354/adxl354.h"
#include "../l3g4200d/l3g4200d.h"
#include "../motorControll/motorControll.h"
#include "../avrConstants.h"
//#include "../usart/usart.h"
#include "../srf08/srf08.h"
#include "../pid/pid.h"
#include "../complementaryFilter/complementaryFilter.h"
#include <math.h>
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
	\def		LED_FORWARD
	\brief		LED for forward direction
	
	\def		LED_BACKWARD
	\brief		LED for backward direction
*/
#define LED_FORWARD			PB5
#define LED_BACKWARD		PB4


/*!
	\def		BT_START_STOP
	\brief		Button for Start / Stop
*/
//#define BT_START_STOP	PB3


/*!
	\def		PID_INTERVAL
	\brief		Sampling rate for PID\n
				(int)( (interval in sec * F_FPU) / 255 )
				
				Measured minimum interval is 305 -> PID_INTERVAL = 310
	
	\def		PID_INTERVAL_SEC
	\brief		Seconds between two PID stabilissation cicles\n
				( PID_INTERVAL * 255 ) / F_CPU
*/
//#define PID_INTERVAL		305
//#define PID_INTERVAL_SEC	0.0048609375
#define PID_INTERVAL		310
#define PID_INTERVAL_SEC	0.004940625


/*!
	\def		BALANCE_REF
	\brief		Reference value for roll (balancing)
*/
//#define BALANCE_REF				91.4835
//#define BALANCE_REF				92.0		// 94.58
#define BALANCE_REF					92.75


/*!
	\defgroup	ROLL_LIMITS		Maximum and minimum roll
	@{
	
	\def		ROLL_MIN_LIMIT
	\brief		Minimum value for roll
	
				If the measured roll is under this value, RoboWay stops balancing
				
	\see		ROLL_MAX_LIMIT
	\see		void roboWayLoop( void )
	
	\def		ROLL_MAX_LIMIT
	\brief		Maximum value for roll
	
				If the measured roll is over this value, RoboWay stops balancing
				
	\see		ROLL_MIN_LIMIT
	\see		void roboWayLoop( void )
*/
#define ROLL_MIN_LIMIT	55.0
#define ROLL_MAX_LIMIT	135.0
/*! @} */



/*!
	\defgroup	PID_CONSERVATIVE	Gain and limits for conservative pid settings (balancing)
	@{
	\def		K_B_C
	\brief		Over all gain
	
	\def		K_P_B_C
	\brief		Gain proportional part
	
	\def		K_I_B_C
	\brief		Gain integral part
	
	\def		K_D_B_C
	\brief		Gain differential part
	
	\def		MIN_OUT_B_C
	\brief		Minimal value for pid output
	
	\def		MAX_OUT_B_C
	\brief		Maximum value for pid output
*/
#define K_B_C		1.0
// Dauerschwingung bei 2.8
#define K_P_B_C		1.86
#define K_I_B_C		0.030
#define K_D_B_C		0.006
#define MIN_OUT_B_C	-255.0
#define MAX_OUT_B_C	255.0
/*! @} */


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
