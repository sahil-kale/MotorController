#include "tim.h"
#include "main.h"
#include <stdbool.h>
#include "PWMinput.hpp"

static const int PWM_MAX_DELAY_MS = 40;

static volatile int IC_Val1 = 0;
static volatile int IC_Val2 = 0;
//static volatile int Frequency = 0;
static volatile int DutyCycle = 0;
static volatile bool isRisingCaptured = false;
static volatile uint32_t timeOfInterruptms = 0;


void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) //tim3 ch1 is being used for input capture
    {

        if(!isRisingCaptured) // If the rising edge is not captured, reset the TIM counter and change the polarity
        {
        	timeOfInterruptms = HAL_GetTick(); //This stores the time at which the interrupt was called. This is used later in isOvertime()
            __HAL_TIM_SET_COUNTER(htim, 0);
            //IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            isRisingCaptured = true;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);  //Capture falling edge now
        }
        else //If the falling edge is now about to be captured, read the counter
        {
            IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            //__HAL_TIM_SET_COUNTER(htim, 0);

            if(IC_Val2 > IC_Val1)
            {
                DutyCycle = IC_Val2-IC_Val1; //Calculate Duty Cycle: Currently the TIM2 clock is at 1MHz, which is a period of 1us
            }

            isRisingCaptured = false;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING); //Capture rising edge now

        }
        


        /*
        IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

        if(IC_Val1 != 0) //If the value isn't 0, another interrupt has been called after measuring started. Measure Falling edge now
        {
            IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);

            DutyCycle = IC_Val2*100/IC_Val1;
        }
        else
        {
            DutyCycle = 0;
        }
        */
    }
}


void startPWMInput() //Starts the interrupt
{
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
}

int getDutyCycleUs()
{
    return DutyCycle; //The prescalar is set so that each tick is 1us. Returning the duty cycle will therefore return pulse width
}

void stopPWMOutput() //Stops the interrupt. Should be called by a transition state
{
	HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_2);
}

bool isOvertime() //This method will ensure that signals are above a certain frequency to operate (see datasheet for specs)
{
	return (HAL_GetTick() - timeOfInterruptms) > PWM_MAX_DELAY_MS;
}
