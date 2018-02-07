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
 * @file    PrenderLED.c
 * @brief   Application entry point.
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

   void initLED(){
	   /* Init board hardware. */
	   	BOARD_InitBootPins();
	   	BOARD_InitBootClocks();
	   	BOARD_InitBootPeripherals();
	   	/* Init FSL debug console. */
	   	BOARD_InitDebugConsole();

	   	CLOCK_EnableClock(kCLOCK_PortB);
	   	CLOCK_EnableClock(kCLOCK_PortE);

	   	port_pin_config_t config_led = { kPORT_PullDisable, kPORT_SlowSlewRate,
	   			kPORT_PassiveFilterDisable, kPORT_OpenDrainDisable,
	   			kPORT_LowDriveStrength, kPORT_MuxAsGpio, kPORT_UnlockRegister, };

	   	PORT_SetPinConfig(PORTB, 21, &config_led);  //Blue
	   	PORT_SetPinConfig(PORTB, 22, &config_led);	//Red
	   	PORT_SetPinConfig(PORTE, 26, &config_led);	//Green

	   	gpio_pin_config_t led_config_gpio = { kGPIO_DigitalOutput, 1 };

	   	GPIO_PinInit(GPIOB, 21, &led_config_gpio);
	   	GPIO_PinInit(GPIOB, 22, &led_config_gpio);
	   	GPIO_PinInit(GPIOE, 26, &led_config_gpio);

	   	void verde()
	   		{
	   		GPIO_WritePinOutput(GPIOE, 26, 0);
	   		GPIO_WritePinOutput(GPIOB, 22, 1);
	   		GPIO_WritePinOutput(GPIOB, 21, 1);
	   		}

	   		/*!
	   			 	 \brief	 This is the function for red LED color
	   			 	 \param[in]  void.
	   			 	 \return void
	   			 */
	   	void rojo()
	   		{
	   		GPIO_WritePinOutput(GPIOE, 26, 1);
	   		GPIO_WritePinOutput(GPIOB, 22, 0);
	   		GPIO_WritePinOutput(GPIOB, 21, 1);
	   		}

	   		/*!
	   			 	 \brief	 This is the function for blue LED color
	   			 	 \param[in]  void.
	   			 	 \return void
	   			 */
	   	void azul()
	   		{
	   		GPIO_WritePinOutput(GPIOE, 26, 1);
	   		GPIO_WritePinOutput(GPIOB, 22, 1);
	   		GPIO_WritePinOutput(GPIOB, 21, 0);
	   		}
}
