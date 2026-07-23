#include <display.h>
#include <Arduino.h>
#include "receiver.h"
#include "debugger.h"

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

void receiveImage(uint8_t display) {
    delay(100);
    if (!waitForPayload(3)) {
        return;
    }
    uint8_t width = Serial.read();
    uint8_t height = Serial.read();
    uint8_t rotation = Serial.read();
    uint32_t expectedPixels = (uint32_t)width * height;
    uint32_t bytesToRead = expectedPixels * 2;
    selectDisplay(display);  
    int16_t x = (240 - width) / 2;
    int16_t y = (240 - height) / 2;
    tft.setRotation(rotation);
    tft.startWrite();
    tft.setAddrWindow(x, y, width, height);
    uint8_t buffer[48];
    uint32_t bytesConsumed = 0;
    while (bytesToRead > 0) {
        uint16_t chunk = min(bytesToRead, sizeof(buffer));
        if (!waitForPayload(chunk)) {
            Serial.println("Bytes Left");
            Serial.println(bytesToRead);
            flushPayload(bytesToRead);
            tft.endWrite();
            return;
        }
        Serial.readBytes((char*)buffer, chunk);
        for (uint16_t i = 0; i < chunk; i +=2) {
            uint16_t pixel = (buffer[i] << 8) | buffer[i + 1];
            bytesConsumed += 2;
            tft.writeColor(pixel, 1);
        }
        bytesToRead -= chunk;
    }
    tft.endWrite();
    setColor(1,1,1);
    if (bytesConsumed == expectedPixels * 2) {
        setColor(0,1,0);
    }


}

void clearDisplay(uint8_t display) {
    Serial.print("Display: ");
    Serial.println(display);
    selectDisplay(display);
    tft.fillScreen(GC9A01A_BLACK);
}

void displayText(uint8_t display) {
    Serial.println("Attempting Text");
    if (!waitForPayload(3))
        return;   
    Serial.println("Payload Received");
    uint8_t x = Serial.read();
    uint8_t y = Serial.read();
    uint16_t textLength = Serial.read();
    Serial.println("display:");
    Serial.println(display);
    Serial.println("x:");
    Serial.println(x);
    Serial.println("y:");
    Serial.println(y);
    Serial.println("Text Length");
    Serial.println(textLength);
    char text[128];
    if (textLength >= sizeof(text))
        textLength = sizeof(text) - 1;
    if (!waitForPayload(textLength)) {
        Serial.println("Text failed to retrieve");
        flushPayload(textLength);
        return;
    }
    Serial.readBytes(text, textLength);
    text[textLength] = '\0';
    selectDisplay(display);
    Serial.println(text);
    tft.setTextColor(GC9A01A_WHITE);
    tft.setCursor(x, y);
    tft.setTextSize(2);
    tft.print(text);
}


void displayTest(uint8_t display) {
    setColor(1,1,1);
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

void displayFillScreen(uint8_t display) {
    if (!waitForPayload(2))
        return;
    uint16_t color = (Serial.read() << 8);
    color |= Serial.read();
    selectDisplay(display);
    tft.fillScreen(color);
}
