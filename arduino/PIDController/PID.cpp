#include "PID.h"

PID::PID(double p, double i, double d, double t) : P(p), I(i), D(d), T(t) {

	integral = 0.0;
	previousError = 0.0;
	derivative = 0.0;
	previousMeasurement = 0.0;
	out = 0.0;
}

void PID::setParams(double _outMax, double _outMin, double _integralMax, double _integralMin, double _tau = 0.2) {
	
	outMax = _outMax;
	outMin = _outMin;
	integralMax = _integralMax;
	integralMin = _integralMin;
	tau = _tau;

}

double PID::update(double target, double measurement){

	double error = target - measurement;

	double proportional = P * error;

	integral += 0.5 * I * T * (error + previousError);

	if (integral > integralMax) {
	
		integral = integralMax;
	
	}

	else if (integral < integralMin) {

		integral = integralMin;

	}

	derivative = (-2.0 * D * (measurement - previousMeasurement) + (2.0 * tau - T) * derivative) / (2.0 * tau + T);

	out = proportional + integral + derivative;

	if (out > outMax) {

		out = outMax;

	}
	else if (out < outMin) {

		out = outMin;

	}

	previousError = error;
	previousMeasurement = measurement;

	return out;
	
}