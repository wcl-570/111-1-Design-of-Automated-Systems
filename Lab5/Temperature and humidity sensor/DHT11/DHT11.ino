#include "DHT.h"
#define dhtPin 6
//chose DHT11
#define dhtType DHT11

//initialize DHT sensor
DHT dht(dhtPin, dhtType);

void setup() { 
  Serial.begin(9600); //set bauds
  dht.begin(); //start DHT11
}

void loop() {
  //read data of Temperature
  float t = dht.readTemperature();
  //read data of Humidity
  int h = dht.readHumidity();
  Serial.print("Temperature: "); 
  Serial.print(t); Serial.print("*C \t"); 
  Serial.print("Humidity: "); 
  Serial.print(h); 
  Serial.print("% \n"); 
  delay(1000);
}