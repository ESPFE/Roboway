#include "kalman.h"

void setupKalman( struct kalmanData *kData )
{
	/* We will set the variables like so, these can also be tuned by the user */
	kData->qAngle = 0.001;
	kData->qBias = 0.003;
	kData->rMeasure = 0.03;

	kData->angle = 0; // Reset the angle
	kData->bias = 0; // Reset bias

	kData->p[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
	kData->p[0][1] = 0;
	kData->p[1][0] = 0;
	kData->p[1][1] = 0;
}

// The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
double kalmanGetAngle( double newAngle, double newRate, double dt, struct kalmanData *kData )
{
	// KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
	// Modified by Kristian Lauszus
	// See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
	
	// Discrete Kalman filter time update equations - Time Update ("Predict")
	// Update xhat - Project the state ahead
	/* Step 1 */
	kData->rate = newRate - kData->bias;
	kData->angle += dt * kData->rate;
	
	// Update estimation error covariance - Project the error covariance ahead
	/* Step 2 */
	kData->p[0][0] += dt * ( dt * kData->p[1][1] - kData->p[0][1] - kData->p[1][0] + kData->qAngle );
	kData->p[0][1] -= dt * kData->p[1][1];
	kData->p[1][0] -= dt * kData->p[1][1];
	kData->p[1][1] += kData->qBias * dt;
	
	// Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
	// Calculate Kalman gain - Compute the Kalman gain
	/* Step 4 */
	kData->s = kData->p[0][0] + kData->rMeasure;
	
	/* Step 5 */
	kData->k[0] = kData->p[0][0] / kData->s;
	kData->k[1] = kData->p[1][0] / kData->s;
	
	// Calculate angle and bias - Update estimate with measurement zk (newAngle)
	/* Step 3 */
	kData->y = newAngle - kData->angle;
	
	/* Step 6 */
	kData->angle += kData->k[0] * kData->y;
	kData->bias += kData->k[1] * kData->y;
	
	// Calculate estimation error covariance - Update the error covariance
	/* Step 7 */
	kData->p[0][0] -= kData->k[0] * kData->p[0][0];
	kData->p[0][1] -= kData->k[0] * kData->p[0][1];
	kData->p[1][0] -= kData->k[1] * kData->p[0][0];
	kData->p[1][1] -= kData->k[1] * kData->p[0][1];

	return kData->angle;
}