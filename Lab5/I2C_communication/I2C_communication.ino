#define SENSOR_I2CADD 0x45 //address for the sensor. Different for each device connected.
#include <Wire.h> //I2C library

char dataByte;

void setup() { 
  Wire.begin();
  Serial.begin(9600); 
}

void loop() {
  Wire.beginTransmission(SENSOR_I2CADD); //begin transmission to address 0x45 
  Wire.write(0x22); //register address within the sensor where the data is to be read from Wire.endTransmission();
  Wire.requestFrom(SENSOR_I2CADD, 1); //get a byte(1) from the register address 0x22 
  if(Wire.available()){ //if the buffer has data
    dataByte = Wire.read(); //save the data to a variable
  }
  Serial.println(dataByte); //print the received byte to Serial 
  delay(100);
}