/*!
	\file		roboWay.c
	\brief		This is the main source code file for RoboWay - all crazy stuff is placed here
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		3.02.2014
	\version	2.6.5
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#include "roboWay.h"
//#include <stdlib.h>
//#include <stdio.h>

/*!
	\var		pidDataC
	\brief		Working data structure for pid motor control

	\var		compFilterDataC
	\brief		Working data structure for complementary filter motor control
*/
pidData pidDataC;
compFilterData compFilterDataC;

/*!
	\var		pidMCEn
	\brief		Global variable for timing of motor controll

				It is used in ISR(TIMER2_OVF_vect) and void roboWayLoop( void )

*/
volatile bool pidMCEn = true;


/*!
	\fn			ISR(TIMER2_OVF_vect)
	\brief		Interrupt service routine for sampling rate of the motor controller

	\var		TIMER2_OVF_vect
	\brief		Timer 2 overflow interrupt
*/
ISR(TIMER2_OVF_vect)
{
	static uint16_t i = 0;
	if( i < PID_INTERVAL )
	{
		i += 1;
	}
	else
	{
		pidMCEn = true;
		i = 0;
	}
}


void roboWayInit()
{
	// Wait while the hardware is starting
	_delay_ms( 50 );
	// initialize motor control
	mCInit();
	// initialize i2c
	i2cInit( I2C_SCL_HIGH );
	// initialize usart
	//setupUsart0( 9600 );

	// Set range of the SRF08 to nearly 50cm
//	srf08SetRange( SRFF, 500 );
//	srf08SetRange( SRFB, 500 );
	// initialize accelerometer
	adxl354Init( ACC_ADDR, ADXL354_REG_BW_RATE_400 );

	l3g4200dInit( GYRO_ADDR, L3G4200D_BW_RATE_400 );
	// Set GYRO to a full scale selection of 500 deg/s
	l3g4200dSetReg( GYRO_ADDR, L3G4200D_REG_CTRL_4, 0b00110000 );

	// initialize PID for Motor Control balancing
	//pidInit( K_B, K_P_B, K_I_B, K_D_B, MIN_OUT_B, MAX_OUT_B, &pidDataA );
	pidInit( K_B_C, K_P_B_C, K_I_B_C, K_D_B_C, MIN_OUT_B_C, MAX_OUT_B_C, &pidDataC );

	// initialize complementary filter
	compFilterInit( CF_STD_GYRO_GAIN, CF_STD_ACC_GAIN, PID_INTERVAL_SEC, &compFilterDataC );


	// Setup timer, enable timer/counter 0 overflow interrupt
	TCCR2B = ( 1 << CS20 );
	TIMSK2 = ( 1 << TOIE2 );
	TCNT2 = 0;

	// Setup LED Ports
	DDRB |= ( 1 << LED_FORWARD ) | ( 1 << LED_BACKWARD );
	// Setup pin for buttons
	//PORTB |= ( 1 << BT_START_STOP );

	// enable interrupts
	sei();
}



void roboWayLoop( void )
{
	int16_t accYData = 0;
	int16_t accZData = 0;
	double roll = 0.0;

	int16_t gyroXData = 0;
	double gyroXRate = 0.0;

	double rollFiltered = 0.0;
	volatile double balanceRef = BALANCE_REF;

	//double error = 0.0;

	int8_t mcSpeed = 0;
	//int8_t mcSpeedOld = 0;
	//uint8_t mcLeftSpeed = 0;
	//uint8_t mcRightSpeed = 0;

	// Set initial value for roll and accZAngle
	ADXL354_GET_ACCEL_Y( ACC_ADDR, &accYData );
	ADXL354_GET_ACCEL_Z( ACC_ADDR, &accZData );
	L3G4200D_GET_AR_X(GYRO_ADDR, &gyroXData );

	roll = atan2( accYData, accZData );
	roll = - RAD_TO_DEG( roll );
	rollFiltered = roll;

    while( true )
    {
		if( pidMCEn == true )
		{
			// Get acceleration of y and z axis
			ADXL354_GET_ACCEL_Y( ACC_ADDR, &accYData );
			ADXL354_GET_ACCEL_Z( ACC_ADDR, &accZData );

			// Get angular rate for x axis
			L3G4200D_GET_AR_X(GYRO_ADDR, &gyroXData );
			// Convert to degrees per second and change direction
			gyroXRate = - gyroXData / 14.286;

			// Calculate roll (rotation around the x axis)
			roll = atan2( accYData, accZData );
			// Convert to degrees and change direction
			roll = - RAD_TO_DEG( roll );

			rollFiltered = compFilterGetAngle( gyroXRate, roll, &compFilterDataC );

			// Position (rollFiltered) out of range -> stop motors
			if( rollFiltered < ROLL_MIN_LIMIT || rollFiltered > ROLL_MAX_LIMIT )
			{
				mcSpeed = 0;
				PORTB &= ( ~( 1 << LED_BACKWARD ) ) & ( ~( 1 << LED_FORWARD ) );
			}
			else
			{
				mcSpeed = updatePid( balanceRef, rollFiltered, &pidDataC );
			}

			if( mcSpeed < 0 )
			{
				mCLeftFW();
				mCRightFW();
				mcSpeed *= -1;
				PORTB |= 1 << LED_BACKWARD;
				PORTB &= ~( 1 << LED_FORWARD );
			}
			else if( mcSpeed > 0 )
			{
				mCLeftBW();
				mCRightBW();
				PORTB |= 1 << LED_FORWARD;
				PORTB &= ~( 1 << LED_BACKWARD );
			}

			mCSetSpeedRight( mcSpeed );
			mCSetSpeedLeft( mcSpeed );

			pidMCEn = false;
		}
    }
}