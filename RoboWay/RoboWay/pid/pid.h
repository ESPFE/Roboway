/*!
	\file		pid.h
	\brief		This is the header file for pid closed loop controller for RoboWay
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		18.03.2014
	\version	1.6.2
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#ifndef PID_H_
#define PID_H_


#include <stdint.h>
#include "../avrConstants.h"


/*!
	\def				PID_MAX_ITERM
	\brief				Maximum value for pidData::iTerm
	
	\def				PID_MIN_ITERM
	\brief				Minimum value for pidData::iTerm
*/
#define PID_MAX_ITERM		200.0
#define PID_MIN_ITERM		-200.0



/*!
	\struct     pidData
	\brief      Data structure for PID functions

	\var        pidData::k
	\brief      Over all gain

	\var        pidData::kp
	\brief      Gain proportional part

	\var        pidData::ki
	\brief      Gain integral part

	\var        pidData::kd
	\brief      Gain differential part

	\var        pidData::minOut
	\brief      Minimum output value

	\var        pidData::maxOut
	\brief      Maximum output value

	\var        pidData::eOld
	\brief      Error of previous call of double updatePid( double rPos, double cPos, pidData *pd )

	\var        pidData::iTerm
	\brief      Integral term

*/
typedef struct
{
	double k;
	double kp;
	double ki;
	double kd;
	double minOut;
	double maxOut;
	double eOld;
	double iTerm;
} pidData;


/*!
    \fn         void pidInit( double k, double kp, double ki, double kd, double minOut, double maxOut, pidData *pd )
    \brief      Initial setup of a pid controller
    \param      k
    \brief      Over all gain
    \param      kp
    \brief      Gain proportional part
    \param      ki
    \brief      Gain integral part
    \param      kd
    \brief      Gain differential part
    \param      minOut
    \brief      Minimum output value
    \param      maxOut
    \brief      Maximum output value
    \param      pd
    \brief      Pointer to a pid working structure
    \return     void
*/
void pidInit( double k, double kp, double ki, double kd, double minOut, double maxOut, pidData *pd );


/*!
    \fn         double updatePid( double rPos, double cPos, pidData *pd )
    \brief      Calculate new output depending on reference position, current position and the data in the working structure
    \param      rPos
    \brief      Reference position
    \param      cPos
    \brief      Current position
    \param      pd
    \brief      Pointer to a pid working structure
    \return     double
    \brief      New value for motor speed
    \see        motorControll.h
    \retval     pidData::minOut <= x <= pidData::maxOut
*/
double updatePid( double rPos, double cPos, pidData *pd );



#endif /* PID_H_ */
