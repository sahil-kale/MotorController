#include "led.hpp"
#include "PWMPinout.hpp"


static const int LED_CHANNELS = 3;

static const int RED_CHANNEL_IN_STRUCT = 0;
static const int BLUE_CHANNEL_IN_STRUCT = 1;
static const int GREEN_CHANNEL_IN_STRUCT = 2;

static const int MAX_COLOUR_VALUE = 255;

static const PWMPinOut LED_Pinout[LED_CHANNELS] =
{
		{&htim3, TIM_CHANNEL_1},
		{&htim3, TIM_CHANNEL_2},
		{&htim3, TIM_CHANNEL_3},
};

LED::LED()
{
	for(int channel = 0; channel < LED_CHANNELS; channel++)
		{
			PWMPinOut currentChannel = LED_Pinout[channel];
			HAL_TIM_PWM_Start(currentChannel.timer, currentChannel.timer_channel);
		}
}

void LED::setColour(char red, char green, char blue) //Chars are used to save memory since they're only 4 bits
{

	double redValue = int(red)/double(MAX_COLOUR_VALUE);
	double greenValue = int(green)/double(MAX_COLOUR_VALUE);
	double blueValue = int(blue)/double(MAX_COLOUR_VALUE);

	PWMPinOut redChannel = LED_Pinout[RED_CHANNEL_IN_STRUCT];
	PWMPinOut greenChannel = LED_Pinout[GREEN_CHANNEL_IN_STRUCT];
	PWMPinOut blueChannel = LED_Pinout[BLUE_CHANNEL_IN_STRUCT];

	uint32_t redTimerPeriod = redChannel.timer->Init.Period;
	uint32_t greenTimerPeriod = greenChannel.timer->Init.Period;
	uint32_t blueTimerPeriod = blueChannel.timer->Init.Period;

	__HAL_TIM_SET_COMPARE(redChannel.timer, redChannel.timer_channel, redTimerPeriod*redValue);
	__HAL_TIM_SET_COMPARE(greenChannel.timer, greenChannel.timer_channel, greenTimerPeriod*greenValue);
	__HAL_TIM_SET_COMPARE(blueChannel.timer, blueChannel.timer_channel, blueTimerPeriod*blueValue);

}
