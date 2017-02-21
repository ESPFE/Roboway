/*!
	\file		complementaryFilter.h
	\brief		This is the header file for complementary filter

              A complementary filter combines the good characteristics of an accelerometer and a gyroscope.\n
              On the other hand it filters out bad properties like drift or high sensitivity.

              A <a href="http://www.cbcity.de/das-kalman-filter-einfach-erklaert-teil-1" target="_blank">Kalman Filter</a> is another solution for this problem.\n
              The result is a little bit better, but it is much more complex.

              Because of the limitations of ressources of the used controller and the very time critical application i recommend to use a complementary filter.\n
              The sampling rate is about five times higher with a Kalman Filter.

	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		18.03.2014
	\version	1.3.1
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.
*/


#ifndef COMPLEMENTARYFILTER_H_
#define COMPLEMENTARYFILTER_H_


#include <stdint.h>


/*!
    \def        CF_STD_GYRO_GAIN
    \brief      Standard gain for the high pass filter (gyroscope)

    \def        CF_STD_ACC_GAIN
    \brief      Standart gain for the low pass filter (accelerometer)
*/
#define CF_STD_GYRO_GAIN    0.98
#define CF_STD_ACC_GAIN     0.02


/*!
    \struct     compFilterData
    \brief      Data structure for complementary filter
    \see        void compFilterInit( double gyroGain, double accGain, double dt, compFilterData *fd )
    \see        double compFilterGetAngle( double gyroData, double accData, compFilterData *fd )

    \var        compFilterData::gG
    \brief      Gain for high pass filter of gyroscope
    \warning    Sum of compFilterData::gG and compFilterData::aG must be 1

    \var        compFilterData::aG
    \brief      Gain for low pass filter of accelerometer
    \warning    Sum of compFilterData::gG and compFilterData::aG must be 1

    \var        compFilterData::aO
    \brief      Old angle

    \var        compFilterData::dt
    \brief      Sampling rate in seconds
    \warning    This must be as precise as possible
*/
typedef struct
{
    double gG;
    double aG;
    double aO;
    double dt;
} compFilterData;


/*!
    \fn         void compFilterInit( double gyroGain, double accGain, double dt, compFilterData *fd )
    \brief      Initial setup of an complementary filter
    \param      gyroGain
    \brief      Gain for high pass filter of gyroscope
    \param      accGain
    \brief      Gain for low pass filter of accelerometer
    \param      dt
    \brief      Sampling rate in seconds
    \warning    dt should be as precise as possible
    \param      fd
    \brief      Pointer to a complementary filter working structure
    \warning    gyroGain + accGain must be 1
    \see        compFilterData
    \return     void
*/
void compFilterInit( double gyroGain, double accGain, double dt, compFilterData *fd );


/*!
    \fn         double compFilterGetAngle( double gyroData, double accData, compFilterData *fd )
    \brief      Get new filtered angle

                It depends on of the angular rate of the gyroscope, the old angle and the angle measured by the accelerometer\n
                The angular rate of the gyroscope is filtered with a high pass filer ( \ref CF_STD_GYRO_GAIN ).\n
                The angle measured by the acceleromter is filtered with a low pass filter ( \ref CF_STD_ACC_GAIN )
    \param      gyroData
    \brief      Measured angular rate of the gyroscope in degrees
    \param      accData
    \brief      Meassured angle of the accelerometer in degrees
    \param      fd
    \brief      Pointer to the complementary filter working structure
    \see        compFilterData
    \return     double
    \brief      Filtered angle
*/
//double compFilterGetAngle( double angleOld, double gyroData, double accData, double dt );
double compFilterGetAngle( double gyroData, double accData, compFilterData *fd );



#endif /* COMPLEMENTARYFILTER_H_ */
