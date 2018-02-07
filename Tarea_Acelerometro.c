
#include <stdio.h>
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
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	initI2C();
	initLED();

    while(1) {
       if(getI2C()>-17000 && getI2C()<35000)
    	   verde();
       else
    	   rojo();

    }
    return 0 ;
}
