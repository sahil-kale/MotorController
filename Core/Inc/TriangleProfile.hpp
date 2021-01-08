#ifndef TRIANGLEPROFILE_HPP
#define TRIANGLEPROFILE_HPP

#include <vector>		

class TriangleProfile {
	private:
		double inc;
	public:
		//constructor
		TriangleProfile(double pInc) : inc(pInc) {};
		
		/* params:
		 * dt: milliseconds required to reach the target
		 * dist: displacement in encoder units 
		 *
		 * returns: a vector of pairs, 
		 * 1st element in each pair is time in ms
		 * 2nd element is the target velocity in units/ms
		 */
		std::vector<std::pair<double,double>> generate(double dt, double dist);
}
#endif //TRIANGLEPROFILE_HPP
