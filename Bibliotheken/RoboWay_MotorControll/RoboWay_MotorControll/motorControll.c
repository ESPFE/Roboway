/*!
    \file       motorControll.c
    \brief      Sourcecode for motorcontroll of the RoboWay

    \version    0.0.1
    \author     Andr� S�nnemann (a.suennemann@edv-peuker.de | www.edv-peuker.de )
    \date       27.01.2014

*/

#include "motorControll.h"


void mCInit( void )
{
    // Set motor controll pins as output
    MC_DDR |= ( 1 << MC_LEFT ) | ( 1 << MC_LEFT_FW ) | ( 1 << MC_LEFT_BW ) |
			( 1 << MC_RIGHT ) | ( 1 << MC_RIGHT_FW ) | ( 1 << MC_RIGHT_BW );
    // Setup Timer 0
    // ( 1 << WGM00 )  | ( 1 << WGM01 )     =>  Fast PWM Mode
    // ( 1 << COM0A1 )                      =>  Clear OC0A on compare match (MC_RIGHT)
    // ( 1 << COM0B1 )                      =>  Clear OC0B on compare match (MC_LEFT)
    TCCR0A = ( 1 << WGM00 ) | ( 1 << WGM01 ) |
             ( 1 << COM0A1 ) | ( 1 << COM0B1 );
    // ( 1 << CS00 )                        =>  Use internal OSC, not prescaler
    TCCR0B = ( 1 << CS00 );
    // Reset Timer
    TCNT0 = 0x00;
    MC_LEFT_OCR = 0x00;
    MC_RIGHT_OCR = 0x00;
}


void mCSetSpeedLeft( uint8_t val )
{
    MC_LEFT_OCR = val;
	// Break
	if( val == 0 )
	{
		MC_PORT |= ( 1 << MC_LEFT_BW ) | ( 1 << MC_LEFT_FW );
	}
}


void mCSetSpeedRight( uint8_t val )
{
    MC_RIGHT_OCR = val;
	// Break
	if( val == 0 )
	{
		MC_PORT |= ( 1 << MC_RIGHT_BW ) | ( 1 << MC_RIGHT_FW );
	}
}


void mCRightFW( void )
{
	MC_PORT &= ~( 1 << MC_RIGHT_BW );
	MC_PORT |= ( 1 << MC_RIGHT_FW );
}

void mCRightBW( void )
{
	MC_PORT &= ~( 1 << MC_RIGHT_FW );
	MC_PORT |= ( 1 << MC_RIGHT_BW );
}

void mCLeftFW( void )
{
	MC_PORT &= ~( 1 << MC_LEFT_BW );
	MC_PORT |= ( 1 << MC_LEFT_FW );
}

void mCLeftBW( void )
{
	MC_PORT &= ~( 1 << MC_LEFT_FW );
	MC_PORT |= ( 1 << MC_LEFT_BW );
}