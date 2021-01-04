#include "tim.h"
#include "main.h"
#include <stdbool.h>
#include "PWMinput.hpp"


//Prescalar Math: (8MHz/2MHz) - 1 = 3 <- PRESCALAR
//65535/2000000 = 0.0327675s | 0.02/0.0327675 = 40000 ARR countup 


static volatile int IC_Val1 = 0;
static volatile int IC_Val2 = 0;
//static volatile int Frequency = 0;
static volatile int DutyCycle = 0;
static volatile bool isRisingCaptured = false;

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) //rising edge IN
    {

        if(!isRisingCaptured)
        {
            __HAL_TIM_SET_COUNTER(htim, 0);
            //IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            isRisingCaptured = true;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
        }
        else
        {
            IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            //__HAL_TIM_SET_COUNTER(htim, 0);

            if(IC_Val2 > IC_Val1)
            {
                DutyCycle = IC_Val2-IC_Val1;
            }

            isRisingCaptured = false;
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);

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


void startPWMInput()
{
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
}

int getDutyCycleUs()
{
    return DutyCycle; //The prescalar is set so that each tick is 1us. Returning the duty cycle will therefore return pulse width
}
