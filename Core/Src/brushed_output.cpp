#include "brushed_output.hpp"
#include "main.h"
#include "PWMPinout.hpp"

static const int MAX_PWM = 4;

extern TIM_HandleTypeDef htim4;

static const PWMPinOut PWM_PINOUT[MAX_PWM] =
{
		{&htim4, TIM_CHANNEL_1},
		{&htim4, TIM_CHANNEL_2},
		{&htim4, TIM_CHANNEL_3},
		{&htim4, TIM_CHANNEL_4},
};


BrushedMotorDriver::BrushedMotorDriver()
{
	for(int channel = 0; channel < MAX_PWM; channel++)
	{
		PWMPinOut currentChannel = PWM_PINOUT[channel];
		HAL_TIM_PWM_Start(currentChannel.timer, currentChannel.timer_channel);
	}
}

BrushedMotorDriver* BrushedMotorDriver::s_instance = nullptr; //assign NullPTR to singleton instance

BrushedMotorDriver* BrushedMotorDriver::GetInstance() //Singleton design
{
	if(!s_instance)
	{
		s_instance = new BrushedMotorDriver();
	}

	return s_instance;
}

bool BrushedMotorDriver::set(double speed)
{
	static const double MAX_SPEED = 1.0;
	bool wasSuccessful = true; //Potential improvement point: add error handling
	if(speed >  MAX_SPEED || speed < -MAX_SPEED)
	{
		speed = 0;
		wasSuccessful = false;
	}

	if(speed > 0)
	{
		setForwardPWMPeripherals(speed);
		setBackwardPWMPeripherals(0);
	}
	else if(speed < 0)
	{
		setForwardPWMPeripherals(0);
		setBackwardPWMPeripherals(-speed);
	}
	else
	{
		setForwardPWMPeripherals(0);
		setBackwardPWMPeripherals(0);
	}

	return wasSuccessful;

}


void BrushedMotorDriver::setForwardPWMPeripherals(double dutyPercent)
{
	/**H1 and H4 are coupled together to form a classic H bridge**/

	PWMPinOut out_H1 = PWM_PINOUT[0];
	uint32_t periodTicksH1 = out_H1.timer->Init.Period;
	__HAL_TIM_SET_COMPARE(out_H1.timer, out_H1.timer_channel, periodTicksH1*dutyPercent); //sets the CCR register proportional to ticks

	PWMPinOut out_H4 = PWM_PINOUT[3];
	uint32_t periodTicksH4 = out_H4.timer->Init.Period;
	__HAL_TIM_SET_COMPARE(out_H4.timer, out_H4.timer_channel, periodTicksH4*dutyPercent);
}

void BrushedMotorDriver::setBackwardPWMPeripherals(double dutyPercent)
{
	/**H2 and H3 are coupled together to form a classic H bridge**/

	PWMPinOut out_H2 = PWM_PINOUT[1];
	uint32_t periodTicksH2 = out_H2.timer->Init.Period;
	__HAL_TIM_SET_COMPARE(out_H2.timer, out_H2.timer_channel, periodTicksH2*dutyPercent); //sets the CCR register proportional to ticks

	PWMPinOut out_H3 = PWM_PINOUT[2];
	uint32_t periodTicksH3 = out_H3.timer->Init.Period;
	__HAL_TIM_SET_COMPARE(out_H3.timer, out_H3.timer_channel, periodTicksH3*dutyPercent);
}
