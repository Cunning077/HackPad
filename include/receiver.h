#ifndef RECEIVER_H
#define RECEIVER_H
#include <Arduino.h>

struct Packet {
    uint8_t command;
    uint8_t display;
};

enum ConnectionState {
    DISCONNECTED,
    HANDSHAKE,
    CONNECTED
};

enum SerialState {
    SerialBusy,
    SerialIdle
};
extern SerialState serialState;
extern ConnectionState connectionState;
bool receivePacket(Packet &packet);
bool waitForPayload(uint16_t length);
void flushPayload(uint16_t bytes);
void resolveConnection();
void sendHandshake();
bool checkSerialState();
#endif
