/*
 * free_fall.c
 *
 *  Created on: Feb 8, 2018
 *      Author: Sergio
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"
#include "I2C.h"
#include "leds.h"

#define segundo 5250000
bool flag = true;

/*!
	 \brief	 This is the interrupt services routing (ISR) of
	 the PIT0
	 Loop for both directions for LED lighting
	 \param[in]  void.
	 \return void
 */
void PIT0_IRQHandler()
{
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	if (true == flag)
		rojo();
	else
		azul();

	flag = !flag;
}


void init(){

	i2cinit();
	ledsinit();
	i2c_ReleaseBus();
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);

	pit_config_t pit_config = {	true };
	PIT_Init(PIT, &pit_config);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, segundo);
	PIT_StartTimer(PIT, kPIT_Chnl_0);
}

void caidalibre(){
	 if(getA()>35000 && getA()<-35000)
	     EnableIRQ(PIT0_IRQn);
	 else
		 DisableIRQ(PIT0_IRQn);
}

void caida();
