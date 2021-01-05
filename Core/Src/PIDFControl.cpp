//
// Created by aadi on 2020-12-19.
//

#include "PIDFControl.h"
#include <cmath>
#include <limits>


PIDFControl::PIDFControl(double minOut, double maxOut, double kP, double kI, double kD, double kF) {
    this->minOut = minOut;
    this->maxOut = maxOut;

    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->kF = kF;  

    this->integral = 0;
    this->lastTime = -1;
    this->lastInput = std::numeric_limits<double>::quiet_NaN();
    this->lastOutput = std::numeric_limits<double>::quiet_NaN(); 

}

double PIDFControl::calculate(double target, double input, uint32_t time) {

    double error = target - input;

    double out = kP * error;

    if(this->kF != 0 && !std::isnan(this->lastOutput)) {
        out += kF * lastOutput;
    }

    if(this->lastTime != -1) {
	
       	uint32_t dt = time - this->lastTime;

		if (this->kI != 0) { 
			
			//integral calculations
	    	integral += dt * error;	
	    	out += this->kI * integral;
		}

		if (this->kD != 0 && dt != 0) {
			//derivative calculations
			out += this->kD * (input - this->lastInput)/dt;
		}
    }

    this->lastInput = input;
    this->lastTime = time;

    if(std::abs(out) < this->minOut) {

		out = (out / std::abs(out) *  this->minOut;
    } else if (std::abs(out) > this->maxOut) {
    
		out = (out / std::abs(out)) * this->maxOut;
    }	

    this->lastOutput = out;

    return out;
}
