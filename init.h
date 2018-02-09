/*
 * init.h
 *
 *  Created on: Feb 7, 2018
 *      Author: lei-n
 */

#ifndef INIT_H_
#define INIT_H_

//for interruptions
#define PORTC_IRQ_MASK 6
#define PORTA_IRQ_MASK 4
//PINS constants
#define RED_LED_PIN 22

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 \brief  This function initialices all the peripherals, includig the LEDs and interruptions.
 \return TRUE if there was no problem
 */
int initSystem ();

#endif /* INIT_H_ */
