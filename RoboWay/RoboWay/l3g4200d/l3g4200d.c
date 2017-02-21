/*!
	\file		l3g4200d.c
	\brief		This is the header file for the l3g4200d gyro bibliothek
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		11.02.2014
	\version	0.0.1
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#include "l3g4200d.h"


uint8_t l3g4200dInit( uint8_t addr, uint8_t bwRate )
{
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( L3G4200D_REG_CTRL_1 );
	// Set bit rate, data rate and enable the gyro
	i2cWrite( bwRate | 0b00001111 );
	if( ! i2cRepStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( L3G4200D_REG_CTRL_2 );
	i2cWrite( 0b00000000 );
	i2cStop();
	return true;
}


uint8_t l3g4200dGetReg( uint8_t addr, uint8_t reg )
{
	uint8_t val = 0;
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( reg );
	if( ! i2cRepStart( I2C_READ( addr ) ) )
	{
		return false;
	}
	val = i2cReadNak();
	i2cStop();
	return val;
}


uint8_t l3g4200dSetReg( uint8_t addr, uint8_t reg, uint8_t val )
{
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( reg );
	if( ! i2cRepStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( val );
	i2cStop();
	return true;
}


uint8_t l3g4200dGetAR( uint8_t addr, uint8_t axis, int16_t *val )
{
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( axis );
	if( ! i2cRepStart( I2C_READ( addr ) ) )
	{
		return false;
	}
	*val = i2cReadNak();
	if( ! i2cRepStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( axis + 0x01 );
	if( ! i2cRepStart( I2C_READ( addr ) ) )
	{
		return false;
	}
	*val |= i2cReadNak() << 8;
	i2cStop();
	return true;
}


uint8_t l3g4200dGetARAll( uint8_t addr, int16_t *x, int16_t *y, int16_t *z )
{
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	i2cWrite( L3G4200D_REG_DATAX_L );
	if( ! i2cRepStart( I2C_READ( addr ) ) )
	{
		return false;
	}
	*x = i2cReadAck();
	*x |= i2cReadAck() << 8;
	*y = i2cReadAck();
	*y |= i2cReadAck() << 8;
	*z = i2cReadAck();
	*z |= i2cReadNak() << 8;
	i2cStop();
	return true;
}