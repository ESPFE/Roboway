/*!
    \file		main.c
	\brief		Main program file	for RoboWay
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		11.02.2014
	\version	0.0.1
	\see        roboWay.h
	\see        roboWay.c
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/

#include <avr/io.h>
#include "./RoboWay/roboWay.h"



/*!
	\fn			int main( void )
	\brief		Main function for RoboWay
*/

int main(void)
{
    roboWayInit();
    roboWayLoop();


    // last never ending loop
    while(1)
    {

    }
}
