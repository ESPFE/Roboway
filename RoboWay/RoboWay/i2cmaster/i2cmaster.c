/*!
    \file       i2cmaster.c
    \brief      Implementation of the I2C (TWI) bus\n
                Basic source code provided by Peter Fleury\n
                Adapted and documented by Andre S&uuml;nnemann
    \author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
    \version    0.1.0
    \date       29.01.2014
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#include "i2cmaster.h"


void i2cInit( unsigned long sclMode )
{
    // set clockrate
    TWBR = ( ( F_CPU / ( sclMode ) ) - 16 ) / 2;
	// set statusregister to 0x00;
	TWSR = 0x00;
}


uint8_t i2cStart( uint8_t addr )
{
    uint8_t twst;

	// send START condition
	TWCR = ( 1<<TWINT ) | ( 1<<TWSTA ) | ( 1<<TWEN );
	
	// wait until transmission completed
	while( !( TWCR & ( 1 << TWINT ) ) );
	
	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START) )
	{
	    i2cStop();
        return I2C_FAIL;
	}

	// send device address
	TWDR = addr;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if( ( twst != TW_MT_SLA_ACK ) && ( twst != TW_MR_SLA_ACK ) )
	{
	    i2cStop();
	    return I2C_FAIL;
	}

	return I2C_OK;
}


void i2cStartWait( uint8_t addr )
{
    uint8_t twst;

    while ( true )
    {
	    // send START condition
	    TWCR = ( 1 << TWINT ) | ( 1 << TWSTA ) | ( 1 << TWEN );

    	// wait until transmission completed
    	while( !( TWCR & ( 1<<TWINT ) ) );

    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if( ( twst != TW_START ) && ( twst != TW_REP_START ) )
    	{
    	    continue;
    	}

    	// send device address
    	TWDR = addr;
    	TWCR = ( 1<<TWINT ) | ( 1<<TWEN );

    	// wail until transmission completed
    	while( ! ( TWCR & ( 1<<TWINT ) ) );

    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if( (twst == TW_MT_SLA_NACK ) || ( twst == TW_MR_DATA_NACK ) )
    	{
    	    /* device busy, send stop condition to terminate write operation */
	        TWCR = ( 1<<TWINT ) | ( 1<<TWEN ) | ( 1<<TWSTO );

	        // wait until stop condition is executed and bus released
	        while(TWCR & (1<<TWSTO));

    	    continue;
    	}
    	break;
     }
}


void i2cStop(void)
{
    /* send stop condition */
	TWCR = ( 1<<TWINT ) | ( 1<<TWEN ) | ( 1<<TWSTO );

	// wait until stop condition is executed and bus released
	while( TWCR & ( 1 << TWSTO ) );
}


uint8_t i2cWrite( uint8_t data )
{
    uint8_t twst;

	// send data to the previously addressed device
	TWDR = data;
	TWCR = ( 1 << TWINT ) | ( 1<<TWEN );

	// wait until transmission completed
	while( ! ( TWCR & ( 1<<TWINT ) ) );

	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK )
	{
	    i2cStop();
	    return I2C_FAIL;
	}
	return I2C_OK;

}


uint8_t i2cReadAck( void )
{
	// Request one byte from slave and request more
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN ) | ( 1 << TWEA );
	// Wait for received data and reset interrupt bit
	while( ! ( TWCR & ( 1 << TWINT ) ) );

    return TWDR;
}


unsigned char i2cReadNak(void)
{
	// Request one byte from slave and send a stop condition
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
	// Wait for received data and reset interrupt bit
	while( ! ( TWCR & ( 1 << TWINT ) ) );

    return TWDR;
}
