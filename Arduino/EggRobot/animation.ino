/*************************************************** 

  For Raspberry Pi Pico, connect as follows:
  Pico  - LED Backpack
  Pin 6   SDA
  Pin 7   SCL
  Pin 36  VCC
  Pin 3   GND

*****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

static const uint8_t PROGMEM
  smile[] =
  { B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 };

void animate_setup() {
  matrix.begin(0x70);  // pass in the address

  matrix.clear();
  matrix.drawBitmap(0, 0, smile, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void animate_loop() {
}