#ifndef ENCODER_DRIVER_HPP
#define ENCODER_DRIVER_HPP

class EncoderDriver {

		public:

			EncoderDriver(const EncodeDriver*) = delete; 
			static EncoderDriver* GetInstance();

			int32_t getPosition();
			void setPosition(int32_t pos);	
			double getVelocity();

			void intChannelA(bool rising);
			void intChannelB(bool rising);

		private:
			
			EncoderDriver(); //private constructor
			static EncoderDriver* instance;
			
			uint32_t position;
			double velocity;

			uint32_t lastInterruptTime; //used to find the time between interrupts
}

