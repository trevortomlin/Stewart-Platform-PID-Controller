#include <vector3.h>
#include <StewartPlatform.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50

StewartPlatform s;

void setup() {
    
    Serial.begin(9600);
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ);
    delay(10);

}

void loop() {

    Vector3 r(30, 0, 222.11-40.0);
    s.moveTo(r, 0, 0, 0);
    writeServos(s.W);
    
    delay(5000);

    Vector3 t(0, 0, 222.11-40.0);
    s.moveTo(t, 0, 0, 0);
    writeServos(s.W);

    delay(5000);

    Vector3 e(-25, 0, 222.11-40.0);
    s.moveTo(e, 0, 0, 0);
    writeServos(s.W);

    delay(5000);


}

void writeServos(double pos[6]){

    for (int i=0; i < 6; i++){
	
	Serial.println(pos[i]);
	pwm.writeMicroseconds(i, pos[i]);

    }


}
