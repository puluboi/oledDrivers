#include "OLED_Driver.h"
void OLED_init(void){
  //Reset signal
  Reset();

  //Run the init commands to the screen.
  InitReg();
  delay(200);
  //Turn the screen on.
  writeReg(0xAF);
}

void OLED_setWindow(uint8_t xstart, uint8_t ystart, uint8_t xend, uint8_t yend){
  if((xstart>OLED_WIDTH) || (ystart > OLED_HEIGHT) || (xend > OLED_WIDTH) || (yend > OLED_HEIGHT)){
    return;
  }
  writeReg(0x15); // Start the updating of columns
  writeReg(xstart/2); // divide by 2 because of pixel depth.
  writeReg(xend/2-1);

  writeReg(0x75); // Start updating the rows-
  writeReg(ystart/2);
  writeReg(yend-1);
}

void OLED_displayImg(const uint8_t *img){
  uint16_t i, j, temp;
  OLED_setWindow(0,0, OLED_WIDTH, OLED_HEIGHT); // Set the window to fullscreen.
  for(i=0; i<OLED_HEIGHT; i++){     // go through all the rows
    for(j=0; j<OLED_WIDTH/2; j++)   // go through each of the pixels in each row
    {
      temp = pgm_read_byte(&img[j + i*OLED_WIDTH/2]);
      writeData(temp);
    }
  }
}

void OLED_displayPartialImg(const uint8_t *img, uint8_t xstart, uint8_t ystart, uint8_t xend, uint8_t yend){
  uint16_t i, j, temp;
  OLED_setWindow(0,0, OLED_WIDTH, OLED_HEIGHT);
  for(i=0; i<OLED_HEIGHT; i++){
    for(j=0; j<OLED_WIDTH; j++){
      temp = img[j+i*(xend-xstart)/2];
      writeData(temp);
    }
  }
}


void OLED_clear(uint8_t color){
  uint16_t i;
  OLED_setWindow(0,0, OLED_WIDTH, OLED_HEIGHT);
  for(i=0; i<OLED_WIDTH*OLED_HEIGHT/2; i++){
    writeData(color | (color << 2) | (color << 4) | (color << 6));
  }
}
