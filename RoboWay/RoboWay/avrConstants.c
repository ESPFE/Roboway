/*!
	\file		avrConstants.c
	\brief		Global constants and settings for AtMega 8 bit micro controllers (source code)
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		11.02.2014
	\version	2.1.5
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#include "avrConstants.h"


double constrainD( double val, double min, double max )
{
	if( val < min )
	{
		return min;
	}
	else if( val > max )
	{
		return max;
	}
	return val;
}