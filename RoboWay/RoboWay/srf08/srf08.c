/*!
	\file		srf08.c
	\brief		This is the main source code file for RoboWay - all crazy stuff is placed here
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		3.02.2014
	\version	1.8.4
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#include "srf08.h"


void srf08Start( uint8_t addr, uint8_t command )
{
	if( ! i2cStart( SRF08_ADDR_WRITE( addr ) ) )
	{
		return;
	}
	i2cWrite( SRF08_REG_COMMAND );
	i2cWrite(command );
	i2cStop();
}


uint8_t srf08Status( uint8_t addr )
{
	uint8_t status = SRF08_UNAVAIL;
	if( ! i2cStart( SRF08_ADDR_WRITE( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_COMMAND );
	i2cStop();
	if( ! i2cStart( SRF08_ADDR_READ( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	status = i2cReadNak();
	i2cStop();
	return status;
}


uint16_t srf08GetDistance( uint8_t addr )
{
	uint8_t distanceH = 0;
	uint8_t distanceL = 0;
	if( ! i2cStart( SRF08_ADDR_WRITE( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_ECHO_H );
	i2cStop();
	if( ! i2cStart( SRF08_ADDR_READ( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	distanceH = i2cReadAck();
	distanceL = i2cReadNak();
	i2cStop();
	return ( ( distanceH << 8 ) | distanceL );
}


uint8_t srf08GetLight( uint8_t addr )
{
	uint8_t light = SRF08_UNAVAIL;
	if( ! i2cStart( SRF08_ADDR_WRITE( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_LIGHT );
	i2cStop();
	if( ! i2cStart( SRF08_ADDR_READ( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	light = i2cReadNak();
	i2cStop();
	return light;
}


uint8_t srf08SetReg( uint8_t addr, uint8_t reg, uint8_t val )
{
	if( ! i2cStart( SRF08_ADDR_WRITE( addr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( reg );
	i2cWrite( val );
	i2cStop();
	return SRF08_AVAIL;
}



uint8_t srf08SetAddr( uint8_t oldAddr, uint8_t newAddr )
{
	// Send first sequence
	if( ! i2cStart( SRF08_ADDR_WRITE( oldAddr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_COMMAND );
	i2cWrite( SRF08_COM_ADDR0 );
	i2cStop();
	_delay_ms( 80 );
	// Send second sequence
	if( ! i2cStart( SRF08_ADDR_WRITE( oldAddr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_COMMAND );
	i2cWrite( SRF08_COM_ADDR1 );
	i2cStop();
	_delay_ms( 80 );
	// Send third sequence
	if( ! i2cStart( SRF08_ADDR_WRITE( oldAddr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_COMMAND );
	i2cWrite( SRF08_COM_ADDR2 );
	i2cStop();
	_delay_ms( 80 );
	// Send new address
	if( ! i2cStart( SRF08_ADDR_WRITE( oldAddr ) ) )
	{
		return SRF08_UNAVAIL;
	}
	i2cWrite( SRF08_REG_COMMAND );
	i2cWrite( newAddr );
	i2cStop();
	return SRF08_AVAIL;
}
