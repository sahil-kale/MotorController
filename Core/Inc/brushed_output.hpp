#ifndef BRUSHED_OUTPUT_HPP
#define BRUSHED_OUTPUT_HPP

class BrushedMotorDriver //Singleton behaviour used to prevent 2 files from using the set functions
{
	public:
		BrushedMotorDriver(const BrushedMotorDriver*) = delete; //Ensures that you don't accidently make a copy
		static BrushedMotorDriver* GetInstance();

		/* @param speed -1.0 to 1.0*/
		bool set(double speed);

	private:
		BrushedMotorDriver(); //Private constructor
		static BrushedMotorDriver* s_instance;
};

#endif
