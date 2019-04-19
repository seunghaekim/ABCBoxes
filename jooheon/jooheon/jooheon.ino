const int beepPin = 8;
const int beepPitch = 1000;
const long beepDuration = 200;
const int projectorPin = 9;
const int motorPinA = 6;
const int motorPinB = 6;
const long startTime = millis();
const int moveDuration = 100000;

bool isMove = true;

void setup() {
  pinMode(beepPin, OUTPUT);
  pinMode(projectorPin, OUTPUT);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
}

void loop() {
  if(isMove == true){
    digitalWrite(motorPinA, HIGH);
    if((millis() - startTime) > moveDuration){
      isMove = false;    
      tone(beepPin, beepPitch, 200);
    }
    return;
  }
  
  digitalWrite(motorPinA, LOW);
  digitalWrite(projectorPin, HIGH);
}
