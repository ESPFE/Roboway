/*!
    \file       twi.c
    \brief      This is the sourcecode for the avr two wire interface (twi, I²C)

                Here are definitions and functions for simple use of AVR TWI
*/


/*******************************************/
/* definitions */
/*******************************************/

#include "twi.h"

#define F_CPU 16000000UL

/*! \addtogroup twiCLKModes */
/*! @{ */
/*!
    \def        TWI_CLK_NORMAL_MODE_VAL
    \brief      Constant clockrate in twi normal mode

                This Constant is used by void twiSetBitRate( bool clkMode )
                to calculate the clockrate for TWI

    \warning    DO NOT USE OR MODYFY THIS OTHERWISE
*/
/*!
    \def        TWI_CLK_FAST_MODE_VAL
    \brief      Constant clockrate in twi fast mode

                This Constant is used by void twiSetBitRate( bool clkMode )
                to calculate the clockrate for TWI

    \warning    DO NOT USE OR MODYFY THIS OTHERWISE
*/
#define TWI_CLK_NORMAL_MODE_VAL     100000UL
#define TWI_CLK_FAST_MODE_VAL       400000UL
/*! @} */

/*!
    \def        TWI_CALC_TWBR(x)
    \brief      Makro for calculating the value for TWBR

                TWBR is the Two Wire Bitrate Register
                The value in it is used to set the bit rate / clock for SCL
*/
// Calculate value for TWI Bitrate Register ( TWBR )
#define TWI_CALC_TWBR(x) ( ( ( F_CPU / (x) ) - 16 ) / 2 )


/*******************************************/
/* function prototypes */
/*******************************************/

void twiSetBitRate( bool clkMode );












/*******************************************/
/* functions in twi.c */
/*******************************************/

/*!
    \fn         void twiSetBitRate( bool clkMode )
    \brief      Set value for TWBR to set the TWI clock

                fast mode -> TWI clock is 400kHz\n
                normal mode -> TWI clock is 100kHz

    \param      clkMode
    \brief      TWI_CLK_NORMAL_MODE or TWI_CLK_FAST_MODE
*/
void twiSetBitRate( uint8_t clkMode )
{
    if( clkMode == TWI_CLK_NORMAL_MODE )
    {
        TWBR = TWI_CALC_TWBR( TWI_CLK_NORMAL_MODE_VAL );
    }
    else
    {
        TWBR = TWI_CALC_TWBR( TWI_CLK_FAST_MODE_VAL );
    }
    TWSR = 0x0;
}



/*******************************************/
/* functions in twi.h */
/*******************************************/
void twiSetup( bool mode, bool clkMode, uint8_t addr )
{
    if( mode == TWI_MASTER )
    {
        twiSetBitRate( clkMode );
    }
    else
    {
        TWAR = ( addr << 1 );
        TWCR = ( 1 << TWINT ) | ( 1 << TWEA ) | ( 1 << TWEN );
    }
}



uint8_t twiStart( void )
{
    // enable interrupts ( 1 << TWINT )
    // send start / repeated start condition ( 1 << TWSTA )
    // enable TWI ( 1 << TWEN )
    TWCR = ( 1 << TWINT ) | ( 1 << TWSTA ) | ( 1 << TWEN );

    // wait until we are the boss
    while( ! ( TWCR & ( 1 << TWINT ) ) );

    // errordetection
    // TWI_OK -> no error
    // TWI_ERROR -> error
    return ((( TWSR & 0xF8 ) == 0x08 ) || ( TWSR & 0xF8 ) == 0x10 );
}


void twiStop( void )
{
    TWCR = ( 1 << TWINT ) | ( 1 << TWEN ) | ( 1 << TWSTO );
}


uint8_t twiSelectRead( uint8_t addr )
{
    // Shift addr 1 bit to the left and set last bit to 1
    // then write addr to TWDR ( TWI Data Register )
    TWDR = ( addr << 1 ) | 0x01;

    // start sending
    TWCR = ( 1 << TWINT ) | ( 1 << TWEN );

    // Wait until everything is sent
    while( ! ( TWCR & ( 1 << TWINT ) ) );

    // errordetection
    // TWI_OK -> no error
    // TWI_ERROR -> error
    return ( ( TWSR & 0xF8 ) == 0x40 );
}


uint8_t twiSelectWrite( uint8_t addr )
{
    // Shift addr 1 bit to the left and set last bit to 0
    // then write addr to TWDR ( TWI Data Register )
    TWDR = ( addr << 1 );

    // start sending
    TWCR = ( 1 << TWINT ) | ( 1 << TWEN );

    // wati until everything is sent
    while( ! ( TWCR & ( 1 << TWINT) ) );

    // errordetection
    // TWI_OK -> no error
    // TWI_ERROR -> error
    return ( ( TWSR & 0xF8 ) == 0x18 );
}


uint8_t twiRead( uint8_t data[], uint8_t length )
{
    while( length )
    {
        --length;
        // Normal read
        if( length > 0 )
        {
            TWCR = ( 1 << TWINT ) | ( 1 << TWEN ) | ( 1 << TWEA );
        }
        // otherwise send NACK
        else
        {
            TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
        }

        // wait
        while( ! ( TWCR & ( 1 << TWINT ) ) );

        *data = TWDR;

        ++data;

        switch( TWSR & 0xF8 )
        {
            // ACK
            case 0x50:
                *data = TWDR;
                ++data;
                break;

            // NACK
            case 0x58:
                // data left -> error
                if( length > 0 )
                {
                    return TWI_ERROR;
                }
                // no data left -> NACK correct
                else
                {
                    *data = TWDR;
                    ++data;
                }
                break;

            default:
                return TWI_ERROR;
                break;
        }
    }
    // success
    return TWI_OK;
}


uint8_t twiWrite( uint8_t data[], uint8_t length )
{
    while( length > 0 )
    {
        TWDR = *data;
        // start sending
        TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
        // wati until everything is sent
        while( ! ( TWCR & ( 1 << TWINT ) ) );

        // sent but no ACK is received
        if( ( TWSR & 0xF8 ) != 0x28 )
        {
            return TWI_ERROR;
        }

        --length;
        ++data;
    }
    // everything is sent successfully
    return TWI_OK;
}
