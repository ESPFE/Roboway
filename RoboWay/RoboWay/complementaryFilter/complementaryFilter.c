/*!
	\file		complementaryFilter.c
	\brief		This is the source code file for complementary filter
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		18.03.2014
	\version	1.3.1
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#include "complementaryFilter.h"



void compFilterInit( double gyroGain, double accGain, double dt, compFilterData *fd )
{
    fd->gG = gyroGain;
    fd->aG = accGain;
    fd->dt = dt;
    fd->aO = 0.0;
}



double compFilterGetAngle( double gyroData, double accData, compFilterData *fd )
{
	/*!
	    \code
	    double compFilterGetAngle( double gyroData, double accData, compFilterData *fd )
	    {
	      fd->aO = fd->gG * ( fd->aO + gyroData * fd->dt ) + fd->aG * accData;
	      return fd->aO;
	    }
	    \endcode
	*/
        // high pass filter for gyroscope            // low pass filter for accelerometer
	fd->aO = fd->gG * ( fd->aO + gyroData * fd->dt ) + fd->aG * accData;
	return fd->aO;
}

