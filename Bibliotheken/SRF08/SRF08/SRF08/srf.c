#include "srf.h"
#include "usart.h"


void SRFStartMeasure( uint8_t address, uint8_t command )
{
    uint8_t data[] = { SRF_REG_COMMAND, command };
	if( twiStart() != TWI_OK )
	{
			twiStop();
			return;
	}
    if( twiSelectWrite( address ) != TWI_OK )
	{
		twiStop();
		return;
	}
    if( twiWrite( data, 2 ) != TWI_OK )
	{
		twiStop();
		return;
	}
	twiStop();
}


uint8_t SRFAvailable( uint8_t address )
{
    uint8_t data = SRF_REG_COMMAND;
	if( twiStart() != TWI_OK )
	{
		twiStop();
		return SRF_UNAVAILABLE;
	}
    if( twiSelectWrite( address ) != TWI_OK )
	{
		twiStop();
		return SRF_UNAVAILABLE;
	}
    if( twiWrite( &data, 1 ) != TWI_OK )
	{
		twiStop();
		return SRF_UNAVAILABLE;
	}
	twiStop();
	
	if( twiStart() != TWI_OK )
	{
		twiStop();
		return SRF_UNAVAILABLE;
	}
    if( twiSelectRead( address ) != TWI_OK )
	{
		twiStop();
		return SRF_UNAVAILABLE;
	}
	twiRead( &data, 1 );
	twiStop();
    return data;
}


uint16_t SRFReadDistance( uint8_t address )
{
	uint8_t dataLow  = SRF_REG_ECHO_LOW;
	uint8_t dataHigh = SRF_REG_ECHO_HIGH;

	if( twiStart() != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 0\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiSelectWrite( address ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 1\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiWrite( &dataLow, 1 ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 2\n" );
		return SRF_UNAVAILABLE_16;
	}
	twiStop();
	
	if( twiStart() != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 3\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiSelectRead( address ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 4\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiRead( &dataLow, 1 ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 5\n" );
		return SRF_UNAVAILABLE_16;
	}
	twiStop();
	
	if( twiStart() != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 6\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiSelectWrite( address ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 7\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiWrite( &dataHigh, 1 ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 8\n" );
		return SRF_UNAVAILABLE_16;
	}
	twiStop();
	
	if( twiStart() != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 9\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiSelectRead( address ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 10\n" );
		return SRF_UNAVAILABLE_16;
	}
	if( twiRead( &dataHigh, 1 ) != TWI_OK )
	{
		twiStop();
		usart0PrintStr( "Fehler bei 11\n" );
		return SRF_UNAVAILABLE_16;
	}
	
	twiStop();
	usart0PrintStr( "Kein Fehler\n" );	
    return ( ( dataHigh << 8 ) | dataLow );
}


uint8_t SRFReadLight( uint8_t address )
{
    uint8_t data = SRF_REG_LIGHT;
	twiStart();
    twiSelectWrite( address );
    twiWrite( &data, 1 );
	twiStop();
	twiStart();
    twiSelectRead( address );
    twiRead( &data, 1 );
	twiStop();
    return data;
}


uint8_t SRFChangeAddress( uint8_t oldAddress, uint8_t newAddress )
{
    uint8_t data[4] = { SRF_COM_CH_ADDR_1, SRF_COM_CH_ADDR_2, SRF_COM_CH_ADDR_3, newAddress };
    uint8_t ret = SRF_REG_COMMAND;

    // Check if the SRF that we want to change the address is available on the I22
	twiStart();
    twiSelectWrite( oldAddress );
    twiWrite( &ret, 1 );
    twiSelectRead( oldAddress );
    twiRead( &ret, 1 );
    if( ret == SRF_UNAVAILABLE )
    {
        return SRF_UNAVAILABLE;
    }

    // Change address
    ret = SRF_REG_COMMAND;
    twiSelectWrite( oldAddress );
    twiWrite( data, 4 );
    twiSelectWrite( newAddress );
    twiWrite( &ret, 1 );
    twiSelectRead( newAddress );
    twiRead( &ret, 1 );
	twiStop();
    return ret;
}
