/*!
	\file		l3g4200d.h
	\brief		This is the header file for the l3g4200d gyro bibliothek
	\author		Andre Suennemann ( a.suennemann@edv-peuker.de | www.edv-peuker.de )
	\date		11.02.2014
	\version	0.0.1
*/


#ifndef L3G4200D_H_
#define L3G4200D_H_

#include <avr/io.h>
#include "../avrConstants.h"
#include "../i2cmaster/i2cmaster.h"
#include "../usart/usart.h"


/*!
	\defgroup	L3G4200D_DEVICE_IDS		Possible device ids of an L3G4200D Gyroscope
	@{
	\def		L3G4200D_DEVID_0
	\brief		Possible address 0 of an L3G4200D on I2C
	\def		L3G4200D_DEVID_1
	\brief		Possible address 1 of an L3G4200D on I2C
*/
#define L3G4200D_DEVID_0			0x68
#define L3G4200D_DEVID_1			0x69
/*! @} */


/*!
	\defgroup	L3G4200D_REGISTERS		All nessesary registers of an L3G4200D
	@{
	\def		L3G4200D_REG_WAI
	\brief		Device identification register (Who Am I)
	
	\def		L3G4200D_REG_CTRL_1
	\brief		Control register 1\n
				Refer to table 20 of in data sheet
				
	\def		L3G4200D_REG_CTRL_2
	\brief		Control register 2\n
				Refer to table 28 in data sheet
				
	\def		L3G4200D_REG_CTRL_3
	\brief		Control register 3\n
				Refer to table 28 in data sheet
				
	\def		L3G4200D_REG_CTRL_4
	\brief		Control register 4\n
				Refer to table 30 in data sheet
				
	\def		L3G4200D_REG_CTRL_5
	\brief		Control register 5\n
				Refer to table 33 in data sheet
				
	\def		L3G4200D_REG_REF
	\brief		Reference value for interrupt generation\n
				Refer to table 37 / 38 in data sheet
	
	\def		L3G4200D_REG_TEMP
	\brief		Temperatur data\n
				Refer to table 39 / 40 in data sheet
	
	\def		L3G4200D_REG_STATUS
	\brief		Status register\n
				Refer to table 41 / 42 in data sheet
	
	\def		L3G4200D_REG_DATAX_L
	\brief		X-Axis angular rate data - Low Byte
	
	\def		L3G4200D_REG_DATAX_H
	\brief		X-Axis angular rate data - High Byte
	
	\def		L3G4200D_REG_DATAY_L
	\brief		Y-Axis angular rate data - Low Byte
	
	\def		L3G4200D_REG_DATAY_H
	\brief		Y-Axis angular rate data - High Byte
	
	\def		L3G4200D_REG_DATAZ_L
	\brief		Z-Axis angular rate data - Low Byte
	
	\def		L3G4200D_REG_DATAZ_H
	\brief		Z-Axis angular rate data - High Byte
	
	\def		L3G4200D_REG_CTRL_FIFO
	\brief		Register for FIFO configuration\n
				Refer to table 43 / 44 / 45
	
	\def		L3G4200D_REG_SRC_FIFO
	\brief		Source configuration for FIFO\n
				Refer to table 46 / 47
	
	\def		L3G4200D_REG_CFG_INT1
	\brief		Configuration register for interrupt 1\n
				Refer to table 48 / 49
	
	\def		L3G4200D_REG_SRC_INT1
	\brief		Configuration register for interrupt source\n
				Refer to table 50 / 51
	
	\def		L3G4200D_REG_INT1_TSH_XH
	\brief		Interrupt threshold X-Axis - High Byte
	
	\def		L3G4200D_REG_INT1_TSH_XL
	\brief		Interrupt threshold X-Axis - Low Byte
	
	\def		L3G4200D_REG_INT1_TSH_YH
	\brief		Interrupt threshold Y-Axis - High Byte
	
	\def		L3G4200D_REG_INT1_TSH_YL
	\brief		Interrupt threshold Y-Axis - Low Byte
	
	\def		L3G4200D_REG_INT1_TSH_ZH
	\brief		Interrupt threshold Z-Axis - High Byte
	
	\def		L3G4200D_REG_INT1_TSH_ZL
	\brief		Interrupt threshold Z-Axis - Low Byte
	
	\def		L3G4200D_REG_INT1_DUR
	\brief		Minimum, wait and max duration of an interrupt\n
				Refer to table 64 / 65 and figure 20 / 21 in data sheet
*/
#define L3G4200D_REG_WAI			0x0F
#define L3G4200D_REG_CTRL_1			0x20
#define L3G4200D_REG_CTRL_2			0x21
#define L3G4200D_REG_CTRL_3			0x22
#define L3G4200D_REG_CTRL_4			0x23
#define L3G4200D_REG_CTRL_5			0x24
#define L3G4200D_REG_REF			0x25
#define L3G4200D_REG_TEMP			0x26
#define L3G4200D_REG_STATUS			0x27
#define L3G4200D_REG_DATAX_L		0x28
#define L3G4200D_REG_DATAX_H		0x29
#define L3G4200D_REG_DATAY_L		0x2A
#define L3G4200D_REG_DATAY_H		0x2B
#define L3G4200D_REG_DATAZ_L		0x2C
#define L3G4200D_REG_DATAZ_H		0x2D
#define L3G4200D_REG_CTRL_FIFO		0x2E
#define L3G4200D_REG_SRC_FIFO		0x2F
#define L3G4200D_REG_CFG_INT1		0x30
#define L3G4200D_REG_SRC_INT1		0x31
#define L3G4200D_REG_INT1_TSH_XH	0x32
#define L3G4200D_REG_INT1_TSH_XL	0x33
#define L3G4200D_REG_INT1_TSH_YH	0x34
#define L3G4200D_REG_INT1_TSH_YL	0x35
#define L3G4200D_REG_INT1_TSH_ZH	0x36
#define L3G4200D_REG_INT1_TSH_ZL	0x37
#define L3G4200D_REG_INT1_DUR		0x38
/*! @} */


/*!
	\defgroup	L3G4200D_BW_RATE	Possible Bit and Data Rates for L3G4200D_REG_CTRL_1 (refer to table 22 in data sheet)
	@{
	\def		L3G4200D_BW_RATE_100
	\brief		Bit and Data Rate for 100 kHz I2C
	
	\def		L3G4200D_BW_RATE_400
	\brief		Bit and Data Rate for 400 kHz I2C
*/
#define L3G4200D_BW_RATE_100		0b00110000
#define L3G4200D_BW_RATE_400		0b10000000
/*! @} */

/*!
	\fn			uint8_t l3g4200dInit( uint8_t addr, uint8_t bwRate )
	\brief      Initial setup of an L3G4200D - need to be called only once
	\param      addr
	\brief      Address of the L3G4200D (refer to L3G4200D_DEVICE_IDS)
	\param      bwRate
	\brief      Bit rate setting (refer to L3G4200D_BW_RATE)
	\return     uint8_t
	\retval     true    -> success
	\retval     false   -> fuck you bitch!!
*/
uint8_t l3g4200dInit( uint8_t addr, uint8_t bwRate );


/*!
	\fn			uint8_t l3g4200dGetReg( uint8_t addr, uint8_t reg )
	\brief		Get the value of a specified register
	\param		addr
	\brief		Address of the L3G4200D
	\param		reg
	\brief		Address of the register (see L3G4200D_REGISTERS)
	\return		uint8_t
	\retval		Value of the register
*/
uint8_t l3g4200dGetReg( uint8_t addr, uint8_t reg );


/*!
	\def		l3g4200dGetTemp( addr )
	\brief		Get measured temperature
*/
#define l3g4200dGetTemp( addr )		 l3g4200dGetReg( addr, L3G4200D_REG_TEMP )


/*!
	\fn			uint8_t l3g4200dGetAR( uint8_t addr, uint8_t axis, int16_t *val )
	\brief		Get angular rate data of one axis
	\param		addr
	\brief		Address of the L3G4200D
	\param		axis
	\brief		Witch axis (see L3G4200D_AXIS)
	\param		val
	\brief		Value of axis
	\return		uint8_t
	\retval		true
	\brief		success
	\retval		false
	\brief		failure
*/
uint8_t l3g4200dGetAR( uint8_t addr, uint8_t axis, int16_t *val );


/*!
	\defgroup	L3G4200D_AXIS	Alias names of L3G4200D Axis
	@{
	\def		L3G4200D_AXIS_X
	\brief		Start register of X-Axis
	
	\def		L3G4200D_AXIS_Y
	\brief		Start register of Y-Axis
	
	\def		L3G4200D_AXIS_Z
	\brief		Start register of Z-Axis
*/
#define L3G4200D_AXIS_X				L3G4200D_REG_DATAX_L
#define L3G4200D_AXIS_Y				L3G4200D_REG_DATAY_L
#define L3G4200D_AXIS_Z				L3G4200D_REG_DATAZ_L
/*! @} */


/*!
	\defgroup	L3G42000D_MACROS	Macros for simpler use of the L3G4200D
	@{
	\def		L3G4200D_GET_AR_X(addr,val)
	\brief		Get current angular rate data of X-Axis
	
	\def		L3G4200D_GET_AR_Y(addr,val)
	\brief		Get current angular rate data of Y-Axis
	
	\def		L3G4200D_GET_AR_Z(addr,val)
	\brief		Get current angular rate data of Z-Axis
*/
#define L3G4200D_GET_AR_X(addr,val)		l3g4200dGetAR( addr, L3G4200D_REG_DATAX_L, val )
#define L3G4200D_GET_AR_Y(addr,val)		l3g4200dGetAR( addr, L3G4200D_REG_DATAY_L, val )
#define L3G4200D_GET_AR_Z(addr,val)		l3g4200dGetAR( addr, L3G4200D_REG_DATAZ_L, val )
/*! @} */


/*!
	\fn		uint8_t l3g4200dGetARAll( uint8_t addr, int16_t *x, int16_t *y, int16_t *z )
	\brief		Get current angular rate data of all three axis
	\param		addr
	\brief		Address of the L3G4200D
	\param		x
	\brief		Value of X-Axis
	\param		y
	\brief		Value of Y-Axis
	\param		z
	\brief		Value of Z-Axis
	\return		uint8_t
	\retval		true
	\brief		success
	\retval		false
	\brief		failure
*/
uint8_t l3g4200dGetARAll( uint8_t addr, int16_t *x, int16_t *y, int16_t *z );


#endif /* L3G4200D_H_ */