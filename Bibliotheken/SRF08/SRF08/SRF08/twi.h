/*!
    \file       twi.h
    \brief      This is the headerfile for the avr two wire interface (twi, I²C)

                Here are all definitions and function for simple use of AVR TWI
                This module requires the modul "avrDefines" in version 1.0 written by André Sünnemann\n\n

                Version: 1.0    14.11.2013\n
                Author:  André Sünnemann    a.suennemann@edv-peuker.de      EDV-Systeme Peuker KG
*/


#ifndef TWI_H_INCLUDED
#define TWI_H_INCLUDED


#include <avr/io.h>
#include "avrDefines.h"
//#include "usart.h"


/*!
    \defgroup twiCLKModes Modes for TWI Clock (PIN SCL)
    @{
*/
/*!
    \def        TWI_CLK_NORMAL_MODE
    \brief      Constant for TWI to run in normal mode
*/
/*!
    \def        TWI_CLK_FAST_MODE
    \brief      Constant for TWI to run in fast mode
*/
#define TWI_CLK_NORMAL_MODE false
#define TWI_CLK_FAST_MODE   true
/*! @} */


/*!
    \defgroup   twiModes    Modes for TWI
    @{
*/
/*!
    \def        TWI_MASTER
    \brief      Set TWI to operate in master mode
*/
/*!
    \def        TWI_SLAVE
    \brief      Set TWI to operate in slave mode
*/
#define TWI_MASTER  false
#define TWI_SLAVE   true
/*! @} */

/*! \defgroup   TWI_ERROR_DETECTION     Return values of functions for errordetection
    @{

    \def        TWI_OK
    \brief      Returned by a function if no error occured

    \def        TWI_ERROR
    \brief      Returned by a function if an error occured
*/
#define TWI_OK      true
#define TWI_ERROR   false
/*! @} */



/*!
    \fn         void twiSetup( bool mode, bool clkMode, uint8_t addr )
    \brief      setup the TWI

    \param      mode
    \brief      TWI_MASTER or TWI_SLAVE

    \param      clkMode
    \brief      TWI_CLK_NORMAL_MODE or TWI_CLK_FAST_MODE

    \param      addr
    \brief      this is used for the adress when the controller operates in TWI_SLAVE
*/
void twiSetup( bool mode, bool clkMode, uint8_t addr );


/*!
    \fn         uint8_t twiStart( void )
    \brief      enable twi, send start condition and enable interrupts

                use this function before sending some data over TWI

    \return     uint8_t
    \brief      Return value for detecting some errors

                TWI_OK   ->  everything ok\n
                TWI_ERROR   ->  an error occured during start
*/
uint8_t twiStart( void );


/*!
    \fn         void twiStop( void )
    \brief      disable twi and free bus
*/
void twiStop( void );


/*!
    \fn        uint8_t twiSelectRead( uint8_t addr )
    \brief      Prepare reading from a slave ( master mode only )

    \param      addr
    \brief      Adress of slave to read from

    \return     uint8_t
    \brief      Return value for detecting some errors

                TWI_OK   ->  everything ok\n
                TWI_ERROR   ->  an error occured during start
*/
uint8_t twiSelectRead( uint8_t addr );


/*!
    \fn         uint8_t twiSelectWrite( uint8_t addr )
    \brief      Prepare writing to a slave ( master mode only )

    \param      addr
    \brief      Adress of slave to write to

    \return     uint8_t
    \brief      Return value for detecting some errors

                TWI_ERROR   ->  everything ok\n
                TWI_OK      ->  an error occured
*/
uint8_t twiSelectWrite( uint8_t addr );


/*!
    \fn         uint8_t twiRead( uint8_t data[], uint8_t length )
    \brief      Read from slave

                You have to select the slave to read from with twiSelectWrite( uint8_t addr )\n
                before you can read data with this function

    \param      data
    \brief      Array to store read data

    \param      length
    \brief      length of array ( uint8_t data[] ) int bytes / length of data to read in bytes

    \return     uint8_t
    \brief      Return value for detecting some errors

                TWI_OK      ->  everything ok\n
                TWI_ERROR   ->  an error occured
*/
uint8_t twiRead( uint8_t data[], uint8_t length );


/*!
    \fn         uint8_t twiWrite( uint8_t data[], uint8_t length )
    \brief      Write to slave

                You have to select the slave to write to with twiSelectWrite( uint8_t addr )\n
                before you can write data with this function

    \param      data[]
    \brief      Array with data you want to write to the slave

    \param      length
    \brief      length of array ( uint8_t data[] ) int bytes

    \return     uint8_t
    \brief      Return value for detecting some errors

                TWI_OK      ->  everything ok\n
                TWI_ERROR   ->  an error occured

*/
uint8_t twiWrite( uint8_t data[], uint8_t length );



#endif // TWI_H_INCLUDED
