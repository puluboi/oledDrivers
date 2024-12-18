
#include "eero.c"
#include "OLED_Driver.h"
#include "SPI_Com.h"
#include "canvas.hpp"

uint8_t *canvas;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  InitSystem();
  OLED_init();
  uint16_t canvasSize = ((OLED_WIDTH%2==0)? (OLED_WIDTH/2): (OLED_WIDTH/2 + 1)) * OLED_HEIGHT;
  if((canvas = (uint8_t *)malloc(canvasSize/8))==NULL){  // Memory check
    Serial.println("Not enough memory for canvas...");
    return;
  }
  delay(500);
  fillCanvas(0,canvas);
}

void loop() {
  // put your main code here, to run repeatedly:
  OLED_displayImg(gImage_eero);
  delay(1000);
  OLED_clear(0);
  delay(1000);
  OLED_clear(255);
  delay(1000);
  OLED_clear(0);
  delay(1000);
  meteor(6, 6, 48,canvas);
  
  fillCanvas(0,canvas);
  drawSpinningCube(canvas);
  fillCanvas(0,canvas);
}




