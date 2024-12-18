#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H
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

//Define the dimensions of the screen-

#define OLED_WIDTH  128//OLED width
#define OLED_HEIGHT 96 //OLED height

#include "SPI_Com.h"
#include <Arduino.h>

void OLED_init();

void OLED_setWindow(uint8_t xstart, uint8_t ystart, uint8_t xend, uint8_t yend);

void OLED_displayImg(const uint8_t *img);

void OLED_displayPartialImg(const uint8_t *img, uint8_t xstart, uint8_t ystart, uint8_t xend, uint8_t yend);

void OLED_clear(uint8_t color);

#endif
