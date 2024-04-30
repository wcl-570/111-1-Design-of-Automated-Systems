#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include <Servo.h>
MPU6050 accelgyro(0x68);
Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);
const int A = 3;
const int B = 4;
const int C = 5;
const int D = 6;
const int E = 7;
const int F = 9;
const int G = 8;
bool Bpress = false;
int UpPin = 10;
int CheckPin = 11;
int num = 0;
int ButtonUp = 0;
int LastButtonUp =0;
int ButtonCheck = 0;
int LastButtonCheck =0;
int16_t ax, ay, az;
int16_t gx, gy, gz;
double ax_offset, ay_offset, az_offset, gx_offset , gy_offset, gz_offset;
const double accel_factor = 4096, gyro_factor = 32.8;
double Pitch_angle, Roll_angle, Pitch_accel, Roll_accel, Yaw_angle;
const double RAD_TO_DAG = 180.0 / 3.14159265359;
double previous=90;
long previousTime;
long lastime;
void setup()
{ Serial.begin(115200);
Wire.begin();
lcd.begin();
pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(D, OUTPUT);
pinMode(E, OUTPUT);
pinMode(F, OUTPUT);
pinMode(G, OUTPUT);
pinMode(UpPin,INPUT_PULLUP);
Serial.println("Initializing I2C devices...");
accelgyro.initialize();
servo.attach(12);
servo.write(90);
// verify connection
Serial.println("Testing device connections...");
previousTime = millis(); }
double errorI=0;
void loop()
{
ButtonUp = digitalRead(UpPin);
ButtonCheck = digitalRead(CheckPin);
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
SensorFusion();
long nowTime = millis();
double Time = (nowTime - previousTime)/1000.0;
previousTime = nowTime;
double errorP = map(ay,-17000,17000,-10,10);
//Serial.println(Time);
errorI += ay * Time;
//Serial.println(errorI);
double totalError = errorP + errorI * 0.000001;
Serial.println(totalError);
previous = previous + totalError;
Serial.println(previous);
if (previous > 180)
{
previous = 180;
}
else if (previous < 0)
{
previous = 0;
}
servo.write(previous);
delay(50);
ButtonFusion();
}
void SensorFusion()
{
double accx = ax - ax_offset, accy = ay - ay_offset, accz = az
- az_offset ;
int g_total = accx * accx + accy * accy + accz * accz;
if (abs(g_total) < 33554432)
{
Pitch_accel = atan2(accx, sqrt(accy * accy + accz * accz))
* RAD_TO_DAG;
Roll_accel = atan2(accy, accz) * RAD_TO_DAG;
}
// Calculate gyro angle without any filter
double dt = (millis() - lastime) / 1000.0;
lastime = millis();
Pitch_angle += (-(gy - gy_offset) / gyro_factor) * dt;
Roll_angle += ((gx - gx_offset) / gyro_factor) * dt;
Yaw_angle += (-(gz - gz_offset) / gyro_factor) * dt;
// Calculate the angle using a Complimentary filter
Pitch_angle = 0.9 * Pitch_angle + 0.1 * Pitch_accel;
Roll_angle = 0.9 * Roll_angle + 0.1 * Roll_accel;
}
void ButtonFusion()
{
if(ButtonUp != LastButtonUp)
{
if(ButtonUp == LOW)
{
Bpress = true;
num++;
if(num >= 3)
{
num = 0;
}
ChangeNum(num);
}
LastButtonUp = ButtonUp;
}
if(ButtonCheck == HIGH)
{
if(num == 0)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MPU6050");
lcd.setCursor(0,1);
lcd.print("The yaw angle:");
lcd.setCursor(0,2);
lcd.print(Yaw_angle);
}
if(num == 1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MPU6050");
lcd.setCursor(0,1);
lcd.print("The pitch angle:");
lcd.setCursor(0,2);
lcd.print(Pitch_angle);
}
if(num == 2)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MPU6050");
lcd.setCursor(0,1);
lcd.print("The roll angle:");
lcd.setCursor(0,2);
lcd.print(Roll_angle);
}
}
}
void ChangeNum(int button1)
{
switch (button1)
{
case 0:
digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, LOW);
break;
case 1:
digitalWrite(A, LOW);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);
digitalWrite(E, LOW);
digitalWrite(F, LOW);
digitalWrite(G, LOW);
break;
case 2:
digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, LOW);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, LOW);
digitalWrite(G, HIGH);
break;
}
}