#ifndef vector3
#define vector3

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Vector3 {
  
public:

  double x, y, z;

  Vector3();
  Vector3(double _x, double _y, double _z);

  void operator=(const Vector3 &v);

  Vector3 operator+(Vector3 &v);
  Vector3 operator-(Vector3 &v);

  Vector3 operator*(double &s);
  Vector3 operator*(Vector3 &v);
  Vector3 operator*(double mat3[3][3]);

  double mag();

};

#endif
