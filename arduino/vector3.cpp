#include "Vector3.h"
#include <math.h>

Vector3::Vector3() : x(0.0), y(0.0), z(0.0) {}

Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z){}

void Vector3::operator=(const Vector3 &v){

  x = v.x;
  y = v.y;
  z = v.z;

}

Vector3 Vector3::operator+(Vector3 &v) {

  return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(Vector3 &v) {

  return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(double &s) {

  return Vector3(x * s, y * s, z * s);

}

Vector3 Vector3::operator*(Vector3 &v) {

  return Vector3(x * v.x, y * v.y, z * v.z);

}

Vector3 Vector3::operator*(double mat3[3][3]) {

  Vector3 out;
  
  for (int row = 0; row < 3; row++) {

    double sum = 0;

    for (int col = 0; col < 3; col++) {

      if (col == 0)
        sum += x * mat3[row][col];
      else if (col == 1)
        sum += y * mat3[row][col];
      else 
        sum += z * mat3[row][col];

    }

    if (row == 0)
      out.x = sum;
    else if (row == 1)
      out.y = sum;
    else
      out.z = sum;

  }

  return out;

}

double Vector3::mag() {

  return sqrt(x * x + y * y + z * z);

}
