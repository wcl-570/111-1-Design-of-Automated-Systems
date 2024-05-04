//create Atmega code
//include libraries and sensor setting
#include "SoftwareSerial.h" 
#include "DHT.h"
#include <Wire.h> 
#include <BH1750.h> 
#include <SPI.h>
#include "Adafruit_Sensor.h" 
#include "Adafruit_BMP280.h" 
#include <MQ135.h>
#define DHTPIN 6
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 

//declare BH1750 variables 
BH1750 bh;

//declare BMP280 variables 
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10 
Adafruit_BMP280 
bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK); 

//declare MQ135 variables
MQ135 gasSensor = MQ135 (A0); 

//declare GP2Y1014AU variables 
int measurePin = A1;
int ledPower = 2;
int samplingTime = 280; 
int deltaTime = 40;
int sleepTime = 9680; 
float voMeasured = 0; 
float calcVoltage = 0; 
float pm25 = 0;

//create getvalue() function
void getvalue() {
  //read temperature datas of DHT11
  float temperature = dht.readTemperature(); 
  //read humidity datas of DHT11
  int humidity = dht.readHumidity();
  //read illuminance datas of BH1750
  float light = bh.readLightLevel();
  //read pressure datas of BMP280
  float pressure = bme.readPressure() / 100; 
  //read CO2 datas of MQ135
  float co2 = gasSensor.getPPM();
  //read PM2.5 datas of GP2Y1014AU
  //power on the LED 
  digitalWrite(ledPower,LOW); 
  delayMicroseconds(samplingTime);
  //read the dust value
  float value = analogRead(measurePin); 
  delayMicroseconds(deltaTime);
  //turn the LED off
  digitalWrite(ledPower,HIGH); 
  delayMicroseconds(sleepTime);
  //0 - 5V mapped to 0 - 1023 integer values 
  //recover voltage
  calcVoltage = value * (5.0 / 1024.0);
  pm25 = (0.17 * calcVoltage - 0.1) * 1000;

  //create strings of payload with JSON format
  String payload = "{";
  payload += "\"Temp\":"; payload += temperature; payload += ","; 
  payload += "\"Hum\":"; payload += humidity; payload += ","; 
  payload += "\"Lm\":"; payload += light; payload += ",";
  payload += "\"Pre\":"; payload += pressure; payload += ","; 
  payload += "\"CO2\":";payload += co2; payload += ",";
  payload += "\"PM25\":";payload += pm25; payload += "}";

  //send payload
  byte arrsize = payload.length()+1; 
  //serial.println(arrsize);
  char attributes[arrsize]; 
  payload.toCharArray(attributes, arrsize); 
  //publish payload to Broker 
  Serial.println(attributes);
}

//create setup() function and timer
#include "Timer.h" 

Timer t;
void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200);
  t.every(5000,getvalue);
  //execute getvalue() every 5 seconds
  Wire.begin();
  pinMode(7, OUTPUT); 
  dht.begin();
  bh.begin(); 
  bme.begin(0x76);
  //execute set 
  pinMode(ledPower,OUTPUT); 
}

//create loop() function
void loop() {
  //put your main code here, to run repeatedly:
  String readString;
  String incog;
  if (Serial.available() > 0) {
    incog = Serial.readString(); 
    if (incog.equals("LEDon")) {
      digitalWrite(7, HIGH); 
      //turn the LED on (Note that LOW is the voltage level
    }
    if (incog.equals("LEDoff")) { 
      digitalWrite(7, LOW);
      //turn the LED on (Note that LOW is the voltage level
    } 
  }
  t.update(); 
}
