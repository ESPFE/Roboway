#include "avrDefines.h"


char iToC( int8_t i )
{
    if( i > 9 )
    {
        return -1;
    }

    return (char)( i + '0' );
}

char* i8ToStr( int8_t i, char *buffer, uint8_t len )
{
    len -= 1;
    buffer[len] = '\0';
    while( len && i )
    {
        len -= 1;
        buffer[len] = iToC( i % 10 );
        i /= 10;
    }
    while( len )
    {
        len -= 1;
        buffer[len] = ' ';
    }
    return buffer;
}


char* i16ToStr( int16_t i, char *buffer, uint8_t len )
{
	len -= 1;
	buffer[len] = '\0';
	while( len && i )
	{
		len -= 1;
		buffer[len] = iToC( i % 10 );
		i /= 10;
	}
	while( len )
	{
		len -= 1;
		buffer[len] = ' ';
	}
	return buffer;
}