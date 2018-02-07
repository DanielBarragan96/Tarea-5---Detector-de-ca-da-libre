/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Tarea4-Timer.c
 * @brief   Show a sequence of colors in the leds.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"
#include "leds.h"
#include "stdbool.h"

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


void PIT0_IRQHandler(void)
{//handle the pit interrupt, change led color
	updateLeds();
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, LDVAL_trigger);//cycles
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
	PIT_StartTimer(PIT, kPIT_Chnl_0);
}

void PORTC_IRQHandler()
{//when switch 2 is pressed
	PORT_ClearPinsInterruptFlags (PORTC, 1<<PORTC_IRQ_MASK);//clear irq
	ToogleLedStatus();//change led to stop/run
}

void PORTA_IRQHandler()
{//when switch 2 is pressed
	PORT_ClearPinsInterruptFlags (PORTA, 1<<PORTA_IRQ_MASK);//clear irq
	toogleReverse();//change led reverse
}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */

	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_EnableClock(kCLOCK_Pit0);

    // Input pin PORT configuration P-833 SDK
    const port_pin_config_t config =
			{
				kPORT_PullDisable,
				kPORT_FastSlewRate,
				kPORT_PassiveFilterDisable,
				kPORT_OpenDrainDisable,
				kPORT_LowDriveStrength,
				kPORT_MuxAsGpio,
				kPORT_UnlockRegister,
			};
	const port_pin_config_t config_switch =
			{
				kPORT_PullDisable,
				kPORT_FastSlewRate,
				kPORT_PassiveFilterDisable,
				kPORT_OpenDrainDisable,
				kPORT_LowDriveStrength,
				kPORT_MuxAsGpio,
				kPORT_UnlockRegister,
			  };

	// Sets the configuration
	//configure LEDs
    PORT_SetPinConfig(PORTB, BLUE_LED_PIN, &config);//BLUE
    PORT_SetPinConfig(PORTB, RED_LED_PIN, &config);//RED
    PORT_SetPinConfig(PORTE, GREEN_LED_PIN, &config);//GREEN
    //configure Switches
    PORT_SetPinConfig(PORTA, SW3_PIN, &config_switch);//SW3
    PORT_SetPinConfig(PORTC, SW2_PIN, &config_switch);//SW2

    //Output pin configuration
    const gpio_pin_config_t led_config =
		{
			kGPIO_DigitalOutput,//configurar como output
			1,//valor default
		};
    const gpio_pin_config_t switch_config =
		  {
			kGPIO_DigitalInput,//configurar como output
			1,//valor default
		  };

    // Sets the configuration
    GPIO_PinInit(GPIOB, BLUE_LED_PIN, &led_config);
    GPIO_PinInit(GPIOB, RED_LED_PIN, &led_config);
    GPIO_PinInit(GPIOE, GREEN_LED_PIN, &led_config);
    GPIO_PinInit(GPIOA, SW3_PIN, &switch_config);
    GPIO_PinInit(GPIOC, SW2_PIN, &switch_config);

    //PIT enable debug
    pit_config_t pit_config;
    PIT_GetDefaultConfig(&pit_config);
    //PIT configuration
    PIT_Init(PIT, &pit_config);
    ///cycles
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, (uint32_t) LDVAL_trigger);

    //enable switches interrupt
    PORT_SetPinInterruptConfig(PORTA, SW3_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(PORTC, SW2_PIN, kPORT_InterruptFallingEdge);

    //enable interruptions
    NVIC_EnableIRQ(PORTA_IRQn);
    NVIC_EnableIRQ(PORTC_IRQn);
    EnableIRQ(PIT0_IRQn);
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
    PIT_StartTimer(PIT, kPIT_Chnl_0);

    //turn red led on
    GPIO_PinWrite(GPIOB, RED_LED_PIN, LED_ON);

    /* Enter an infinite loop, just incrementing a counter. */
    while(1)
    {

    }
    return 0 ;
}
