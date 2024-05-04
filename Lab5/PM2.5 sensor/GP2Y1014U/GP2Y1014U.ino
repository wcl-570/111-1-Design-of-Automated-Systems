//connect dust sensor to Arduino A1 pin
int measurePin = A1;
//connect 3 led driver pins of dust sensor to Arduino D2
int ledPower = 2;

int samplingTime = 280; 
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0; 
float calcVoltage = 0; 
float dustDensity = 0;

void setup() { 
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT); 
}

void loop() {
  //power on the LED
  digitalWrite(ledPower,LOW); 
  delayMicroseconds(samplingTime);
  //read the dust value
  voMeasured = analogRead(measurePin); 
  delayMicroseconds(deltaTime);

  digitalWrite(ledPower,HIGH); //turn the LED off 
  delayMicroseconds(sleepTime);

  //0 - 5V mapped to 0 - 1023 integer values 
  //recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  //linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  //Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;

  Serial.print("Raw Signal Value (0-1023): "); 
  Serial.print(voMeasured);
  Serial.print(" - Voltage: "); 
  Serial.print(calcVoltage);
  Serial.print(" - Dust Density: ");
  //change the numerical display to ug/m3
  Serial.print(dustDensity * 1000); 
  Serial.println(" ug/m3 "); 
  delay(1000);
}
s