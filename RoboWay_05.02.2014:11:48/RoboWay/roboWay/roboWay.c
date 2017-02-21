/*!
	\file		roboway.c
	\brief		This is the main source code file for RoboWay - all crazy stuff is placed here
	\author		Andre Suennemann ( a.suennemann@edv-peuker.de | www.edv-peuker.de )
	\date		3.02.2014
	\version	0.0.1
*/

#include "roboWay.h"
#include <stdlib.h>
 

#define MAX 10

struct PID_DATA pidDataStab;
struct kalmanData kData;

volatile uint8_t pidMCEn = true;
uint16_t pidDataStabInterval = 6;


ISR(TIMER2_OVF_vect)
{
	static uint16_t i = 0;
	if( i < pidDataStabInterval )
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
//	setupUsart0( 9600 );

	// Set range of the SRF08 to nearly 50cm
//	srf08SetRange( SRFF, 500 );
//	srf08SetRange( SRFB, 500 );
	// initialize accelerometer
	adxl354Init( ACC_ADDR, ADXL354_REG_BW_RATE_400 );
	l3g4200dInit( GYRO_ADDR, L3G4200D_BW_RATE_400 );
	
	// initialize PID Stab for Motor Control
	pid_Init( K_P_STAB *SCALING_FACTOR, K_I_STAB *SCALING_FACTOR, K_D_STAB *SCALING_FACTOR, &pidDataStab );
	
	// initialize kalman filter
	setupKalman( &kData );
	
	// setup sampling rate for PID Motor Control
	//pidDataStabInterval = PID_SAMPLE_INTERVAL(0.0001);
	// Set up timer, enable timer/counter 0 overflow interrupt
	TCCR2B = ( 1 << CS20 );
	TIMSK2 = ( 1 << TOIE2 );
	TCNT2 = 0;
	
	_delay_ms( 100 );
	
	adxl354SetReg( ACC_ADDR, ADXL354_REG_OFSZ, 0);

	DDRB |= ( 1 << LED_FAILURE ) | ( 1 << LED_OK_MODE );
	PORTB |= ( 1 << BT_START_STOP );
	
	_delay_ms(100);
	
	sei();
}



void roboWayLoop( void )
{
	/*
	char text[20] = { '\0' };
	uint16_t distanceF = 0;
	uint16_t distanceB = 0;
	*/
	
	int16_t accData = 0;
	int16_t gyroData = 0;
	double gyroXRate = 0.0;
	double accAngle = 0.0;
	
	int16_t refAcc = 0;
	
	double mcSpeed;
	uint8_t mcLeftSpeed = 0;
	uint8_t mcRightSpeed = 0;
	
    while( true )
    {
		if( pidMCEn == true )
		{
			ADXL354_GET_ACCEL_Z( ACC_ADDR, &accData );
			L3G4200D_GET_AR_X(GYRO_ADDR, &gyroData );
			
			if( accData < 0 )
			{
				PORTB |= ( 1 << LED_FAILURE );
				PORTB &= ~( 1 << LED_OK_MODE );
				mCRightBW();
				mCLeftBW();
				accData *= -1;
			}
			else
			{
				PORTB &= ~( 1 << LED_FAILURE );
				PORTB |= ( 1 << LED_OK_MODE );
				mCRightFW();
				mCLeftFW();
			}
			
			if( accData > ACC_LIMIT )
			{
				mCSetSpeedLeft( 0 );
				mCSetSpeedRight( 0 );
				continue;
			}
			
			gyroXRate = (double)gyroData / 14.375;
			accAngle = ( (double)accData / 1023.00 ) * 180.00;
			
			accAngle = kalmanGetAngle( accAngle, gyroXRate, 0.0001, &kData );
			
			mcSpeed = pid_Controller( refAcc, accAngle, &pidDataStab );
			if( mcSpeed < 0 )
			{
				mcSpeed *= -1;
			}
			
			mcLeftSpeed = (double)UINT8_T_MAX_VAL * mcSpeed / INT16_T_MAX_VAL;
			mcRightSpeed = mcLeftSpeed;

			mCSetSpeedLeft( mcLeftSpeed );
			mCSetSpeedRight( mcRightSpeed );
			
			pidMCEn = false;
		}
    }
}