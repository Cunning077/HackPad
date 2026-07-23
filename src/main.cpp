#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GC9A01A.h>
#include "display.h"
#include "cmdLedger.h"
#include "receiver.h"
#include "debugger.h"
#include "queue.h"


#define TFT_DC 9
#define TFT_RST -1
#define TFT_CS 10
#define LED_R 4
#define LED_G 3
#define LED_B 2

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
   Serial.begin(115200);
   initDebugger(LED_R, LED_G, LED_B);
   initSelPin();
   initDisplay(1);
   initDisplay(0);
}

void loop() {
    resolveConnection();


    Packet packet;
    if (receivePacket(packet)) {
        switch (packet.command) {
            case CMD_HANDSHAKE:
                serialState = SerialBusy;
                sendHandshake();
                return;

        }
        if (connectionState == CONNECTED) {
            Queue.push(packet);
            delay(1);
        }
    }

    if (connectionState == CONNECTED) {
        if (!Queue.empty()) {
            if (Queue.pop(packet)) {
                resolveCMD(packet.command, packet.display);
            }
        }
    }
}
