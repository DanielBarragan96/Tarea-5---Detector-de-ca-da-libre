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

//for interruptions
#define PORTC_IRQ_MASK 6
#define PORTA_IRQ_MASK 4
//PINS constants
#define BLUE_LED_PIN 21
#define RED_LED_PIN 22
#define GREEN_LED_PIN 26
#define SW2_PIN 6
#define SW3_PIN 4

void initSystem()
{
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
}