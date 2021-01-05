//
// Created by aadi on 2020-12-19.
//

#ifndef CONTROLTHEORY_PIDCONTROL_H
#define CONTROLTHEORY_PIDCONTROL_H


class PIDFControl {
    private:
       double minOut, maxOut;
       double kP, kI, kD, kF;
       double integral; //used for kI
       double lastInput; //used for kD
       uint32_t lastTime;
       double lastOutput; //used for kF

    public:

       PIDFControl(double minOut, double maxOut, double kP, double kI, double kD, double kF);

       double calculate(double target, double input, uint32_t time);

};


#endif //CONTROLTHEORY_PIDCONTROL_H
