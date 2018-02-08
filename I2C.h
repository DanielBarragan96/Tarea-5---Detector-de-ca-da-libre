/*
 * I2C.h
 *
 *  Created on: Feb 7, 2018
 *      Author: Sergio
 */
#include "fsl_i2c.h"
#ifndef I2C_H_
#define I2C_H_


void i2c_ReleaseBus();
void i2cinit();
uint16_t getA();

#endif /* I2C_H_ */
