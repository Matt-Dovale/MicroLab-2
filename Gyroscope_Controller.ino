#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t GyX,GyY,GyZ;
int buzzer = 8;
int incomingByte = 0;
void setup(){
  pinMode(buzzer, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  /*
  Serial.print(" | GyX = "); Serial.print(GyX); Serial.print(" | ");
  Serial.print(" | GyY = "); Serial.print(GyY); Serial.print(" | ");
  Serial.print(" | GyZ = "); Serial.print(GyZ); Serial.print(" | ");
  Serial.println();
  */

  if(GyY < -5000 && (GyX > -5000 && GyX < 5000)){
    Serial.println("u");
  }
  else if(GyY > 5000 && (GyX > -5000 && GyX < 5000)){
    Serial.println("d");
  }
  else if(GyX > 5000 && (GyY > -5000 && GyY < 5000)){
    Serial.println("l");
  }
  else if(GyX < -5000 && (GyY > -5000 && GyY < 5000)){
    Serial.println("r");
  }

  if (Serial.available() > 0){ // Buzzer beeps 
    incomingByte = Serial.read();
    if(incomingByte = 'B'){
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }
  }
  delay(200);
}
