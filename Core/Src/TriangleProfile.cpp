#include "TriangleProfile.hpp"

std::vector<std::pair<double,double>> TriangleProfile::generate(double dt, double dist) {
	double vAverage  = distance/dt;
	double vMax = 2 * vAverage;

	double run = dt/2;
	double slope = vMax/run;

	std::vector<std::pair<double, double>> vels;

	double x = 0.0;

	while(x <= run) {
		vels.push_back(std::make_pair(x,x*slope));
		x += this->inc;
	}

	while(x <= dt + this->inc) {
		vels.push_back(std::make_pair(x,x*-slope));
		x += this->inc;	
	}

	return vels;
}
