#include <Servo.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>

#include <Key.h>
#include <Keypad.h>

// password
const String PASSWORD   = "1221213";
      String passIn     = "";
      bool passCompair  = false;
      int passTry       = 0;
      int passTryLimit  = 5;

// keypad
const byte ROWS = 4;
const byte COLS = 3;
const char keys[ROWS][COLS] = {
   {'1', '2', '3'},
   {'4', '5', '6'},
   {'7', '8', '9'},
   {'*', '0', '#'}
};

// 22 24 26 28 30 32 34
byte rowPins[ROWS] = {24, 34, 32, 28};
byte colPins[COLS] = {26, 22, 30};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2);  

// Servo as spinner
const int servoPin = 2;
Servo servo;

// fail
const int failLed = 3;
const long failLoopTime = 200000; // 200 sec

// solenoid
const int solPinA = 4;
const int solPinB = 5;

void setup(){
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(failLed, OUTPUT);
  pinMode(solPinA, OUTPUT);
  pinMode(solPinB, OUTPUT);
  lcd.begin();
  lcd.backlight();
}

void loop(){
  if(passCompair == false){
    SpinnerLoop();
    if(passTry >= passTryLimit){
      passFailLoop();
      return;
    }
    keyinLoop();
    return;
  }

  lcd.clear();
  lcd.print("Sucess");
  servo.write(0);

  char key = keypad.getKey();
  if(key != NO_KEY){
    if(key == '#'){
      passCompair = false;
      passTry = 0;
      passIn = "";
      return;
    }
  }
}

void keyinLoop(){
  char key = keypad.getKey();
  int passLen = passIn.length();
  
  if(key != NO_KEY){
    switch(key) {
      case char('*'):
        if(passLen > 0){
          passIn = passIn.substring(0, (passLen - 1));
        }
        break;
      case char('#'):
        passCompair = PASSWORD.equals(passIn);
        if(passCompair == false){
          passTry = passTry + 1;
          char bfr[60];
          sprintf(bfr, "Failed (%d/%d)", char(passTry), char(passTryLimit));
          lcd.clear();
          lcd.print(bfr);
          passIn = "";
          return;
        }
        break;
      default: 
        passIn = passIn + String(key);
        break;
    }
    
    lcd.clear();
    lcd.print(passIn);
  }
}

void passFailLoop(){
  long startAt = millis();
  while(true){
    lcd.clear();
    lcd.print("FAILED !!!");
    delay(10);
    digitalWrite(failLed, HIGH);
    delay(10);
    digitalWrite(failLed, LOW);
    if((millis() - startAt) >= failLoopTime){
      break;
    }
  }
  
  lcd.clear();
  passIn = "";
  passTry = 0;
}

void SpinnerLoop(){
  servo.write(180);
  delay(10);
  servo.write(0);
  delay(10);
}
