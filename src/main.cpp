#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GC9A01A.h>
#include "display.h"
#include "cmdLedger.h"
#include "receiver.h"
#include "queue.h"

#define TFT_DC 9
#define TFT_RST -1
#define TFT_CS 10

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
   Serial.begin(115200);
   initDisplay(2);
}

void loop() {
    Packet packet;
    if (!receivePacket(packet))
        return;
    if (packet.command == CMD_HANDSHAKE) {
        serialState = SerialBusy;
        sendHandshake();
        return;
    }
    resolveConnection(connectionState);
    if (connectionState == CONNECTED) {
        if (!checkSerialState) {
            Queue.push(packet)
        }
        if (!Queue.empty()) {
            if (Queue.pop(packet)) {
                resolveCMD(packet.empty, packet.display);
            }
        }
    }
    //Final section here to flush full serial 
}
