#include "Wire.h"
#include "LiquidCrystal_I2C.h"
const int A = 3; // Set 7-Seg pins
const int B = 4;
const int C = 5;
const int D = 6;
const int E = 7;
const int F = 9;
const int G = 8;
bool Bpress = false; // Set button1 signal as false
int UpPin = 10; // Set Button1(UpPin) pin
int CheckPin = 11; // Set Button2(CheckPin) pin
int num = 0; // Set variable int as initial value
int ButtonUp = 0;
int LastButtonUp =0;
int ButtonCheck = 0;
int LastButtonCheck =0;
// Set LCD I2C communication
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
Serial.begin(9600);
lcd.begin(); // Set LCD display interface size
pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(D, OUTPUT);
pinMode(E, OUTPUT);
pinMode(F, OUTPUT);
pinMode(G, OUTPUT);
pinMode(UpPin,INPUT_PULLUP);
}
void loop()
{
// Set ButtonUp(該按鈕為數字切換紐)
ButtonUp = digitalRead(UpPin);
// Set ButtonCheck (該按鈕為數字確認紐)
ButtonCheck = digitalRead(CheckPin);
if(ButtonUp != LastButtonUp)
{
if(ButtonUp == LOW) // If ButtonUp為低電位
{
Bpress = true; // Set button1 signal as true
num++; // 按鈕次數疊加
if(num >= 3) // 如果次數大於3，則回到0
{
num = 0;
}
ChangeNum(num); // 觸發函式ChangeNum()
delay(50);
}
}
if(ButtonCheck == HIGH) // If ButtonCheck為高電位
{// 若確認該數字則會顯示指定名稱及數值
if(num == 0) // 如果num=0，則LCD顯示yaw值
{
lcd.clear(); // 清除LCD顯示文字
lcd.setCursor(0,0); // 顯示第一列文字
lcd.print("MPU6050");
lcd.setCursor(0,1);
lcd.print("The yaw angle:");
lcd.setCursor(0,2);
lcd.print("yaw");
}
if(num == 1) // 如果num=1，則LCD顯示pitch值
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MPU6050");
lcd.setCursor(0,1);
lcd.print("The pitch angle:");
lcd.setCursor(0,2);
lcd.print("pitch");
}
if(num == 2) // 如果num=2，則LCD顯示roll值
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MPU6050");
lcd.setCursor(0,1);
lcd.print("The roll angle:");
lcd.setCursor(0,2);
lcd.print("roll");
}}}
void ChangeNum(int button1) // 函式ChangeNum()
{
switch (button1)
{
case 0: // 當button 1=0，7-Seg.顯示0
digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, HIGH);
digitalWrite(G, LOW);
break;
case 1: // 當button 1=1，7-Seg.顯示1
digitalWrite(A, LOW);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);
digitalWrite(E, LOW);
digitalWrite(F, LOW);
digitalWrite(G, LOW);
break;
case 2: // 當button 1=2，7-Seg.顯示2
digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, LOW);
digitalWrite(D, HIGH);
digitalWrite(E, HIGH);
digitalWrite(F, LOW);
digitalWrite(G, HIGH);
break;
}}