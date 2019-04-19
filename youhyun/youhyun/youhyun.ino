int rgbPin[3] = {3, 6, 5}; // red, green, blue
int rainbow[7][3] = {
  {255, 63, 63},  // red
  {255, 149, 63}, // orange
  {255, 229, 63}, // yellow
  {168, 255, 63}, // green
  {63, 194, 255}, // blue
  {82, 63, 255},  // navy
  {191, 63, 255}  // purple
};
int rainbowIdx = 0;

int motorLeftPin = 8;
int motorRightPin = 9;
int motorCenterPin = 10;
bool motor_is_left = false;

bool checkTrigger(int trigger) {
  if(millis() == 0 || (millis() % trigger) == 0){
    return true;
  }
  return false;
}

void setup()
{ 
  pinMode(motorLeftPin, OUTPUT);
  pinMode(motorCenterPin, OUTPUT);
  pinMode(motorRightPin, OUTPUT);
  // RGB LED
  for(int i = 0; i < sizeof(rgbPin); i++){
    pinMode(rgbPin[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  rainbowLoop();
  motorLoop();
}

void rainbowLoop(){
  int trigger = 3000;
  if(checkTrigger(trigger) == false){
    return;
  }
  
  for(int i = 0; i < sizeof(rainbow[rainbowIdx]); i++){
    analogWrite(rgbPin[i], rainbow[rainbowIdx][i]);
  }
  rainbowIdx++;
  if(rainbowIdx > sizeof(rainbow)){
    rainbowIdx = 0;
  }
}

void motorLoop(){
  int trigger = 50;
  
  digitalWrite(motorCenterPin, HIGH);
  
  if(checkTrigger(trigger) == false){
    return;
  }
  
  if(motor_is_left == false){
    digitalWrite(motorRightPin, LOW);
    digitalWrite(motorLeftPin, HIGH);
    motor_is_left = true;
  }
  else {
    digitalWrite(motorRightPin, HIGH);
    digitalWrite(motorLeftPin, LOW);
    motor_is_left = false;
  }
}
