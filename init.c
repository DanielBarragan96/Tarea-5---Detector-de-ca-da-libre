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
#include "leds.h"

int initSystem()
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

	// Sets the configuration
	//configure LEDs
    PORT_SetPinConfig(PORTB, RED_LED_PIN, &config);//RED

    //Output pin configuration
    const gpio_pin_config_t led_config =
		{
			kGPIO_DigitalOutput,//configurar como output
			1,//valor default
		};

    // Sets the configuration
    GPIO_PinInit(GPIOB, RED_LED_PIN, &led_config);

    //PIT enable debug
    pit_config_t pit_config;
    PIT_GetDefaultConfig(&pit_config);
    //PIT configuration
    PIT_Init(PIT, &pit_config);
    ///cycles
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, (uint32_t) LDVAL_trigger);

    //enable interruptions
    NVIC_EnableIRQ(PORTA_IRQn);
    NVIC_EnableIRQ(PORTC_IRQn);
    EnableIRQ(PIT0_IRQn);
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);

    //turn red led on
    GPIO_PinWrite(GPIOB, RED_LED_PIN, LED_OFF);
    return 0;
}
