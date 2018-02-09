/**
 * @brief this module is used to control and configurate the leds in the Kinetis
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "DataTypeDefinitions.h"
#include "stdbool.h"
#include "fsl_pit.h"


//the system clock of the Kinetis
#define SYSTEM_CLOCK CLOCK_GetBusClkFreq()
//period for the pit to get 1 second
#define PERIOD 1.00
//pit number to count
#define LDVAL_trigger  (SYSTEM_CLOCK * PERIOD)
//for interruptions
#define PORTC_IRQ_MASK 6
#define PORTA_IRQ_MASK 4
//PINS constants
#define RED_LED_PIN 22

/* This definition is used to indicate if the led is on or off */
typedef enum
{
	LED_ON = 0,
	LED_OFF = 1
}Led;
/* This definition is used to indicate whether the LEDs are changing or not */
typedef enum
{
	RUN = true,
	STOP = false
}Status;

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 Function to start the LED sequence if not started before.
 	 \return TRUE if there was no problem.
 */
BooleanType startLed();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 This function stop the LED sequence, and interrupts the PIT.
 	 \return TRUE if there was no problem
 */
BooleanType stopLed();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 Initialize PIT for the LED sequence
 	 \return TRUE if there was no problem
 */
BooleanType startPit();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 Stop the PIT, and by this stop the LED sequence. Also turn off
 	 the LED.
 	 \return TRUE if there was no problem
 */
BooleanType stopPit();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 Function to turn off the LED.
 	 \return TRUE if there was no problem
 */
BooleanType ledOff();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 Function to turn on the LED.
 	 \return TRUE if there was no problem
 */
BooleanType ledOn();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 Function called when the PIT interrupt flag is on. Manages the
 	 state of the LED sequence, also if the stop flag is on this function
 	 stops the PIT, stop the sequence and turn off the LED
 	 \return TRUE if there was no problem
 */
BooleanType changeLED();

#endif
