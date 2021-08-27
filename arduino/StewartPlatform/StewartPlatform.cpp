#include <math.h>
#include "StewartPlatform.h"
#include "vector3.h"

#define pi 3.14159
#define deg2rad pi/180
#define rad2deg 180/pi

const double BASE_ANGLE_OFFSET = 21.689;
const double PLATFORM_ANGLE_OFFSET = 3.668;
const double BASE_RADIUS = sqrt(8969);
const double PLATFORM_RADIUS = 78.16;
const double LEG_LENGTH = 195.0;
const double SERVO_HORN_LENGTH = 23.5;
const double SERVO_HEIGHT = 40.0;
const double PLATFORM_HEIGHT = 222.11 - SERVO_HEIGHT;
const double BASE_ANGLES[6] = { 360 - BASE_ANGLE_OFFSET, BASE_ANGLE_OFFSET, 120 - BASE_ANGLE_OFFSET, 120 + BASE_ANGLE_OFFSET, 240 - BASE_ANGLE_OFFSET, 240 + BASE_ANGLE_OFFSET };
const double PLATFORM_ANGLES[6] = { 300 + PLATFORM_ANGLE_OFFSET, 60 - PLATFORM_ANGLE_OFFSET, 60 + PLATFORM_ANGLE_OFFSET, 180 - PLATFORM_ANGLE_OFFSET, 180 + PLATFORM_ANGLE_OFFSET, 300 - PLATFORM_ANGLE_OFFSET };
const double BETA[6] = { pi / 2, -pi / 2, -5 * pi / 6, pi / 6, -pi / 6, 5 * pi / 6 };
const double W0[6] = { 1650, 1650, 1625, 1625, 1650, 1575 };

StewartPlatform::StewartPlatform() {

  T = Vector3(0, 0, PLATFORM_HEIGHT);

  calcBandP();

  moveTo(T, 0, 0, 0);

}

void StewartPlatform::moveTo(Vector3 trans, double yaw, double pitch, double roll) {

  T = trans;

  calcR(R, yaw, pitch, roll);

  calcQ();
    
  double angles[6] = { 0,0,0,0,0,0 };
  calcAngles(angles);

  calcW(angles);

}

void StewartPlatform::calcBandP() {

  for (int i = 0; i < 6; i++) {

    Vector3 b(BASE_RADIUS * cos(BASE_ANGLES[i] * deg2rad), BASE_RADIUS * sin(BASE_ANGLES[i] * deg2rad), 0);
    Vector3 p(PLATFORM_RADIUS * cos(PLATFORM_ANGLES[i] * deg2rad), PLATFORM_RADIUS * sin(PLATFORM_ANGLES[i] * deg2rad), 0);

    B[i] = b;
    P[i] = p;

  }

}

void StewartPlatform::calcQ() {

  for (int i = 0; i < 6; i++) {

    Q[i] = (P[i] * R) + T;
  
  }

}

void StewartPlatform::calcAngles(double thetas[6]) {

  double minAngle, maxAngle, currentTheta = 0.0;
  int n = 0;

  for (int i = 0; i < 6; i++) {
    
    minAngle = -45;
    maxAngle = 45;

    currentTheta = 0;
    n = 0;

    while (n < 10) {
    
      Vector3 a = calcA(currentTheta, i);
      Vector3 dl = Q[i] - a;

      if (abs(LEG_LENGTH - dl.mag()) < 0.01) {

        thetas[i] = currentTheta;
        break;

      }

      else {
      
        if (dl.mag() < LEG_LENGTH) {
        
          maxAngle = currentTheta;
        
        }

        else {

          minAngle = currentTheta;

        }

        n += 1;

        if (minAngle == 45.0 || maxAngle == -45.0){
        
          thetas[i] = currentTheta;
          break;
        
        }

        currentTheta = minAngle + ((maxAngle - minAngle) / 2);
      
      }
    
    }
  
  }
  
}

Vector3 StewartPlatform::calcA(double ang, int i) {

  Vector3 a;

  a.x = SERVO_HORN_LENGTH * cos(ang * deg2rad) * cos(BETA[i]) + B[i].x;
  a.y = SERVO_HORN_LENGTH * cos(ang * deg2rad) * sin(BETA[i]) + B[i].y;
  a.z = SERVO_HORN_LENGTH * sin(ang * deg2rad) + B[i].z;

  return a;
}


void StewartPlatform::calcR(double R[3][3], double psi, double theta, double phi) {
  
  R[0][0] = (cos(psi) * cos(theta));
  R[0][1] = ((-sin(psi) * cos(phi)) + (cos(psi) * sin(theta) * sin(phi)));
  R[0][2] = ((sin(psi) * sin(phi)) + (cos(psi) * sin(theta) * cos(phi)));
  R[1][0] = (sin(psi) * cos(theta));
  R[1][1] = ((cos(psi) * cos(phi)) + (sin(psi) * sin(theta) * sin(phi)));
  R[1][2] = ((-cos(psi) * sin(phi) + (sin(psi) * sin(theta) * cos(phi))));
  R[2][0] = (-sin(theta));
  R[2][1] = (cos(theta) * sin(phi));
  R[2][2] = (cos(theta) * cos(phi));
  
}

void StewartPlatform::calcW(double angles[6]) {

  double r = 400.0 / 45.0;

  for (int i = 0; i < 6; i++) {
  
    if (i % 2 == 0)
      W[i] = round(W0[i] + angles[i] * r);
    else
      W[i] = round(W0[i] - angles[i] * r);

  }

}
