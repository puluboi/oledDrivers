#include "canvas.hpp"

void fillCanvas(uint8_t color, uint8_t *canvas){
  for(int i = 0; i < OLED_WIDTH * OLED_HEIGHT; i++){
      canvas[i] = color;
    }
}

void meteor(uint8_t size, uint8_t speed, uint8_t start, uint8_t *canvas){
  for(int i = 0; i < OLED_WIDTH/2+size; i += speed){
      uint8_t it = i+start*OLED_WIDTH;
      for(int j = 0; j < size; j++){ // Size of the meteor
        if(i-j <= (start+1)*OLED_WIDTH/2){canvas[i-j] = 0xFF;}
      }

      for(int j = 0; j < size; j++){
        i-j - size >= 0 ? canvas[i-j-size] = 0 : canvas[OLED_WIDTH * OLED_HEIGHT] = 0; // remove the tail of the meteor
      }
      OLED_displayImg(canvas);
      delay(20);
    }
}

void drawSpinningSpiral(uint8_t *canvas) {
  float angle = 0.0;
  float radius = 0.0;
  float angleIncrement = 0.1;
  float radiusIncrement = 0.05;
  int centerX = OLED_WIDTH / 4;
  int centerY = OLED_HEIGHT / 4;

  for (int i = 0; i < 1000; i++) {
    int x = centerX + (int)(radius * cos(angle));
    int y = centerY + (int)(radius * sin(angle));

    if (x >= 0 && x < OLED_WIDTH && y >= 0 && y < OLED_HEIGHT) {
      canvas[y * OLED_WIDTH + x] = 1; // Set 0xFF if u want full brightness, 1 if dim.
    }

    angle += angleIncrement;
    radius += radiusIncrement;
    if(i%4==0){
      OLED_displayImg(canvas);
      delay(20);
  }
}}

void drawLine(int x0, int y0, int x1, int y1, uint8_t *canvas) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;

  while (true) {
    if (x0 >= 0 && x0 < OLED_WIDTH && y0 >= 0 && y0 < OLED_HEIGHT) {
      canvas[y0 * OLED_WIDTH + x0] = 0xFF;
    }
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

void drawSpinningCube(uint8_t *canvas, unsigned int timeInMS) {
  float angle = 0.0;
  float angleIncrement = 0.05;
  int centerX = OLED_WIDTH / 4;
  int centerY = OLED_HEIGHT / 4;
  int size = 20;
  int t = 0;
  while (t < timeInMS) {
    fillCanvas(0,canvas);
    //paintString5x7("CUBE", 10, 10, canvas);
    paintString3x5("California", 5, 20, canvas);
    paintString3x5("dreamin'", 5, 30, canvas);
    for (int i = 0; i < 8; i++) {
      float x = (i & 1 ? 1 : -1) * size;
      float y = (i & 2 ? 1 : -1) * size;
      float z = (i & 4 ? 1 : -1) * size;

      // Rotate around Y axis
      float tempX = x * cos(angle) - z * sin(angle);
      z = x * sin(angle) + z * cos(angle);
      x = tempX;

      // Rotate around X axis
      float tempY = y * cos(angle) - z * sin(angle);
      z = y * sin(angle) + z * cos(angle);
      y = tempY;

      // Project to 2D
      int screenX = centerX + (int)(x / (z / size + 2));
      int screenY = centerY + (int)(y / (z / size + 2));

      if (screenX >= 0 && screenX < OLED_WIDTH && screenY >= 0 && screenY < OLED_HEIGHT) {
        canvas[screenY * OLED_WIDTH + screenX] = 0xFF;
      }
    }

    // Draw edges
    for (int i = 0; i < 8; i++) {
      for (int j = i + 1; j < 8; j++) {
        if (__builtin_popcount(i ^ j) == 1) {
          float x1 = (i & 1 ? 1 : -1) * size;
          float y1 = (i & 2 ? 1 : -1) * size;
          float z1 = (i & 4 ? 1 : -1) * size;

          float x2 = (j & 1 ? 1 : -1) * size;
          float y2 = (j & 2 ? 1 : -1) * size;
          float z2 = (j & 4 ? 1 : -1) * size;

          // Rotate around Y axis
          float tempX1 = x1 * cos(angle) - z1 * sin(angle);
          z1 = x1 * sin(angle) + z1 * cos(angle);
          x1 = tempX1;

          float tempX2 = x2 * cos(angle) - z2 * sin(angle);
          z2 = x2 * sin(angle) + z2 * cos(angle);
          x2 = tempX2;

          // Rotate around X axis
          float tempY1 = y1 * cos(angle) - z1 * sin(angle);
          z1 = y1 * sin(angle) + z1 * cos(angle);
          y1 = tempY1;

          float tempY2 = y2 * cos(angle) - z2 * sin(angle);
          z2 = y2 * sin(angle) + z2 * cos(angle);
          y2 = tempY2;

          // Project to 2D
          int screenX1 = centerX + (int)(x1 / (z1 / size + 2));
          int screenY1 = centerY + (int)(y1 / (z1 / size + 2));

          int screenX2 = centerX + (int)(x2 / (z2 / size + 2));
          int screenY2 = centerY + (int)(y2 / (z2 / size + 2));

          drawLine(screenX1, screenY1, screenX2, screenY2, canvas);
        }
      }
    }
    
    OLED_displayImg(canvas);
    angle += angleIncrement;
    delay(50);
    t += 50;
    Serial.println(t);
  }
}

// Function to paint a character on the canvas using 5x7 font
void paintChar5x7(char c, int x, int y, uint8_t *canvas) {    
    // Get the font data for the character
    const uint8_t* charData = font5x7[c - 32];

    // Paint the character on the canvas
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (charData[i] & (1 << j)) {
                canvas[(x + i) + (y + j) * 128] = 0xFF; // Set pixel to bright
            } else {
                canvas[(x + i) + (y + j) * 128] = 0; // Clear pixel
            }
        }
    }
}

// Function to paint a character on the canvas using 3x5 font
void paintChar3x5(char c, int x, int y, uint8_t *canvas) {    
    // Get the font data for the character
    const uint8_t* charData = font3x5[c - 32];

    // Paint the character on the canvas
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (charData[i] & (1 << j)) {
                canvas[(x + i) + (y + j) * 128] = 0xFF; // Set pixel to bright
            } else {
                canvas[(x + i) + (y + j) * 128] = 0; // Clear pixel
            }
        }
    }
}

// Function to paint a string on the canvas using 5x7 font
void paintString5x7(const char* str, int x, int y, uint8_t *canvas) {
    int offsetX = 0;
    while (*str) {
        paintChar5x7(*str, x + offsetX, y, canvas);
        offsetX += 6; // Move to the next character position (5 pixels for character + 1 pixel space)
        str++;
    }
}

// Function to paint a string on the canvas using 3x5 font
void paintString3x5(const char* str, int x, int y, uint8_t *canvas) {
    int offsetX = 0;
    while (*str) {
        paintChar3x5(*str, x + offsetX, y, canvas);
        offsetX += 4; // Move to the next character position (3 pixels for character + 1 pixel space)
        str++;
    }
}