#ifndef SPI_COM_H
#define SPI_COM_H
#include <SPI.h>
#include <Arduino.h>

//Define the Rest bits.
#define OLED_RST 13
#define OLED_CS_0     digitalWrite(OLED_CS, LOW)
#define OLED_CS_1     digitalWrite(OLED_CS, HIGH)

//define the chip select bits.
#define OLED_CS 10
#define OLED_RST_0    digitalWrite(OLED_RST, LOW)
#define OLED_RST_1    digitalWrite(OLED_RST, HIGH)

//define the data command bits
#define OLED_DC 9
#define OLED_DC_0     digitalWrite(OLED_DC, LOW)
#define OLED_DC_1     digitalWrite(OLED_DC, HIGH)

void writeByte(uint8_t DATA);

void InitSystem();

void writeReg(uint8_t Reg);

void writeData(uint8_t Data);

void Reset(void);

void InitReg(void);

#endif