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

void PIT0_IRQHandler (void)
{ //handle the pit interrupt, change led color
    changeLED ();
}

int main (void)
{
    init_i2c (); //initialize I2C
    initSystem (); //initialize peripherals like PIT and LEDs

    while (1)
    {
        i2c_trnsfer (); //manage accelerometer
    }

}
