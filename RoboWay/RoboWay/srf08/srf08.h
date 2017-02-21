/*!
	\file		srf08.h
	\brief		This is the header file for the srf08 bibliothek
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		04.02.2014
	\version	1.8.4
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#ifndef SRF08_H_
#define SRF08_H_


#include "../i2cmaster/i2cmaster.h"
#include "../avrConstants.h"

#include <util/delay.h>

/*!
	\defgroup	SRF08_ADDRESSES	Possible values for the address register
	@{
	\def		SRF08_ADDR_00
	\brief		Possible address 0
	\def		SRF08_ADDR_01
	\brief		Possible address 1
	\def		SRF08_ADDR_02
	\brief		Possible address 2
	\def		SRF08_ADDR_03
	\brief		Possible address 3
	\def		SRF08_ADDR_04
	\brief		Possible address 4
	\def		SRF08_ADDR_05
	\brief		Possible address 5
	\def		SRF08_ADDR_06
	\brief		Possible address 6
	\def		SRF08_ADDR_07
	\brief		Possible address 7
	\def		SRF08_ADDR_08
	\brief		Possible address 8
	\def		SRF08_ADDR_09
	\brief		Possible address 9
	\def		SRF08_ADDR_10
	\brief		Possible address 10
	\def		SRF08_ADDR_11
	\brief		Possible address 11
	\def		SRF08_ADDR_12
	\brief		Possible address 12
	\def		SRF08_ADDR_13
	\brief		Possible address 13
	\def		SRF08_ADDR_14
	\brief		Possible address 14
	\def		SRF08_ADDR_15
	\brief		Possible address 15
*/
#define SRF08_ADDR_00		0xE0
#define SRF08_ADDR_01		0xE2
#define SRF08_ADDR_02		0xE4
#define SRF08_ADDR_03		0xE6
#define SRF08_ADDR_04		0xE8
#define SRF08_ADDR_05		0xEA
#define SRF08_ADDR_06		0xEC
#define SRF08_ADDR_07		0xEE
#define SRF08_ADDR_08		0xF0
#define SRF08_ADDR_09		0xF2
#define SRF08_ADDR_10		0xF4
#define SRF08_ADDR_11		0xF6
#define SRF08_ADDR_12		0xF8
#define SRF08_ADDR_13		0xFA
#define SRF08_ADDR_14		0xFC
#define SRF08_ADDR_15		0xFE
/*! @} */

/*!
	\defgroup	SRF08_MOD_ADDR	Modify an address for read or write operation for the I2C bus
	@{
	\def		SRF08_ADDR_READ(x)
	\brief		Modify the address for read operation
	\warning	Do not use I2C_READ(addr) or i2C_WRITE(addr) from i2cmaster.h
	
	\def		SRF08_ADDR_WRITE(x)
	\brief		Modify the address for write operation
	\warning	Do not use I2C_READ(addr) or i2C_WRITE(addr) from i2cmaster.h
*/
#define SRF08_ADDR_READ(x)		( (x) + 0x01 )
#define SRF08_ADDR_WRITE(x)		( (x) )
/*! @} */

/*!
	\defgroup	SRF08_REGISTERS	Registers of SRF08
	@{
	\def		SRF08_REG_VERSION
	\brief		Version of the SRF08 is stored here
	\def		SRF08_REG_COMMAND
	\brief		Register for commands - See SRF08_COMMANDS for possible values
	\def		SRF08_REG_LIGHT
	\brief		Value of measured light is stored here
	\def		SRF08_REG_GAIN
	\brief		Register for setting the gain
	\def		SRF08_REG_ECHO_H
	\brief		Value of measured distance - high byte
	\def		SRF08_REG_RANGE
	\brief		Range in mm
				( val * 43mm ) + 43mm
	
	\def		SRF08_REG_ECHO_L
	\brief		Value of measured distance - low byte
*/
#define SRF08_REG_VERSION		0x00
#define SRF08_REG_COMMAND		SRF08_REG_VERSION
#define SRF08_REG_LIGHT			0x01
#define SRF08_REG_GAIN			SRF08_REG_LIGHT
#define SRF08_REG_ECHO_H		0x02
#define SRF08_REG_RANGE			SRF08_REG_ECHO_H
#define SRF08_REG_ECHO_L		0x03

/*! @} */

/*!
	\defgroup	SRF08_COMMANDS		Commands for SRF08
	@{
	\def		SRF08_COM_INCH
	\brief		Start measure in inch
	\def		SRF08_COM_CM
	\brief		Start measure in cm
	\def		SRF08_COM_MKS
	\brief		Start measure in microseconds
	\def		SRF08_COM_ADDR0
	\brief		Sequence one for changing the I2C-Address
	\def		SRF08_COM_ADDR1
	\brief		Sequence two for changing the I2C-Address
	\def		SRF08_COM_ADDR2
	\brief		Sequence three for changing the I2C-Address
*/
#define SRF08_COM_INCH			0x50
#define SRF08_COM_CM			0x51
#define SRF08_COM_MKS			0x52
#define SRF08_COM_ADDR0			0xA0
#define SRF08_COM_ADDR1			0xAA
#define SRF08_COM_ADDR2			0xA5
/*! @} */

/*!
	\def		SRF08_AVAIL
	\brief		SRF08 is not available
	\def		SRF08_UNAVAIL
	\brief		SRF08 is not available or measure is pending
*/
#define SRF08_AVAIL				0x00
#define SRF08_UNAVAIL			0xFF

/*!
	\fn			void srf08Start( uint8_t addr, uint8_t command )
	\brief		Start a measure of distance and light
	\param		addr
	\brief		I2C address of the SRF08
	\param		command
	\brief		Modes for measure (see SRF08_COMMANDS)
	\return		none
*/
void srf08Start( uint8_t addr, uint8_t command );

/*!
	\def		srf08StartInch(addr)
	\brief		Start measure in inch
	
	\def		srf08StartCM(addr)
	\brief		Start measure in cm
	
	\def		srf08StartMcs(addr)
	\brief		Start measure in microseconds
*/
#define srf08StartInch(addr)	srf08Start( addr, SRF08_COM_INCH )
#define srf08StartCM(addr)		srf08Start( addr, SRF08_COM_CM )
#define srf08StartMcs(addr)		srf08Start( addr, SRF08_COM_MKS )

/*!
	\fn			uint8_t	srf08Status( uint8_t addr )
	\brief		Get status of the srf08
	\param		addr
	\brief		Address of the srf08 to check
	\return		uint8_t
	\retval		!= SRF08_UNAVAIL
	\brief		SRF08 is available
	\retval		SRF08_UNAVAIL
	\brief		SRF08 is unavailable or measurement is pending
*/
uint8_t srf08Status( uint8_t addr );

/*!
	\fn			uint16_t srf08GetDistance( uint8_t addr )
	\brief		Get measured distance
	\param		addr
	\brief		Address of the srf08
	\return		uint16_t
	\retval		Distance
*/
uint16_t srf08GetDistance( uint8_t addr );

/*!
	\fn			uint8_t srf08GetLight( uint8_t addr )
	\brief		Get measured light
	\param		addr
	\brief		Address of the srf08
	\return		uint8_t
	\retval		Measured Light
*/
uint8_t srf08GetLight( uint8_t addr );

/*!
	\fn			uint8_t srf08SetReg( uint8_t addr, uint8_t reg, uint8_t val )
	\brief		Change the value of an specified register
	\param		addr
	\brief		Address of the srf08
	\param		reg
	\brief		Address of register to change (see SRF08_REGISTERS)
	\param		val
	\brief		New value for register given by param reg
	\return		uint8_t
	\retval		SRF08_AVAIL
	\brief		Success
	\retval		SRF08_UNAVAIL
	\brief		Error
*/
uint8_t srf08SetReg( uint8_t addr, uint8_t reg, uint8_t val );

/*!
	\def		srf08SetRange(addr,range)
	\brief		Set range in mm
*/
#define srf08SetRange(addr,range)	srf08SetReg( addr, SRF08_REG_RANGE, ( (range) - 43 ) / 43 )

/*!
	\fn			uint8_t srf08SetAddr( uint8_t oldAddr, uint8_t newAddr )
	\brief		Set a new address for an SRF08
	\param		oldAddr
	\brief		Old address of the SRF08
	\param		newAddr
	\brief		New address of the SRF08 (see SRF08_ADDRESSES)
	\return		uint8_t
	\retval		SRF08_AVAIL
	\brief		Success
	\retval		SRF08_UNAVAIL
	\brief		Error
*/
uint8_t srf08SetAddr( uint8_t oldAddr, uint8_t newAddr );

#endif