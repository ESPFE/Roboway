/*!
	\file		pid.c
	\brief		This is the source code file of the pid controller
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		18.03.2014
	\version	1.6.2
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#include "pid.h"

void pidInit( double k, double kp, double ki, double kd, double minOut, double maxOut, pidData *pd )
{
	pd->k = k;
	pd->kp = kp;
	pd->ki = ki;
	pd->kd = kd;
	pd->minOut = minOut;
	pd->maxOut = maxOut;
	pd->eOld = 0;
	pd->iTerm = 0;
}

/*
double updatePid( double rPos, double cPos, pidData *pd )
{
	double error = 0.0;
	double pTerm = 0.0;
	double iTerm = 0.0;
	double dTerm = 0.0;

	error = rPos - cPos;
	pTerm = pd->kp * error;
	pd->iError += error;
	iTerm = pd->ki * constrainD( pd->iError, -MAX_IERROR, MAX_IERROR);
	dTerm = pd->kd * ( error - pd->eOld );
	pd->eOld = error;
	return constrainD( pTerm + iTerm + dTerm, pd->minOut, pd->maxOut );
}
*/



double updatePid( double rPos, double cPos, pidData *pd )
{
	/*!
		\code
			double updatePid( double rPos, double cPos, pidData *pd )
			{
					double error = 0.0;
					double pTerm = 0.0;
					double dTerm = 0.0;
					
					error = rPos - cPos;
					pTerm = pd->kp * error;
					pd->iTerm = constrainD( pd->iTerm + pd->ki * error, PID_MIN_ITERM, PID_MAX_ITERM );
					dTerm = pd->kd * ( error - pd->eOld );
					return constrainD( pTerm + pd->iTerm + dTerm, pd->minOut, pd->maxOut );
			}
		\endcode
	*/
	double error = 0.0;
	double pTerm = 0.0;
	double dTerm = 0.0;
	
	error = rPos - cPos;
	pTerm = pd->kp * error;
	pd->iTerm = constrainD( pd->iTerm + pd->ki * error, PID_MIN_ITERM, PID_MAX_ITERM );
	dTerm = pd->kd * ( error - pd->eOld );
	return constrainD( pTerm + pd->iTerm + dTerm, pd->minOut, pd->maxOut );
}