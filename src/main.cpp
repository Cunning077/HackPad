#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GC9A01A.h>
#include "display.h"
#include "cmdLedger.h"
#include "receiver.h"

#define TFT_DC 9
#define TFT_RST -1
#define TFT_CS 10

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
   Serial.begin(115200);
   initSelPin();
   initDisplay(0);
   initDisplay(2);
}

void loop() {
    Packet packet;
    if (!receivePacket(packet))
        return;
   resolveCMD(static_cast<Command>(packet.command), packet.display); 
}
