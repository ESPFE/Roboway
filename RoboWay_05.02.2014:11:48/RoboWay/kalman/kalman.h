/*
 * kalman.h
 *
 * Created: 02.03.2014 20:30:52
 *  Author: suennemann
 */ 


#ifndef KALMAN_H_
#define KALMAN_H_


 
/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */


struct kalmanData
{
	double qAngle;		// Process noise variance for the accelerometer
	double qBias;		// Process noise variance for the gyro bias
	double rMeasure;	// Measurement noise variance - this is actually the variance of the measurement noise
	
	double angle;		// The angle calculated by the Kalman filter - part of the 2x1 state vector
	double bias;		// The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
	double rate;		// Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate
	
	double p[2][2];		// Error covariance matrix - This is a 2x2 matrix
	double k[2];		// Kalman gain - This is a 2x1 vector
	double y;			// Angle difference
	double s;			// Estimate error
};

void setupKalman( struct kalmanData *kData );

// The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
double kalmanGetAngle( double newAngle, double newRate, double dt, struct kalmanData *kData );





#endif /* KALMAN_H_ */