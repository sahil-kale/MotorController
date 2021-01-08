#ifndef TRAPEZOID_PROFILE_HPP
#define TRAPEZOID_PROFILE_HPP

#include <vector>
#include <pair>

class TrapezoidProfile {
	
	public:
		/*
		 * params:
		 * pMaxVel: max velocity of the profile
		 * pAccel: acceleration of the profile
		 * pInc: increment of the profile
		 */
		TrapezoidProfile(double pMaxVel, double pAccel, double pInc): inc(pInc), maxVel(pMaxVel), accel(pAccel) {}
		
		//generate profile
		
		/* params:
		 * dist: displacement in encoder units 
		 *
		 * returns: a vector of pairs, 
		 * 1st element in each pair is time in ms
		 * 2nd element is the target velocity in units/ms
		 */
		std::vector<std::pair<double, double>> generate(double distance);

	private:
		double inc; //increment for time
		double maxVel;
		double accel;
}

#endif
