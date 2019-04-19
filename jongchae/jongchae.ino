#include <Servo.h>

const byte ledSetSize = 4;
int ledSet[ledSetSize] = {8, 9, 10, 11};
int lightLedIdx = 0;

Servo myservo;
int servoSpeed = 85;
int servoPin = 3;

void setup()
{
  myservo.attach(servoPin);
  for(int i = 0; i < ledSetSize; i++){
    pinMode(ledSet[i], OUTPUT);
  }
}

void loop()
{
  myservo.write(servoSpeed);
  for(int i = 0; i < ledSetSize; i++){
    if(i == lightLedIdx){
      digitalWrite(ledSet[i], HIGH);
    }
    else {
      digitalWrite(ledSet[i], LOW);
    }
  }
  lightLedIdx = lightLedIdx + 1;
  if(lightLedIdx == int(ledSetSize)){
    lightLedIdx = 0;
  }
  delay(1000);
}
