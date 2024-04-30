#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <Servo.h>
MPU6050 accelgyro(0x68);
Servo servo;
int16_t ax, ay, az;
int16_t gx, gy, gz;
double previous=90; // 誤差角度初始值
void setup()
{
Serial.begin(115200);
Wire.begin();
Serial.println("Initializing I2C devices...");
accelgyro.initialize();
servo.attach(12); // Servo motor pin
servo.write(90); // 初始角度
// Verify connection
Serial.println("Testing device connections...");
}
void loop()
{
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
double a = ay*9.8/16384; // ay加速度值計算
previous = previous + a; // 偏轉角度計算
// 防止角度超過0~180度範圍
if (previous > 180)
{
previous = 180;
}
else if (previous < 0)
{
previous = 0;
}
servo.write(previous); // 角度觸發
delay(50);
}