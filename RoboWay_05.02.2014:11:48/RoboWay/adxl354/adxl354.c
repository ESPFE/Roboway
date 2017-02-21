/*!
	\file		adxl354.c
	\brief		This is the source code file of a little bibliothek for simple use of the digital accelerometer ADXL354
	\author		Andre Suennemann ( a.suennemann@edv-peuker.de | www.edv-peuker.de )
	\date		31.01.2014
	\version	0.0.1
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