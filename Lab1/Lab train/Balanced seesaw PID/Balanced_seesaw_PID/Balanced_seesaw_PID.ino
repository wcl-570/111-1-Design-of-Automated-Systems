#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <Servo.h>

MPU6050 accelgyro(0x68);
Servo servo;

int16_t ax, ay, az;
int16_t gx, gy, gz;
double previous=90;
long previousTime;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  servo.attach(12);
  servo.write(90);
  Serial.println("Testing device connections...");
  previousTime = millis(); //設置初始時間(上一個時間)
}

double errorI=0; //設置初始積分誤差值
void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  long nowTime = millis(); //設置目前時間
  //計算時間差值
  double Time = (nowTime - previousTime)/1000.0;
  previousTime = nowTime; //將現在時間存入上一個時間
  //計算比例誤差值
  double errorP = map(ay,-17000,17000,-10,10);
  errorI += ay * Time; //計算積分誤差值
  //誤差總和
  double totalError = errorP + errorI * 0.000001;
  //偏轉角度計算
  previous = previous + totalError;
  if (previous > 180) {
    previous = 180;
  } else if (previous < 0) {
    previous = 0;
  }
  servo.write(previous);
  delay(50);
}
