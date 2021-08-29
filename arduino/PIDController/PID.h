#ifndef pid
#define pid

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class PID{

private:

	double P;
	double I;
	double D;

	double T;

	double tau;

	double integral;
	double integralMax;
	double integralMin;
	double previousError;

	double derivative;
	double previousMeasurement;

	double outMax;
	double outMin;

public:

	PID(double p, double i, double d, double t);
	double update(double target, double measurement);
	void setParams(double _outMax, double _outMin, double _integralMax, double _integralMin, double _tau);
	
	double out;
};

#endif