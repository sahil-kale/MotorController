#ifndef ENCODER_DRIVER_HPP
#define ENCODER_DRIVER_HPP

class EncoderDriver {

		public:
			
			//singleton code
			EncoderDriver(const EncodeDriver*) = delete; 
			static EncoderDriver* GetInstance();
			
			//simple setter and getter methonds
			int32_t getPosition();
			void setPosition(int32_t pos);	
			double getVelocity();

			//two functions to be called in the interrupt handler
			void intChannelA(bool rising);
			void intChannelB(bool rising);

		private:
			
			EncoderDriver(); //private constructor
			static EncoderDriver* instance;
		
				
			int32_t position;
			double velocity;

			uint32_t lastInterruptTime; //used to find the time between interrupts
};

#endif // ENCODER_DRIVER_HPP

