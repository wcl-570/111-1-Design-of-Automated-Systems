#include "Wire.h"
#include "LiquidCrystal_I2C.h"

//set 7-Seg pins
const int A = 3;
const int B = 4;
const int C = 5;
const int D = 6;
const int E = 7;
const int F = 9;
const int G = 8;
//set button1 signal as false
bool Bpress = false; 
//set Button1(UpPin) pin
int UpPin = 10; 
//set Button2(CheckPin) pin
int CheckPin = 11; 
//set variable int as initial value
int num = 0; 
int ButtonUp = 0;
int LastButtonUp =0;
int ButtonCheck = 0;
int LastButtonCheck =0;
//set LCD I2C communication
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  // Set LCD display interface size
  lcd.begin(); 
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(UpPin,INPUT_PULLUP);
}

void loop() {
  //set ButtonUp(該按鈕為數字切換紐)
  ButtonUp = digitalRead(UpPin);
  //set ButtonCheck (該按鈕為數字確認紐)
  ButtonCheck = digitalRead(CheckPin);
  if(ButtonUp != LastButtonUp) {
    //if ButtonUp為低電位
    if(ButtonUp == LOW) {
      //set button1 signal as true
      Bpress = true; 
      //按鈕次數疊加
      num++; 
      //如果次數大於3，則回到0
      if(num >= 3) {
        num = 0;
      }
      //觸發函式ChangeNum()
      ChangeNum(num); 
      delay(50);
    }
  }
  //if ButtonCheck為高電位
  //若確認該數字則會顯示指定名稱及數值
  if(ButtonCheck == HIGH) {
    //如果num=0，則LCD顯示yaw值
    if(num == 0) {
      //清除LCD顯示文字
      lcd.clear(); 
      //顯示第一列文字
      lcd.setCursor(0,0); 
      lcd.print("MPU6050");
      lcd.setCursor(0,1);
      lcd.print("The yaw angle:");
      lcd.setCursor(0,2);
      lcd.print("yaw");
    }
    //如果num=1，則LCD顯示pitch值
    if(num == 1) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MPU6050");
      lcd.setCursor(0,1);
      lcd.print("The pitch angle:");
      lcd.setCursor(0,2);
      lcd.print("pitch");
    }
    //如果num=2，則LCD顯示roll值
    if(num == 2) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MPU6050");
      lcd.setCursor(0,1);
      lcd.print("The roll angle:");
      lcd.setCursor(0,2);
      lcd.print("roll");
    }
  }
}

//函式ChangeNum()
void ChangeNum(int button1) {
  switch (button1) {
  //當button 1=0，7-Seg.顯示0
  case 0: 
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
    break;
  //當button 1=1，7-Seg.顯示1
  case 1: 
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    break;
  //當button 1=2，7-Seg.顯示2
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
