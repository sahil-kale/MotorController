#include "brakecoastmanager.hpp"
#include "GPIO.h"
#include "main.h"

static bool brakeModeEnabled;

BrakeCoastManager::BrakeCoastManager()
{
	brakeModeEnabled = false; //default initalization
}

BrakeCoastManager* BrakeCoastManager::s_instance = nullptr;

BrakeCoastManager* BrakeCoastManager::GetInstance()
{
	if(!s_instance)
	{
		s_instance = new BrakeCoastManager();
	}

	return s_instance;
}


void BrakeCoastManager::enableBrakeMode()
{
	brakeModeEnabled = true;
	setMotorTerminalShort();

}

void BrakeCoastManager::disableBrakeMode()
{
	brakeModeEnabled = false;
	setMotorTerminalShort();
}

bool BrakeCoastManager::getBrakeEnabled() const
{
	return brakeModeEnabled;
}

void setMotorTerminalShort()
{
	if(brakeModeEnabled)
	{
		HAL_GPIO_WritePin(BackEMF_GPIO_Port, BackEMF_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(BackEMF_GPIO_Port, BackEMF_Pin, GPIO_PIN_RESET);
	}
}

