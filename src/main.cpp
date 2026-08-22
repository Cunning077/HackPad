#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GC9A01A.h>
#include "display.h"
#include "cmdLedger.h"
#include "receiver.h"
#include "debugger.h"
#include "queue.h"
#include "buttons.h"


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
   initDisplay(2);
   initDisplay(0);
}

void loop() {
    readButtons();
    resolveConnection();
    readButtons();


    Packet packet;
    if (receivePacket(packet)) {
        switch (packet.command) {
            case CMD_HANDSHAKE:
                serialState = SerialBusy;
                readButtons();
                sendHandshake();
                return;

        }
        if (connectionState == CONNECTED) {
            setColor(1,1,0);
            Queue.push(packet);
            Serial.write(packet.command);
            readButtons();
            delay(1);
        }
    }

    if (connectionState == CONNECTED) {
        if (!Queue.empty()) {
            if (Queue.pop(packet)) {
                readButtons();
                resolveCMD(packet.command, packet.cmdId);
            }
        }
    }
}
