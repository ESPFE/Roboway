/*!
	\file		adxl354.h
	\brief		This is the header file for simple use of the digital accelerometer ADXL354
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		31.01.2014
	\version	1.4.2
		
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#ifndef ADXL354_H_
#define ADXL354_H_


#include <avr/io.h>
#include "../i2cmaster/i2cmaster.h"


/*!
	\def		ADXL354_STD_DEVID
	\brief		Standard address of an ADXL354 on I2C
*/
#define ADXL354_STD_DEVID			0x53


/*!
	\defgroup	ADXL354_REGISTERS		Alias names of ADXL354 Registers (refer to site 24-27 of the ADXL354 datasheet)
	@{
	\def		ADXL354_REG_DEVID
	\brief		The DEVID holds a fixed device ID (see ADXL354_STD_DEVID )

	\def		ADXL354_REG_THRESH_TAP
	\brief		The THRESH_TAP register holds the threshold value for tap interrupts
				Data format is unsigned

	\def		ADXL354_REG_OFSX
	\brief		Offset X-Axis for calibration in twos complement format

	\def		ADXL354_REG_OFSY
	\brief		Offset X-Axis for calibration in twos complement format

	\def		ADXL354_REG_OFSZ
	\brief		Offset X-Axis for calibration in twos complement format

	\def		ADXL354_REG_TAP_DUR
	\brief		Maximum time than an event must be above the THRESH_TAP to qualifiy as a tap event (625us/LSB)
				A value of 0 disables the single / double tap events

	\def		ADXL354_REG_TAP_LATENT
	\brief		Latency from detection of a tap to start the time window
                (1.25 ms/LSB)

	\def		ADXL354_REG_TAP_WINDOW
	\brief		Time window from one to a second valid tap

	\def		ADXL354_REG_THRESH_ACT
	\brief      Threshold value for detecting activity
                unsigned (62.5mg/LSB)

	\def		ADXL354_REG_THRESH_INACT
	\brief      Threshold value for detecting inactivity
                unsigned (62.5mg/LSB)

	\def		ADXL354_REG_TIME_INACT
	\brief      Time value that acceleration must be under the value of ADXL354_REG_THRESH_INACT to generate an inactivity interrupt
                unsigned (1s/LSB)

	\def		ADXL354_REG_ACT_INACT_CTL
	\brief      Control register control activity and inactivity interrupts

	\def		ADXL354_REG_THRESH_FF
	\brief      This register holds the threshold value for free-fall detection
                unsigned (62.5mg/LSB)
                a value between 300 and 600mg is recommended

	\def		ADXL354_REG_TIME_FF
	\brief      Minimum time that the value of all axis must be less than ADXL354_REG_THRESH_FF
                unsigned (5ms/LSB)

	\def		ADXL354_REG_TAP_AXES_CTL
	\brief      Enable/disable tap interrupts

	\def		ADXL354_REG_ACT_TAP_STATUS
	\brief      Act/Tap status - indicates witch axis was first involved in an tap or activity event
                READ ONLY

	\def		ADXL354_REG_CTL_BW_RATE
	\brief      Set bandwidth and output data rate
                Default: 0x0A   -> 100Hz
                See ADXL354_REG_BW_RATE_MODES

	\def		ADXL354_REG_CTL_POWER
	\brief      Power saving features control

	\def		ADXL354_REG_INT_EN
	\brief      Interrupt enable / disable
                Refer to site 20 / 26

	\def		ADXL354_REG_INT_MAP
	\brief      Interrupt and pin mappings

	\def		ADXL354_REG_INT_SRC
	\brief      Interrupt sources - READ ONLY

	\def		ADXL354_REG_DATA_FORMAT
	\brief      Controls the presentation of data to register 0x32 through register 0x37

	\def		ADXL354_REG_DATAX_L
	\brief      Data of X-Axis Low Byte (READ ONLY)

	\def		ADXL354_REG_DATAX_H
	\brief      Data of X-Axis High Byte (READ ONLY)

	\def		ADXL354_REG_DATAY_L
	\brief      Data of Y-Axis Low Byte (READ ONLY)

	\def		ADXL354_REG_DATAY_H
	\brief      Data of Y-Axis High Byte (READ ONLY)

	\def		ADXL354_REG_DATAZ_L
	\brief      Data of Z-Axis Low Byte (READ ONLY)

	\def		ADXL354_REG_DATAZ_H
	\brief      Data of Z-Axis High Byte (READ ONLY)

	\def		ADXL354_REG_CTL_FIFO
	\brief      FIFO Modes

	\def		ADXL354_REG_FIFO_STATUS
	\brief      FIFO Status
*/
#define ADXL354_REG_DEVID			0x00
#define ADXL354_REG_THRESH_TAP		0x1D
#define ADXL354_REG_OFSX			0x1E
#define ADXL354_REG_OFSY			0x1F
#define ADXL354_REG_OFSZ			0x20
#define ADXL354_REG_TAP_DUR			0x21
#define ADXL354_REG_TAP_LATENT		0x22
#define ADXL354_REG_TAP_WINDOW		0x23
#define ADXL354_REG_THRESH_ACT		0x24
#define ADXL354_REG_THRESH_INACT	0x25
#define ADXL354_REG_TIME_INACT		0x26
#define ADXL354_REG_ACT_INACT_CTL	0x27
#define	ADXL354_REG_THRESH_FF		0x28
#define ADXL354_REG_TIME_FF			0x29
#define ADXL354_REG_TAP_AXES_CTL	0x2A
#define ADXL354_REG_ACT_TAP_STATUS	0x2B
#define ADXL354_REG_CTL_BW_RATE		0x2C
#define ADXL354_REG_CTL_POWER		0x2D
#define ADXL354_REG_INT_EN			0x2E
#define ADXL354_REG_INT_MAP			0x2F
#define ADXL354_REG_INT_SRC			0x30
#define ADXL354_REG_DATA_FORMAT		0x31
#define ADXL354_REG_DATAX_L			0x32
#define ADXL354_REG_DATAX_H			0x33
#define ADXL354_REG_DATAY_L			0x34
#define ADXL354_REG_DATAY_H			0x35
#define ADXL354_REG_DATAZ_L			0x36
#define ADXL354_REG_DATAZ_H			0x37
#define ADXL354_REG_CTL_FIFO		0x38
#define ADXL354_REG_FIFO_STATUS		0x39
/*! @} */


/*!
    \defgroup   ADXL354_REG_BW_RATE_MODES       Possible bitrates for bit rate register (refert to table 8 in datasheet)
    @{
    \def        ADXL354_REG_BW_RATE_400
    \brief      Value for ADXL354_REG_BW_RATE in I2C 400 kHz mode
    \def        ADXL354_REG_BW_RATE_100
    \brief      Value for ADXL354_REG_BW_RATE in I2C 100 kHz mode
*/
#define ADXL354_REG_BW_RATE_400     0b1100
#define ADXL354_REG_BW_RATE_100     0b1010
/*! @} */


/*!
    \fn         uint8_t adxl354Init( uint8_t addr, uint8_t bwRate )
    \brief      Initial setup of an ADXL354 - need to be called only once
    \param      addr
    \brief      Address of the ADXL354 (refer to ADXL354_STD_DEVID)
    \param      bwRate
    \brief      Bit rate setting (refer to ADXL354_REG_BW_RATE_MODES)
    \return     uint8_t
    \retval     true    -> success
    \retval     false   -> failure
*/
uint8_t adxl354Init( uint8_t addr, uint8_t bwRate );


/*!
	\defgroup	ADXL354_AXIS		Alias names of ADXL354 AXIS
	@{
	\def		ADXL354_AXIS_X
	\brief		Start register of X-Axis
	
	\def		ADXL354_AXIS_Y
	\brief		Start register of Y-Axis
	
	\def		ADXL354_AXIS_Z
	\brief		Start register of Z-Axis
*/
#define ADXL354_AXIS_X				ADXL354_REG_DATAX_L
#define ADXL354_AXIS_Y				ADXL354_REG_DATAY_L
#define ADXL354_AXIS_Z				ADXL354_REG_DATAZ_L
/*!	@} */


/*!
	\fn			uint8_t adxl354GetAccel( uint8_t addr, int8_t axis, int16_t *val )
	\brief		Get current acceleration of one axis
	\param		addr
	\brief		Address of the ADXL354
	\param		axis
	\brief		Witch axis (see ADXL354_AXIS)
	\param		val
	\brief		Value of axis
	\return     uint8_t
	\retval     true
	\brief		success
	\retval     false
	\brief		failure
*/
uint8_t adxl354GetAccel( uint8_t addr, int8_t axis, int16_t *val );


/*!
    \fn         uint8_t adxl354GetAccelAll( uint8_t addr, int16_t *x, int16_t *y, int16_t *z )
    \brief      Get current acceleration of all three axis
    \param      addr
    \brief      Address of the ADXL354
    \param      *x
    \brief      Value of X-Axis
    \param      *y
    \brief      Value of Y-Axis
    \param      *z
    \brief      Value of Z-Axis
    \return     uint8_t
    \retval     true
    \brief		success
    \retval     false
    \brief		failure
*/
uint8_t adxl354GetAccelAll( uint8_t addr, int16_t *x, int16_t *y, int16_t *z );


/*!
	\defgroup	ADXL354_MACROS	Macros for simpler use of the ADXL354
	@{
	\def		ADXL354_GET_ACCEL_X(addr,val)
	\brief		Get the current acceleration of X-Axis
	
	\def		ADXL354_GET_ACCEL_Y(addr,val)
	\brief		Get the current acceleration of Y-Axis
	
	\def		ADXL354_GET_ACCEL_Z(addr,val)
	\brief		Get the current acceleration of Z-Axis
*/
#define ADXL354_GET_ACCEL_X(addr,val)	adxl354GetAccel( addr, ADXL354_AXIS_X, val )
#define ADXL354_GET_ACCEL_Y(addr,val)	adxl354GetAccel( addr, ADXL354_AXIS_Y, val )
#define ADXL354_GET_ACCEL_Z(addr,val)	adxl354GetAccel( addr, ADXL354_AXIS_Z, val )
/*! @} */


/*!
	\fn			uint8_t adxl354SetReg( uint8_t addr, uint8_t reg, uint8_t val )
	\brief		Set the value of an register
	\param		addr
	\brief		Address of the ADXL354
	\param		reg
	\brief		Address of the register (see ADXL354_REGISTERS)
	\param		val
	\brief		New value for the register
	\return		uint8_t
	\retval		true
	\brief		Success
	\retval		false
	\brief		Failure
*/
uint8_t adxl354SetReg( uint8_t addr, uint8_t reg, uint8_t val );



#endif /* ADXL354_H_ */
