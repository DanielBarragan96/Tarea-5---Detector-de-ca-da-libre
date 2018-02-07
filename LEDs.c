#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_port.h"
#include "MK64F12.h"
#include "fsl_i2c.h"
#include "I2C.h"
#include "LEDs.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

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
}
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

