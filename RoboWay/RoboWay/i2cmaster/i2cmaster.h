/*!
    \file       i2cmaster.h
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

#ifndef I2CMASTER_H_INCLUDED
#define I2CMASTER_H_INCLUDED


#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif


// Constant F_CPU required
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdint.h>
#include <inttypes.h>
// Standart macros and constants for I2C
#include <compat/twi.h>
#include "../avrConstants.h"


/*!
    \defgroup       I2C_DIRECTION   Macros used to modify the address of the slave for read or write operations
    @{
    \def            I2C_READ(addr)
    \brief          Modify the address of the slave for read operations
    \param          addr
    \brief          Address of the I2C slave

    \def            I2C_WRITE(addr)
    \brief          Modify the address of the slave for write operations
    \param          addr
    \brief          Address of the I2C slave
*/
#define I2C_READ(addr)         ( ( (addr) << 1 ) | 0x01 )
#define I2C_WRITE(addr)        ( ( (addr) << 1 ) | 0x00 )
/*! @} */

/*!
    \defgroup   I2CMACROS           Useful macros for I2C
    @{
    \def        i2cRepStart(addr)
    \brief      Issues a repeated start condition, sends address and transfer direction
                This is just an alias of uint8_t i2cStart( uint8_t addr )
 */
#define i2cRepStart(addr)       ( i2cStart(addr) )
/*! @} */

/*!
    \defgroup   I2C_STATUS_CODES    Status codes of I2C functions
    @{
    \def        I2C_OK
    \brief      Status Code OK

    \def        I2C_FAIL
    \brief      Status Code Failure
*/
#define I2C_OK                  TRUE
#define I2C_FAIL                FALSE
/*! @} */

/*!
    \defgroup   I2C_SCL_MODES       Modes for I2C clockrate
    @{
    \def        I2C_SCL_NORMAL
    \brief      Normal Clockrate (100kHz)

    \def        I2C_SCL_HIGH
    \brief      High Clockrate (400kHz)
*/
#define I2C_SCL_NORMAL          10000UL
#define I2C_SCL_HIGH            40000UL
/*! @} */


/*!
    \fn         void i2cInit( unsigned long sclMode )
    \brief      Initialize the I2C master interface. Need to be called only once
    \param      sclMode
    \brief      Clock rate mode (See I2C_SCL_MODES)
	\return		void
*/
void i2cInit( unsigned long sclMode );


/*!
    \fn         void i2cStop( void )
    \brief      Terminates the data transfer and releases the I2C bus
	\return		void
*/
void i2cStop( void );


/*!
    \fn         uint8_t i2cStart( uint8_t addr )
    \brief      Issues a start condition, sends address and transfer direction
    \param      addr
	\brief		Address of I2C Slave
	\warning	Modify the address with I2C_READ(addr) or I2C_WRITE depending on the direction
    \return     uint8_t
    \retval     I2C_FAIL    Failed to access device
    \retval     I2C_OK      Device accessible
 */
uint8_t i2cStart( uint8_t addr );


/*!
    \fn         void i2cStartWait( uint8_t addr )
    \brief      Issues a start condition, sends address and transfer direction
                If device is busy, use ack polling to wait until device ready
    \param      addr
	\brief		Address and transfer direction of I2C device
    \return     none
 */
void i2cStartWait( uint8_t addr );


/*!
    \fn         uint8_t i2cWrite( uint8_t data )
    \brief      Send one byte to I2C device
    \param      data    byte to be transfered
    \return     uint8_t
    \retval     I2C_FAIL    Write failed
    \retval     I2C_OK      Write successful
 */
uint8_t i2cWrite( uint8_t data );


/*!
    \fn         uint8_t i2cReadAck( void )
    \brief      Read one byte from the I2C device, request more data from device
    \return     uint8_t
	\retval		Data read from I2C device
 */
uint8_t i2cReadAck( void );


/*!
    \fn         uint8_t i2cReadNak( void )
    \brief      Read one byte from the I2C device, read is followed by a stop condition
    \return     uint8_t
	\retval		Data read from I2C device
 */
uint8_t i2cReadNak( void );


#endif // I2CMASTER_H_INCLUDED
