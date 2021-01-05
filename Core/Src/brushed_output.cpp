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
	bool wasSuccessful = true; //Potential improvement point: add error handling
	for(int channel = 0; channel < MAX_PWM; channel++)
	{
		PWMPinOut currentChannel = PWM_PINOUT[channel];
		uint32_t periodTicks = currentChannel.timer->Init.Period;
		__HAL_TIM_SET_COMPARE(currentChannel.timer, currentChannel.timer_channel, periodTicks*speed);
	}
	return wasSuccessful;

}
