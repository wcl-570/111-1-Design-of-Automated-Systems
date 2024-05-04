#include <Wire.h> 
#include <BH1750.h>

BH1750 bh;

void setup(){ 
  Serial.begin(9600); 
  //initialize I2C 
  Wire.begin(); 
  bh.begin();
}

void loop() {
  //read data of BH1750
  float lux = lightMeter.readLightLevel(); 
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000); 
}