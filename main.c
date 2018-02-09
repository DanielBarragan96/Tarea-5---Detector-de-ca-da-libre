#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_port.h"
#include "MK64F12.h"
#include "fsl_i2c.h"
#include "leds.h"
#include "init.h"
#include "I2C.h"

void PIT0_IRQHandler(void)
{//handle the pit interrupt, change led color
	BooleanType keepOn = changeLED();
	if(keepOn)
		startPit();
}

int main(void)
{
	init_i2c();
	initSystem();

	while(1)
	{
		i2c_trnsfer();
	}

}
