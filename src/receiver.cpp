#include "receiver.h"
#include "boardInfo.h"

ConnectionState connectionState = DISCONNECTED;

bool receivePacket(Packet &packet) {
    if (Serial.available() < 2)
        return false;
    packet.command = Serial.read();
    packet.display = Serial.read();
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
         bytes--;
     }
 }

void resolveConnection(ConnectionState connectionState) {
    switch (connectionState) {
        case DISCONNECTED:
            break;
        case HANDSHAKE: {
            bool success = Serial.read();
            serialState = SerialIdle
            if (success) { 
                connectionState = CONNECTED;
                Serial.write(static_cast<uint8_t>(1));
            }
            else {
                connectionState = DISCONNECTED;
                Serial.write(static_cast<uint8_t>(0));
            }
            break;
        }
        case CONNECTED:
                break;
    }
}

void sendHandshake() {
    Serial.write(
        reinterpret_cast<const uint8_t*>(&BOARD_INFO),
        sizeof(BOARD_INFO)
    );
    connectionState = HANDSHAKE; 
}

void checkSerialState() {
    if (serialState == SerialIdle) {
        return true;
    }
    return false;
}
