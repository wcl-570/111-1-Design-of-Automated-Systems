#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
MPU6050 accelgyro(0x68); // MPU6050 address 0x68
int16_t ax, ay, az;
int16_t gx, gy, gz;
double ax_offset, ay_offset, az_offset, gx_offset , gy_offset,
gz_offset;
const double accel_factor = 4096, gyro_factor = 32.8;
double Pitch_angle, Roll_angle, Pitch_accel, Roll_accel,
Yaw_angle;
const double RAD_TO_DAG = 180.0 / 3.14159265359;
long lastime;
void setup()
{
Serial.begin(115200);
Wire.begin(); // I2C communication
Serial.println("Initializing I2C devices...");
accelgyro.initialize();
// verify connection
Serial.println("Testing device connections...");
}
void loop()
{ // Get MPU6050 value
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
SensorFusion(); // 觸發函式SensorFusion()
Serial.print("Yaw = "); Serial.print(Yaw_angle); Serial.print(", ");
Serial.print("Pitch = "); Serial.print(Pitch_angle);
Serial.print(", ");
Serial.print("Roll = "); Serial.println(Roll_angle);
}
void SensorFusion() // Calculate angle(yaw, pitch, roll)
{
double accx = ax - ax_offset, accy = ay - ay_offset, accz =
az - az_offset ;
int g_total = accx * accx + accy * accy + accz * accz;
//超過4096*4096*2 = 2G 表示加速規不準，不採納其讀值
if (abs(g_total) < 33554432)
{
Pitch_accel = atan2(accx, sqrt(accy * accy + accz * accz))
* RAD_TO_DAG;
Roll_accel = atan2(accy, accz) * RAD_TO_DAG;
}
// Calculate the angle without filter
double dt = (millis() - lastime) / 1000.0;
lastime = millis();
Pitch_angle += (-(gy - gy_offset) / gyro_factor) * dt;
Roll_angle += ((gx - gx_offset) / gyro_factor) * dt;
Yaw_angle += (-(gz - gz_offset) / gyro_factor) * dt;
// Calculate the angle with the Complimentary filter
Pitch_angle = 0.9 * Pitch_angle + 0.1 * Pitch_accel;
Roll_angle = 0.9 * Roll_angle + 0.1 * Roll_accel;
}