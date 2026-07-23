#include "receiver.h"
#include "boardInfo.h"
#include "debugger.h"
#include "cmdLedger.h"

ConnectionState connectionState = DISCONNECTED;
SerialState serialState = SerialIdle; 

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
        if (millis() - start > 5000) {
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

void resolveConnection() {
    switch (connectionState) {
        case DISCONNECTED:
            break;
        case HANDSHAKE: {
            if (!waitForPayload(1)) {
                return;
            } 
            bool success = Serial.read();
            serialState = SerialIdle;
            if (success) { 
                connectionState = CONNECTED;
                Serial.write(CMD_HANDSHAKE_ACK);
            }
            else {
                connectionState = DISCONNECTED;
                Serial.write(CMD_HANDSHAKE_ACK);
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

bool checkSerialState() {
    if (serialState == SerialIdle) {

        return true;
    }

    return false;
}
