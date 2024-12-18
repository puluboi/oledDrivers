#pragma once
#include "OLED_Driver.h"

void drawSpinningSpiral(uint8_t *canvas);
void meteor(uint8_t size, uint8_t speed, uint8_t start, uint8_t *canvas);
void fillCanvas(uint8_t color, uint8_t *canvas);
void drawLine(int x0, int y0, int x1, int y1, uint8_t *canvas);
void drawSpinningCube(uint8_t *canvas);
