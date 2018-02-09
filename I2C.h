/*
 * I2C.h
 *
 *  Created on: Feb 7, 2018
 *      Author: lei-n
 */

#ifndef I2C_H_
#define I2C_H_

#define GRAVITY 9.81
#define ACCELEROMETER_Y (0.00244/4)
#define ACCELEROMETER_TRESHOLD 10

int init_i2c();

int i2c_trnsfer();


#endif /* I2C_H_ */
