#include <SPI.h>

const int chipSelectPin = 4; 
byte dataByte;

void setup() {
  Serial.begin(9600);
  SPI.begin(); //initializes the SPI
  pinMode(chipSelectPin, OUTPUT); //pin for selecting the slave. Multiple slaves -> multiple pins 
  digitalWrite(chipSelectPin, HIGH); //deselects the slave. Chip select pin is usually inverted
}

void loop() {
  digitalWrite(chipSelectPin, LOW); //selects the slave 
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); //starts communication 
  //using the given settings. SPI clock speed, bit order and SPI mode.
  SPI.transfer(1 << 7 | 0 << 6 | 0x12); //example command for reading data from a register 
  //a byte formed form = (ReadBit MultipleReadBit 6-BitRegisterAddress)
  dataByte = SPI.transfer(0b00); //returned data is saved to a variable. Master sends nothing 
  Serial.println(dataByte); //prints the data
  SPI.endTransaction(); //ends communication
  digitalWrite(chipSelectPin, HIGH); //deselects the slave
}