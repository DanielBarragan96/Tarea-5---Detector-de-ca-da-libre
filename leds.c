#include "leds.h"
#include "fsl_gpio.h"
#include "MK64F12.h"
#include "fsl_pit.h"

//indicates if sequence is stopped
static volatile Led g_leds_status = LED_OFF;
//indicates if sequence is stopped
static volatile Status g_leds_sequence = STOP;
//flag used to stop the sequence after the PiIT finish counting
static volatile int g_stop_sequence = 0;

BooleanType startLed ()
{
    g_stop_sequence = 0; //reset start flag
    if (!g_leds_sequence)
    { //if sequence not started start it
        ledOn (); //turn LED on
        g_leds_sequence = RUN; //change the sequence status
        g_leds_status = LED_ON; //change the LED variable status
        startPit (); //start counting
    }
    return TRUE;
}

BooleanType stopLed ()
{
    g_stop_sequence = 1; //turn on stop flag
    return TRUE;
}

BooleanType ledOff ()
{
    g_leds_status = LED_OFF; //change leds status
    GPIO_PinWrite (GPIOB, 22, LED_OFF); //change the LED variable status
    return TRUE; //there was no error
}

BooleanType ledOn ()
{
    g_leds_status = LED_ON; //change leds status
    GPIO_PinWrite (GPIOB, RED_LED_PIN, LED_ON); //tuern led on
    return TRUE;
}

BooleanType startPit ()
{
    g_leds_sequence = RUN; //change sequence to running
    PIT_SetTimerPeriod (PIT, kPIT_Chnl_0, LDVAL_trigger); //assign cycles
    PIT_ClearStatusFlags (PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK); //clear flag
    PIT_StartTimer (PIT, kPIT_Chnl_0); //start counting
    return TRUE;
}

BooleanType stopPit ()
{
    g_leds_status = LED_OFF; //change the LED variable status
    g_leds_sequence = STOP; //change LED status
    ledOff (); //turn LED off
    PIT_StopTimer (PIT, kPIT_Chnl_0); //g_stop_sequence the pit
    return TRUE; //there was no error
}

BooleanType changeLED ()
{
    PIT_ClearStatusFlags (PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK); //clear flag
    if (g_stop_sequence)
    { //if sequence has to stop
        g_stop_sequence = STOP; //stop sequence
        stopPit (); //stop couting
        return FALSE; //
    }
    //Function to toggle the status of the LED
    if (!g_leds_status)
        ledOff ();
    else
        ledOn ();

    startPit (); //start counting
    return TRUE; //there was no mistake
}
