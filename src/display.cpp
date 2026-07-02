#include <display.h>
#include <Arduino.h>
#include "receiver.h"

#define SEL_A 7
#define SEL_B 6
#define SEL_C 5

void initSelPin() {
    pinMode(SEL_A, OUTPUT);
    pinMode(SEL_B, OUTPUT);
    pinMode(SEL_C, OUTPUT);
}

void initDisplay(int displayNum) {
    selectDisplay(displayNum);
    tft.begin();
    tft.setRotation(1);
}

void selectDisplay(uint8_t display) {
    digitalWrite(SEL_A, display & 0x01);
    digitalWrite(SEL_B, (display >> 1) & 0x01);
    digitalWrite(SEL_C, (display >> 2) & 0x01);
    delay(1);
}

void receiveImage() {
    if (!waitForPayload(3)) {
        Serial.println("Flushing Payload");

        return;
    }
    uint8_t display = Serial.read();
    uint8_t width = Serial.read();
    uint8_t height = Serial.read();
    Serial.print("Display: ");
    Serial.print(display);
    Serial.print(" Width: ");
    Serial.print(width);
    Serial.print(" Height: ");
    Serial.println(height);
    uint32_t expectedPixels = (uint32_t)width * height;
    uint16_t bytesToRead = expectedPixels;
    Serial.println(expectedPixels);
    selectDisplay(display);
    int16_t x = (240 - width) / 2;
    int16_t y = (240 - height) / 2;
    Serial.println("X");
    Serial.println(x);
    Serial.println("Y");
    Serial.println(y);
    tft.setRotation(0);
    tft.startWrite();
    tft.setAddrWindow(x, y, width, height);
    uint32_t bytesRead = 0;
    for (uint32_t i = 0; i < expectedPixels; i++) {
        if (!waitForPayload(2)) {
            Serial.println("Pixels Failed To Retrieve");
            Serial.println("Bytes Read");
            Serial.println(bytesRead);
            flushPayload(bytesToRead * 2);
            tft.endWrite();
            return;
        }
        uint8_t hi = Serial.read();
        bytesRead++;
        uint8_t lo = Serial.read();
        bytesRead++;
        uint16_t pixel = (hi << 8) | lo;
        tft.writeColor(pixel, 1);
        bytesToRead--;
    }
    Serial.print("Bytes To Read");
    Serial.println(bytesToRead);
    tft.endWrite();
}

void clearDisplay() {
    if (!waitForPayload(1))
        return;
    uint8_t display = Serial.read();
    Serial.print("Display: ");
    Serial.println(display);
    selectDisplay(display);
    tft.fillScreen(GC9A01A_BLACK);
}
/*
void displayText() {
    if (!waitForPayload(length))
        return;   
    uint8_t display = Serial.read();
    uint8_t x = Serial.read();
    uint8_t y = Serial.read();
    uint16_t textLength = length - 3;
    char text[128];
    if (textLength >= sizeof(text))
        textLength = sizeof(text) - 1;
    Serial.readBytes(text, textLength);
    text[textLength] = '\0';
    selectDisplay(display);
    tft.setCursor(x, y);
    tft.print(text);
}
*/

void displayTest() {
    if (!waitForPayload(1))
        return;
    uint8_t display = Serial.read();
    selectDisplay(display);
    for (int i = 0; i < 5; i++) {
        tft.fillScreen(GC9A01A_RED);
        tft.setTextColor(GC9A01A_WHITE);
        delay(1000);
        tft.fillScreen(GC9A01A_BLUE);
        delay(1000);
        tft.fillScreen(GC9A01A_GREEN);
        delay(1000);
        tft.fillScreen(GC9A01A_YELLOW);
        delay(1000);
    }
    
}

void displayFillScreen() {
    if (!waitForPayload(3))
        return;
    uint8_t display = Serial.read();
    uint16_t color = (Serial.read() << 8);
    color |= Serial.read();
    selectDisplay(display);
    tft.fillScreen(color);
}
