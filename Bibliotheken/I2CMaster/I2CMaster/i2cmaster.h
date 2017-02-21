/*!
    \file       i2cmaster.h
    \brief      Implementation of the I2C (TWI) bus\n
                Basic source code provided by Peter Fleur\n
                Adapted and documented by André Sünnemann
    \author     André Sünnemann (a.suennemann@edv-peuker.de)
    \version    0.0.1
    \date       29.01.2014
*/

#ifndef I2CMASTER_H_INCLUDED
#define I2CMASTER_H_INCLUDED


#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#ifndef F_CPU
#error  "This library requires F_CPU defined"
#endif

#include <avr/io.h>
#include "avrConstants.h"


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
#define I2C_READ(addr)         ( (addr) + 1 )
#define I2C_WRITE(addr)        ( (addr) + 0 )
/*! @} */

/*!
    \defgroup   I2CMACROS           Usefull macros for I2C
    @{
    \def        i2cRepStart(addr)
    \brief      Issues a repeated start conditionn, sends address and transfer direction
                This is just an alias of uint8_t i2cStart( uint8_t addr )
 */
#define i2cRepStart(addr)       ( i2cStart(addr) )
/*! @} */

/*!
    \defgroup   I2C_STATUS_CODES    Status codes of I2C functions
    @{
    \def        I2C_OK
    \brief      Status Code OK

    \def        I2_FAIL
    \brief      Status Code Failure
*/
#define I2C_OK                  TRUE
#define I2C_FAIL                FALSE
/*! @} */

/*!
    \defgroup   I2C_SCL_MODES       Modes for I2C Clockrate
    @{
    \def        I2C_SCL_NORMAL
    \brief      Normal Clockrate (100kHz)

    \def        I2C_SCL_HIGH
    \brief      High Clockrate (400kHz)
*/
#define I2C_SCL_NORMAL          100000UL
#define I2C_SCL_HIGH            400000UL
/*! @} */

/*!
    \fn         void i2cInit( unsigned long int sclMode )
    \brief      Initialize the I2C master interace. Need to be called only once
    \param      unsigned long int sclMode
    \brief      Clock rate mode\nSee I2C_SCL_MODES
    \return     none
*/
void i2cInit( unsigned long int sclMode );


/*!
    \fn         void i2cStop( void )
    \brief      Terminates the data transfer and releases the I2C bus
    \param      void
    \return     none
*/
void i2cStop( void );


/*!
    \fn         uint8_t i2cStart( uint8_t addr )
    \brief      Issues a start condition, sends address and transfer direction
    \param      addr    Address of I2C Slave
    \return     uint8_t
    \retval     I2C_FAIL    Failed to access device
    \retval     I2C_OK      Device accessible
 */
uint8_t i2cStart( uint8_t addr );


/*!
    \fn         void i2cStartWait( uint8_t addr )
    \brief      Issues a start condition, sends address and transfer direction
                If device is busy, use ack polling to wait until device ready
    \param      addr    Address and transfer direction of I2C device
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
    \return     byte    Read from I2C device
 */
uint8_t i2cReadAck( void );


/*!
    \fn         uint8_t i2cReadNak( void )
    \brief      read one byte from the I2C device, read is followed by a stop condition
    \return     byte read from I2C device
 */
uint8_t i2cReadNak( void );


#endif // I2CMASTER_H_INCLUDED
