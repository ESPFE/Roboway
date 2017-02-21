/*
 * RoboWay.c
 *
 * Created: 27.01.2014 22:19:56
 *  Author: suennemann
 */


//#define F_CPU 16000000UL


#include <avr/io.h>
#include "./RoboWay/roboWay.h"




int main(void)
{
    roboWayInit();
    roboWayLoop();


    // last never ending loop
    while(1)
    {

    }
}
