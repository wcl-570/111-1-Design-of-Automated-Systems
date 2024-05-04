//include libraries and WiFi & Mega328
//include function libraries
#include "SoftwareSerial.h" 
#include <Adafruit_MPU6050.h> 
#include <Adafruit_Sensor.h> 
#include <Wire.h>

//declare MPU6050 variables
Adafruit_MPU6050 mpu; 
double ax, ay, az; 
double accx, accy, accz;

//create getvalue() function
void getvalue() {
  sensors_event_t a, g, temp;
  //get acceleration from MPU6050 mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x;
  accx = abs(ax);
  ay = a.acceleration.y;
  accy = abs(ay);
  az = a.acceleration.z;
  accz = abs(az);
  //use the total acceleration formula to calculate the total acceleration
  double acc = sqrt(accx * accx + accy * accy + accz * accz);
  //construct a string of payload with JSON format
  String payload = "{"; payload += acc; payload += "}";
  //declare character array
  byte arrsize = payload.length()+1; char attributes[arrsize];
  //convert string to character array format
  payload.toCharArray(attributes, arrsize);
  //publish payload to Esp8266
  Serial.print(attributes);
}

//create setup() function
void setup() {
  //put your setup code here, to run once: 
  //initialize Serial and set baud
  Serial.begin(9600);
  //initialize Wire
  Wire.begin();
  //initialize mpu
  mpu.begin(); 
}

//create loop() function
unsigned long lasttime = 0;
void loop() {
  if (millis() - lasttime > 500) {
  //execute getvalue() to get acceleration ,and send data to Esp8266
  getvalue();
  //record interval time of updated data
  lasttime = millis(); 
  }
}
