#include "TriangleProfile.hpp"

std::vector<std::pair<double,double>> TriangleProfile::generate(double dt, double dist) {
	
	//calculating the required slope based on the 
	//given time and distance
	double vAverage  = distance/dt;
	double vMax = 2 * vAverage;

	double run = dt/2;
	double slope = vMax/run;

	std::vector<std::pair<double, double>> vels;

	double x = 0.0;

	//creates the first part of the triangle
	//using vel = accel * times
	//where accel is the slope that was previously calculated
	while(x <= run) {
		vels.push_back(std::make_pair(x,x*slope));
		x += this->inc;
	}

	//creates the second part of the triangle
	//using a negative acceleration
	while(x <= dt + this->inc) {
		vels.push_back(std::make_pair(x,x*-slope));
		x += this->inc;	
	}

	return vels;
}
