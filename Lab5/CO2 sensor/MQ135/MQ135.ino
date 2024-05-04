#include "MQ135.h"
//define Analog PIN on Arduino Board
#define ANALOGPIN A0
//define RZERO Calibration Value
#define RZERO 206.85

MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  Serial.begin(9600);
  float rzero = gasSensor.getRZero(); 
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  //display rzero valur of MQ135
  Serial.println(rzero); 
}

void loop() {
  //read data of MQ135
  float ppm = gasSensor.getPPM(); 
  delay(1000); 
  digitalWrite(13,HIGH); 
  Serial.print("CO2 ppm value : "); 
  Serial.println(ppm);
}