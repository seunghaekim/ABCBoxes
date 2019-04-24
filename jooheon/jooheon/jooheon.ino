#include <Servo.h>

Servo myservo;
const int beepPin = 8;
const int beepPitch = 1000;
const int projectorRoterPin = 10;
const long beepDuration = 200;
const int projectorPin = 9;
const int motorPinAa = 3;
const int motorPinAb = 5;
const int motorPinBa = 7;
const int motorPinBb = 6;
const long startTime = millis();
const long moveDuration = 100000;

bool isMove = true;

void setup() {
  Serial.begin(9600);
  pinMode(beepPin, OUTPUT);
  pinMode(projectorPin, OUTPUT);
  pinMode(motorPinAa, OUTPUT);
  pinMode(motorPinAb, OUTPUT);
  pinMode(motorPinBa, OUTPUT);
  pinMode(motorPinBb, OUTPUT);
  myservo.attach(projectorRoterPin);
}
//
void loop() {
  motorLoop(isMove);
  projector(isMove);
  if(isMove == true){
    if((millis() - startTime) > moveDuration){
      isMove = false;    
      tone(beepPin, beepPitch, 200);
    }
    return;
  }
}

void motorLoop(bool is_run){
    if(is_run == true){
      digitalWrite(motorPinAa, LOW);
      digitalWrite(motorPinAb, HIGH);
      digitalWrite(motorPinBa, LOW);
      digitalWrite(motorPinBb, HIGH);
      return;
    }
    digitalWrite(motorPinAa, LOW);
    digitalWrite(motorPinAb, LOW);
    digitalWrite(motorPinBa, LOW);
    digitalWrite(motorPinBb, LOW);
}

void projector(bool is_run){
  if(is_run == true){
     myservo.write(85);
     digitalWrite(projectorPin, HIGH);
  }
  myservo.write(0);
  digitalWrite(projectorPin, LOW);
}
