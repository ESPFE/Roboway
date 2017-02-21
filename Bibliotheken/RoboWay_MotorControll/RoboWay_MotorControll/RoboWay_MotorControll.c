/*
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "motorControll.h"





int main(void)
{
    uint8_t i = 0;
	uint8_t j = 0;

    mCInit();

    while(1)
    {
        mCSetSpeedLeft( i );
        mCSetSpeedRight( j );
        i += 1;
		j += 2;
		_delay_ms(100);
    }

    return 0;
}
