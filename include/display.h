#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include <Adafruit_GC9A01A.h>

extern Adafruit_GC9A01A tft;

void initSelPin();
void initDisplay(int displayNum);
void selectDisplay(uint8_t display);
void receiveImage();
void clearDisplay();
void displayText();
void displayTest();
void displayFillScreen();
#endif 
