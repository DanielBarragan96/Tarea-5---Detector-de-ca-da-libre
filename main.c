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

//the system clock of the Kinetis
#define SYSTEM_CLOCK CLOCK_GetBusClkFreq()
//period for the pit to get 1 second
#define PERIOD 2.00
//pit number to count
#define LDVAL_trigger  (SYSTEM_CLOCK * PERIOD)

void PIT0_IRQHandler(void)
{//handle the pit interrupt, change led color
	changeLED();
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, LDVAL_trigger);//cycles
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
	PIT_StartTimer(PIT, kPIT_Chnl_0);
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
