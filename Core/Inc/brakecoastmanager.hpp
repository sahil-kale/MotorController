#ifndef BRAKECOASTMANAGER_HPP
#define BRAKECOASTMANAGER_HPP

class BrakeCoastManager
{
	public:
		BrakeCoastManager(const BrakeCoastManager*) = delete;
		static BrakeCoastManager* GetInstance();
		void enableBrakeMode();
		void disableBrakeMode();
		bool getBrakeEnabled() const;

	private:
		BrakeCoastManager();
		static BrakeCoastManager* s_instance;
		void setMotorTerminalShort();
};




#endif
