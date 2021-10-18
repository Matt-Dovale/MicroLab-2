#define joyX A0
#define joyY A1

int xValue, yValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = map(analogRead(joyX), 0, 1023, -5, 5);
  yValue = map(analogRead(joyY), 0, 1023, -5, 5);

  //print the values with to plot or view
  if(xValue != 0 || yValue != 0){
    if(xValue < -2 && (yValue < 2 && yValue > -2)){
        Serial.println('l');
    }
    if(yValue < -2 && (xValue < 2 && xValue > -2)){
      Serial.println('u');
    }
    if(xValue > 2 && (yValue < 2 && yValue > -2)){
      Serial.println('r');
    }
    if(yValue > 2 && (xValue < 2 && xValue > -2)){
      Serial.println('d');
    }
    delay(100);
  }
}
