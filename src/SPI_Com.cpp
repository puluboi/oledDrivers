#include "SPI_Com.h"

void writeByte(uint8_t DATA)
{
  SPI.transfer(DATA);
}
void InitSystem(){
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_RST, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
}
//write register address and data
void writeReg(uint8_t Reg){
  OLED_DC_0;  // Set to command mode
  OLED_CS_0;  // Select chip 0(slave)
  writeByte(Reg);
  OLED_CS_1; // Stop the communication by selecting chip 1(master)
}

//Write data to slave
void writeData(uint8_t Data){
  OLED_DC_1; // Set to data transfer mode
  OLED_CS_0;  
  writeByte(Data);
  OLED_CS_1;
}

// Send a reset signal;
void Reset(void){
  OLED_RST_1;
  delay(100);
  OLED_RST_0;
  delay(100);
  OLED_RST_1;
  delay(100);
}

void InitReg(void){
  // Turn off OLED panel: 
  writeReg(0xae);

  // Set Re-Map:
  writeReg(0xa0); 
  writeReg(0x51); // Column addresses display's memory are reversed

  writeReg(0xa1); // Set display start line
  writeReg(0x00);

  writeReg(0xa2); // Set Display Offset
  writeReg(0x20); // 0-255

  writeReg(0xa4); // Normal display

  writeReg(0xa8); // Set Multiplex ratio
  writeReg(0x5f); 

  writeReg(0xab); // Enable internal VDD regulator 
  writeReg(0x01);

  writeReg(0x81); // set contrast
  writeReg(0x77); // 0-255

  writeReg(0xb1); // Set Phase Length
  writeReg(0x31);

  writeReg(0xb3); // Set front clock divider/oscillator freq
  writeReg(0xb1); // 0xb1: High refresh rate, while increased power usage; b: osc freq, 1: divide ratio(no division with 1)

  writeReg(0xb4); // For brightness enhancement? (not explained in the manual...)
  writeReg(0xb5);

  writeReg(0xb6); // Set Second pre-charge period.
  writeReg(0x0d);
  
  writeReg(0xbe); // set vcomh
  writeReg(0x07);

  writeReg(0xd5); // Enable second pre-charge
  writeReg(0x02);
}
