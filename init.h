/*
 * init.h
 *
 *  Created on: Feb 7, 2018
 *      Author: lei-n
 */

#ifndef INIT_H_
#define INIT_H_

//the system clock of the Kinetis
#define SYSTEM_CLOCK CLOCK_GetBusClkFreq()
//period for the pit to get 1 second
#define PERIOD 2.00
//pit number to count
#define LDVAL_trigger  (SYSTEM_CLOCK * PERIOD)

//for interruptions
#define PORTC_IRQ_MASK 6
#define PORTA_IRQ_MASK 4
//PINS constants
#define BLUE_LED_PIN 21
#define RED_LED_PIN 22
#define GREEN_LED_PIN 26
#define SW2_PIN 6
#define SW3_PIN 4

int initSystem();

#endif /* INIT_H_ */
