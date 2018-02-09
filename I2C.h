/*
 * I2C.h
 *
 *  Created on: Feb 7, 2018
 *      Author: lei-n
 */

#ifndef I2C_H_
#define I2C_H_

//Gravity constant
#define GRAVITY 9.81
//Value used for scaling the accelerometer values to gravity
#define ACCELEROMETER_Y (0.00244/4)
//Value to detect when the Kinetis is in free fall
#define ACCELEROMETER_TRESHOLD 10

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 \brief	 Start the necessary peripherals to use the I2C and read the
 accelerometer.
 \return TRUE if there was no problem
 */
int init_i2c ();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 \brief	 This function reads the status of the accelerometer, and also
 manages the status of the LED sequence
 \return TRUE if there was no problem
 */
int i2c_trnsfer ();

#endif /* I2C_H_ */
