/*
 */

#define F_CPU 16000000UL
#define USART_BAUD_RATE 9600UL

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"
#include "srf.h"
#include "usart.h"



#define SRF_0   SRF_MODIFY_ADDRESS( SRF_ADDR_00 )
#define SRF_1   SRF_MODIFY_ADDRESS( SRF_ADDR_01 )


#define SRF_MIN_DISTANCE 50
#define SRF_MAX_DISTANCE 100


void setup( void );
void loop( void );
void end( void );

int main(void)
{
	setup();
	loop();
	end();
    while(true);
    return 0;
}


void setup( void )
{
    // Setup TWI
    twiSetup( TWI_MASTER, TWI_CLK_NORMAL_MODE, FALSE );
	setupUsart0( USART_BAUD_RATE );
	usart0PrintStr( "Und ab gehts!!!\n" );
    //sei();
}

void loop( void )
{
    uint16_t srf0Distance = 0;
	
	SRFStartMeasure( SRF_0, SRF_COM_MEASURE_CM );
	//SRFStartMeasure( SRF_1, SRF_COM_MEASURE_CM );
	
	
    while( 1 )
    {
		_delay_ms( 1000 );
		srf0Distance = SRFReadDistance( SRF_0 );
		if( srf0Distance < SRF_MIN_DISTANCE )
		{
			usart0PrintStr( "Minimal zulaessigen Abstand unterschritten!!!\n" );
		}
		else if( srf0Distance == SRF_UNAVAILABLE_16 )
		{
			usart0PrintStr( "Fehler bei der Abstandsmessung!!!\n" );
		}
		else if( srf0Distance > SRF_MAX_DISTANCE )
		{
			usart0PrintStr( "Maximal zulaessigen Abstand ueberschritten!!!\n" );
		}
		else
		{
			usart0PrintStr( "Abstand OK!!!\n" );
		}
		_delay_ms( 1000 );
		SRFStartMeasure( SRF_0, SRF_COM_MEASURE_CM );
		
    }
}

void end( void )
{
    twiStop();
}
