#ifndef TRAPEZOID_PROFILE_HPP
#define TRAPEZOID_PROFILE_HPP

#include <vector>
#include <pair>

class TrapezoidProfile {
	
	public:
		//construct generator and set required values
		TrapezoidProfile(double pMaxVel, double pAccel, double pInc): inc(pInc), maxVel(pMaxVel), accel(pAccel) {}
		
		//generate profile
		std::vector<std::pair<double, double>> generate(double distance);

	private:
		double inc; //increment for time
		double maxVel;
		double accel;
}

#endif
