#include <vector3.h>
#include <StewartPlatform.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50

#define LL 12
#define UL 13
#define LR 11
#define UR 10
#define S A0

StewartPlatform s;

void setup() {
    
    pinMode(LL, OUTPUT); 
    pinMode(UL, OUTPUT); 
    pinMode(LR, OUTPUT); 
    pinMode(UR, OUTPUT); 
    
    Serial.begin(9600);
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ);
    delay(10);

}

void loop() {

    int x, y;

    getTouchScreenPos(x, y);

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
	
	//Serial.println(pos[i]);
	pwm.writeMicroseconds(i, pos[i]);

    }


}

void getTouchScreenPos(int &x, int &y){

    digitalWrite(UR, HIGH);
    digitalWrite(LR, HIGH);
    digitalWrite(UL, LOW);
    digitalWrite(LL, LOW);
    
    delay(10);
    x = analogRead(S);

    digitalWrite(UR, HIGH);
    digitalWrite(LR, LOW);
    digitalWrite(UL, HIGH);
    digitalWrite(LL, LOW);
    
    delay(10);
    y = analogRead(S);
    
    Serial.print(x);  
    Serial.print(",");
    Serial.println(y);
}
