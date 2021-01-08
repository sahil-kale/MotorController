#include "TrapezoidProfile.hpp"

#include <pair>
#include <vector>

std::vector<std::pair<double, double>> TriangleProfile::generate(double distance) {

	//calculating the amount of time for each segment
	//assuming the given distance needs a trapezoid 
	double tb = distance / this->velocity - 1/this->accel;
	double ta = vel/accel;
	
	//declare velocity vector
	std::vector<std::pair<double, double>> vels;

	double curTime = 0.0;

	double accel = this->accel;
	double vel = this->velocity;	

	//modify the accel and vel if the distance is negative	
	if(distance < 0.0) {
		accel = -this->accel;
		vel = -this->velocity;
	}
	
	//check if a trapezoid works for this distance
	//or if a triangle is needed
	if(std::abs(ta * vel) > abs(distance)) {

		//calculate a new ta
		ta = std::sqrt(distance/accel);
		
		//first triangle section	
		while (curTime <= ta) {
			vels.push_back(std::make_pair(curTime,curTime*accel));
			curTime += this->inc;
		}

		//second triangle section
		while (curTime <= ta*2) {
			vels.push_back(std::make_pair(curTime, (curTime-2*ta)*-accel));
			curTime += this->inc;
		}
	} else {
		//first section of the trapezoid
		while (curTime < ta) {
			vels.push_back(std::make_pair(curTime, curTime*accel));
			curTime += this->inc;
		}
		
		//rectangular middle section
		while (curTime < ta+tb) {
			vels.push_back(std::make_pair(curTime, vel));
			curTime += this->inc;
		}

		//last triangle section 
		while (curTime < tb + 2*ta) {
			vels.push_back(std::make_pair(curTime, (curTime - 2*ta-tb)*-accel));
			curTime += this->inc;
	}

	return vels;
}
