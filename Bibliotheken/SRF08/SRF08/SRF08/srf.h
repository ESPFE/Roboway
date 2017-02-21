/*!
    \file       srf.h
    \brief      This is the headerfile for the sonar sensor SRF08

                Here are all definitions and function for simple use of SRF08\n
                This module requires the modul "twi" in version 1.0 written by André Sünnemann\n\n

                Version: 1.0    14.11.2013\n
                Author:  André Sünnemann    a.suennemann@edv-peuker.de      EDV-Systeme Peuker KG
*/


#ifndef SRF_H_INCLUDED
#define SRF_H_INCLUDED

#include "twi.h"
#include "avrDefines.h"
//#include <util/delay.h>


/*!
    \defgroup   SRF_Registers   Registers of an SRF
    @{

    \def        SRF_REG_COMMAND
    \brief      Register for commands and softwareversion

                Read\n
                        ->  Get version of SRF Software\n
                        ->  If the returned value is SRF_MEASURE_PENDING the SRF is working\n\n
                Write   ->  Issue a command ( see SRF Commands )

    \def        SRF_REG_LIGHT
    \brief      Register for reading the value of the lightsensor

    \def        SRF_REG_ECHO_HIGH
    \brief      Measured distance - high byte

    \def        SRF_REG_ECHO_LOW
    \brief      Measured distance - low byte
*/
#define SRF_REG_COMMAND         0x00
#define SRF_REG_LIGHT           0x01
#define SRF_REG_ECHO_HIGH       0x02
#define SRF_REG_ECHO_LOW        0x03
/*! @} */

/*!
    \defgroup   SRF_COMMANDS    Commands for an SRF
    @{

    \def        SRF_COM_MEASURE_IN
    \brief      Start measurement in inch

    \def        SRF_COM_MEASURE_CM
    \brief      Start measurement in cm

    \def        SRF_COM_MEASURE_MCS
    \brief      Start measurement in microseconds

    \def        SRF_COM_CH_ADDR_1
    \brief      Change Address Command Byte 1

    \def        SRF_COM_CH_ADDR_2
    \brief      Change Address Command Byte 2

    \def        SRF_COM_CH_ADDR_3
    \brief      Change Address Command Byte 3
*/
#define SRF_COM_MEASURE_IN      0x50
#define SRF_COM_MEASURE_CM      0x51
#define SRF_COM_MEASURE_MCS     0x02

#define SRF_COM_CH_ADDR_1       0xA0
#define SRF_COM_CH_ADDR_2       0xAA
#define SRF_COM_CH_ADDR_3       0xA5
/*! @} */

/*!
    \defgroup   SRF_MAKROS_AND_OTHER_CONSTANTS  SRF Makros and other constants
    @{

    \def        SRF_MEASURE_PENDING
    \brief      This value is read from register SRF_REG_COMMAND if the SRF is working

    \def        SRF_MEASURE_READY
    \brief      This value is read from register SRF_REG_COMMAND if the SRF has finished a measurement

    \def        SRF_MODIFY_ADDRESS(x)
    \brief      Modify the address of SRF for I2C comunication

    \def        SRF_UNAVAILABLE
    \brief      An error occured or the SRF is not on the bus

    \def        SRF_AVAILABLE
    \brief      Everything OK or the SRF is on the bus
*/
#define SRF_MEASURE_PENDING     0xFF
#define SRF_MEASURE_READY       0x00
#define SRF_MODIFY_ADDRESS(x)   ((x)>>1)
#define SRF_UNAVAILABLE         0xFF
#define SRF_AVAILABLE           0x00
#define SRF_UNAVAILABLE_16		0xFFFF
/*! @} */

/*!
    \defgroup   SRF_POSSIBLE_ADDRESSES  SRF possible addresses
    @{

    \def        SRF_ADDR_00
    \def        SRF_ADDR_01
    \def        SRF_ADDR_02
    \def        SRF_ADDR_03
    \def        SRF_ADDR_04
    \def        SRF_ADDR_05
    \def        SRF_ADDR_06
    \def        SRF_ADDR_07
    \def        SRF_ADDR_08
    \def        SRF_ADDR_09
    \def        SRF_ADDR_10
    \def        SRF_ADDR_11
    \def        SRF_ADDR_12
    \def        SRF_ADDR_13
    \def        SRF_ADDR_14
    \def        SRF_ADDR_15

*/
#define SRF_ADDR_00             0xE0
#define SRF_ADDR_01             0xE2
#define SRF_ADDR_02             0xE4
#define SRF_ADDR_03             0xE6
#define SRF_ADDR_04             0xE8
#define SRF_ADDR_05             0xEA
#define SRF_ADDR_06             0xEC
#define SRF_ADDR_07             0xEE
#define SRF_ADDR_08             0xF0
#define SRF_ADDR_09             0xF2
#define SRF_ADDR_10             0xF4
#define SRF_ADDR_11             0xF6
#define SRF_ADDR_12             0xF8
#define SRF_ADDR_13             0xFA
#define SRF_ADDR_14             0xFC
#define SRF_ADDR_15             0xFE
/*! @} */



/*!
    \fn         void SRFStartMeasure( uint8_t address, uint8_t command )
    \brief      Send a command to the SRF08 that starts a measure

    \param      address
    \brief      address of SRF to start measure on

                address must have the Format 0b0xxxxxxx (see SRF_MODIFY_ADDRESS)

    \param      command
    \brief      Command wich to send to the SRF

                Posible values are:\n
                - SRF_COM_MEASURE_IN   -> start measure in inch\n
                - SRF_COM_MEASURE_CM   -> start measure in centimeter\n
                - SRF_COM_MEASURE_MCS  -> start measure in microseconds\n

    \return     void
*/
void SRFStartMeasure( uint8_t address, uint8_t command );


/*!
    \fn         uint8_t SRFAvailable( uint8_t address )
    \brief      Check if a SRF is available or not

    \param      address
    \brief      address of SRF to check

                address must have the Format 0b0xxxxxxx (see SRF_MODIFY_ADDRESS)

    \return     uint8_t
    \brief      SRF_MEASURE_READY       ->  SRF has finished a measurement (so it has nothing to do)
                SRF_MEASURE_PENDING     ->  the SRF working at the moment, or the address isn't online
*/
uint8_t SRFAvailable( uint8_t address );


/*!
    \fn         uint16_t SRFReadDistance( uint8_t address )
    \brief      Get the measured distance

    \param      address
    \brief      address of SRF to read distance from

                address must have the Format 0b0xxxxxxx (see SRF_MODIFY_ADDRESS)

    \return     uint16_t
    \brief      Measured distance depending on the command wich was issued by void SRF08StartMeasure( uint8_t address, uint8_t command );
*/
uint16_t SRFReadDistance( uint8_t address );

/*!
    \fn         uint8_t SRFReadLight( uint8_t address )
    \brief      Start a measure and get the value of the lightsensor

    \param      address
    \brief      Address of the SRF

    \return     uint8_t
    \brief      Value of the lightsensor register
*/
uint8_t SRFReadLight( uint8_t address );

/*!
    \fn         uint8_t SRFChangeAddress8( uint8_t oldAddress, uint8_t newAddress )
    \brief      Change the address of an SRF
    \warning    It must be only one SRF on the I2C-Bus

    \param      oldAddress
    \brief      Old address of the SRF

    \param      newAddress
    \brief      New address of the SRF

    \return     uint8_t
    \brief      Change Succeeded    ->  SRF_AVAILABLE
                ERROR               ->  SRF_UNAVAILABLE
*/
uint8_t SRFChangeAddress( uint8_t oldAddress, uint8_t newAddress );


#endif // SRF08_H_INCLUDED
