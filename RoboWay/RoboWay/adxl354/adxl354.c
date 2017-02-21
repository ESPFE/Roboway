/*!
	\file		adxl354.c
	\brief		This is the source code file for simple use of the digital accelerometer ADXL354
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		31.01.2014
	\version	1.4.2
		
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#include "./adxl354.h"


uint8_t adxl354Init( uint8_t addr, uint8_t bwRate )
{
    if( ! i2cStart( I2C_WRITE( addr ) ) )
    {
        return false;
    }
	i2cWrite( ADXL354_REG_CTL_POWER );
	i2cWrite( 0b00101000 );
	if( ! i2cRepStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
    i2cWrite( ADXL354_REG_CTL_BW_RATE );
    i2cWrite( bwRate );
    i2cStop();
    return true;
}


uint8_t adxl354SetReg( uint8_t addr, uint8_t reg, uint8_t val )
{
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	if( ! i2cWrite( reg ) )
	{
		return false;
	}
	if( ! i2cWrite( val ) )
	{
		return false;
	}
	i2cStop();
	return true;
}


uint8_t adxl354GetAccelAll( uint8_t addr, int16_t *x, int16_t *y, int16_t *z )
{
    if( ! i2cStart( I2C_WRITE( addr ) ) )
    {
        return false;
    }
    if( ! i2cWrite( ADXL354_REG_DATAX_L ) )
    {
        return false;
    }
	i2cRepStart( I2C_READ( addr ) );
    *x = i2cReadAck();
    *x |= i2cReadAck() << 8;
    *y = i2cReadAck();
    *y |= i2cReadAck() << 8;
    *z = i2cReadAck();
    *z |= i2cReadNak() << 8;
    i2cStop();
    return true;
}

uint8_t adxl354GetAccel( uint8_t addr, int8_t axis, int16_t *val )
{
	if( ! i2cStart( I2C_WRITE( addr ) ) )
	{
		return false;
	}
	if( ! i2cWrite( axis ) )
	{
		return false;
	}
	i2cRepStart( I2C_READ( addr ) );
	*val = i2cReadAck();
	*val |= i2cReadNak() << 8;
	i2cStop();
	return true;
}