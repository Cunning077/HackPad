#include "receiver.h"

bool receivePacket(Packet &packet) {
    if (Serial.available() < 3)
        return false;
    packet.command = Serial.read();
    Serial.println("Packet Detected");
    return true;
}

bool waitForPayload(uint16_t length) {
    unsigned long start = millis();
    while (Serial.available() < length) {
        if (millis() - start > 1000) {
            Serial.println("Timeout");
            return false;
        }
    }
    return true;
}
 void flushPayload(uint16_t bytes) {
     while (bytes > 0) {
         if (!waitForPayload(1))
             return;
         Serial.read();
         bytes--;
     }
 }
