/*
 * complementaryFilter.h
 *
 * Created: 04.03.2014 21:15:47
 *  Author: suennemann
 */ 


#ifndef COMPLEMENTARYFILTER_H_
#define COMPLEMENTARYFILTER_H_


#include <stdint.h>

int16_t complementaryFilterAngle( int16_t angle, int16_t gyro, int16_t dt );


#endif /* COMPLEMENTARYFILTER_H_ */