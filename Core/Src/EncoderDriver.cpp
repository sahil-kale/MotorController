import "EncoderDriver.hpp"


//encoder driver constructor
EncoderDriver::EncoderDriver() {
	velocity = 0;
	position = 0;
	lastInterruptTime = 0;
}

EncoderDriver* EncoderDriver::instance = nullptr;

//gets the single instance, creates one if it doesnt exist 
EncoderDriver* EncoderDriver::getInstance() {
	if(!instance) {
		instance = new EncoderDriver();
	}
	
	return instance;
}

//getters and setters
int32_t EncoderDriver::getPosition() {
	return position;
}

void EncoderDriver::setPosition(int32_t pos) {
	position = pos;
}

double EncoderDriver::getVelocity() {
	return velocity;
}


//two functions to be called by the gpio interrupt
void EncoderDriver::intChannelA(bool rising) {
	//get the value of each channel
	bool chanA = rising;
	bool chanB = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);
	
	//compare channels to determine direction of system	
	bool forward = chanA != chanB;

	uint32_t time = HAL_GetTick();	
	//get the time since the last interrrupt
	uint32_t dt  = time - lastInterruptTime;	
	

	//modify position and velocity
	if(forward) {
		position += 1;	
		velocity = 1/dt;
	} else {
		position -= 1;	
		velocity = -1/dt;
	}

	lastInterruptTime = time; 
}

void EncoderDriver::intChannelB(bool rising) {
	//get the value of each channel
	bool chanA = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
	bool chanB = rising;

	//compare channels to determine direction of system	
	bool forward = chanA == chanB;	
	uint32_t time = HAL_GetTick();
	//get the time since the last interrrupt
	uint32_t dt  = time - lastInterruptTime;	
	//modify position and velocity
	if(forward) {
		position += 1;	
		velocity = 1/dt;
	} else {
		position -= 1;	
		velocity = -1/dt;
	}
	lastInterruptTime = time; 
}

//callback to be called on gpio interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	
	if (GPIO_Pin == 0) { //enc 1 pin - channel a
		EncoderDriver.getInstance().intChannelA(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0));
	} else if(*GPIO_Pin == 1) { //enc 2 pin - channel b
		EncoderDriver.getInstance().intChannelB(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1));
	}
}
