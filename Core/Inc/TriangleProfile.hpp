#ifndef TRIANGLEPROFILE_HPP
#define TRIANGLEPROFILE_HPP

#include <vector>		

class TriangleProfile {
	private:
		double inc;
	public:
		TriangleProfile(double pInc) : inc(pInc) {};

		std::vector<std::pair<double,double>> generate(double dt, double dist);
}
#endif //TRIANGLEPROFILE_HPP
