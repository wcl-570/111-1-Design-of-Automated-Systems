#include <Servo.h>;
// Create servo object to control a servo
Servo myservo;
void setup() {
myservo.attach(12);
/* Attache the control signal of the servo
to pin 12 */ }
void loop() {
myservo.write(150);
delay(1000);
myservo.write(30);
delay(1000); }
