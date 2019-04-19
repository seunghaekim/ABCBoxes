#include <Servo.h>

const String PASSWORD = "12";
const int PASSWORD_LENGTH = 2;
const int FAIL_LIMIT = 5;
int arrayLength(int sizeofArray) {
  return sizeofArray / sizeof(int);
}

Servo myservo;
int servoSpeed = 85;
int servoPin = 5;

bool STATUS = false;

int keypad[10] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40};
char keypadValue[11] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
int keyEnter = 42;
int keyPressed;
int keypadSize = sizeof(keypad);
int fail = 0;
String keyData;

int warnLedPin = 6;
int warnLedBlinkCnt = 200;
int warnLedBlinkDelay = 50;
int warnSirenPin = 7;

void setup() {
    for(int i = 0; i < arrayLength(keypadSize); i++){
      pinMode(keypad[i], INPUT);
    }
    pinMode(keyEnter, INPUT);
    
    pinMode(warnLedPin, OUTPUT);
    myservo.attach(servoPin);
}

void loop() {
  int enter;
  myservo.write(servoSpeed);
  
  if(STATUS == false){
    keyData = getKeyAction(keyData);
    if(keyData.length() > PASSWORD_LENGTH){
      keyData = "";
    }
    
    enter = getKeyState(keyEnter);
    if(enter != 0) {
      STATUS = (keyData == PASSWORD);

      if(STATUS == false) {
        fail += 1;
      }

      if(fail > FAIL_LIMIT)  {
        digitalWrite(warnSirenPin, HIGH);
        for(i = 0; i < wranLedBlinkCnt; i++;){
          digitalWrite(warnLedPin, HIGH);
          delay(warnLedBlinkDelay);
          digitalWrite(warnLedPin, LOW);
          delay(warnLedBlinkDelay);
        }
        digitalWrite(warnSirenPin, LOW);

        fail = 0;
        return;
      }
      return;
    }
  }

  if(STATUS == true){
    fail = 0;
    servoSpeed = 0;
    enter = getKeyState(keyEnter);
    if(enter != 0) {
      servoSpeed = 85;
      keyData = "";
      STATUS = false;
      return;
    }
  }
}

String getKeyAction(String keyData){
  int key;
  String val;
  for(int i = 0; i < arrayLength(keypadSize); i++){
    key = getKeyState(keypad[i]);
    if(key != 0){
      val = String(keypadValue[i]);
      keyData += val;
      break;
    }
  }
  return keyData;
}

int getKeyState(int keyPin) {
  if(digitalRead(keyPin) == HIGH) {
    if(keyPressed == keyPin){
      return 0;
    }
    keyPressed = keyPin;
  }
  
  if(digitalRead(keyPin) == LOW) {
    if(keyPressed == keyPin) {
      keyPressed = NULL;
    }
    return 0;
  }
  
  return keyPressed;
}
