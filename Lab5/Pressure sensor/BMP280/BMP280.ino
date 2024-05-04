#include <SPI.h>
#include "Adafruit_Sensor.h" 
#include "Adafruit_BMP280.h"

//set SPI
#define BMP_SCK 13 
#define BMP_MISO 12 
#define BMP_MOSI 11 
#define BMP_CS 10

//set BMP280
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);

void setup() { 
  Serial.begin(9600);
  bmp.begin();
}

void loop() {
  Serial.print("Pressure = ");
  //diplay data of BMP280 
  Serial.print(bmp.readPressure()/100); 
  Serial.println(" hPa");
  delay(2000);
}
