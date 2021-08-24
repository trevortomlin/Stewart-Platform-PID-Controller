#ifndef stewartplatform
#define stewartplatform

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "vector3.h"

class StewartPlatform {

private:

  Vector3 T;
  Vector3 A[6];
  Vector3 B[6];
  Vector3 P[6];
  Vector3 Q[6];

  double R[3][3];
  double l[6];
  double alpha[6];
  double W[6];
  double h0;
  double alpha0 = NAN;

public:

  StewartPlatform();

  void moveTo(Vector3 trans, double yaw, double pitch, double roll);

  void calcBandP();

  void calcQ();

  void calcR(double R[3][3], double psi, double theta, double phi);

  void calcW(double angles[6]);

  void calcAngles(double thetas[6]);

  Vector3 calcA(double ang, int i);

};

#endif

