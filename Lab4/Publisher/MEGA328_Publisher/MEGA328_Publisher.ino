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

//Create getvalue() function
void getvalue() {
  sensors_event_t a, g, temp;
  // Get acceleration from MPU6050 mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x;
  accx = abs(ax);
  ay = a.acceleration.y;
  accy = abs(ay);
  az = a.acceleration.z;
  accz = abs(az);
  // Use the total acceleration formula to calculate the total acceleration
  double acc = sqrt(accx * accx + accy * accy + accz * accz);
  // Construct a string of payload with JSON format
  String payload = "{"; payload += acc; payload += "}";
  // Declare character array
  byte arrsize = payload.length()+1; char attributes[arrsize];
  // Convert string to character array format
  payload.toCharArray(attributes, arrsize);
  // Publish payload to Esp8266
  Serial.print(attributes);
}

//create setup() function
void setup() {
  // put your setup code here, to run once: 
  // Initialize Serial and set baud
  Serial.begin(9600);
  // Initialize Wire
  Wire.begin();
  // Initialize mpu
  mpu.begin(); 
}

//create loop() function
unsigned long lasttime = 0;
void loop() {
  if ( millis() - lasttime > 500 )
  {
  // Execute getvalue() to get acceleration ,and send data to Esp8266
  getvalue();
  // Record interval time of updated data
  lasttime = millis(); 
  }
}