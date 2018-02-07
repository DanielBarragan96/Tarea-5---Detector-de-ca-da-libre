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
 	 \brief	 Function to change the status of the LEDs from start to stop
 	 \return TRUE if there was no problem
 */
BooleanType ToogleLedStatus();

BooleanType changeLED();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 This function returns the status of the LEDs
 	 \return TRUE if there was no problem
 */
Status getLedStatus();
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief Initialize variables for this module
 	 \return TRUE if there was no problem
 */
BooleanType InitLedsPit(PIT_Type* base_pit);
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
/*!
 	 \brief	 This function turns the LEDs in the Kinetis off.
 	 \return TRUE if there was no problem
 */
BooleanType turnLedsOff();

#endif //LEDS_H_
