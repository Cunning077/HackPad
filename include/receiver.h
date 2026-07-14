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

enum serialState {
    SerialBusy,
    SerialIdle
};
SerialState serialState = SerialIdle;
extern ConnectionState connectionState;
bool receivePacket(Packet &packet);
bool waitForPayload(uint16_t length);
void flushPayload(uint16_t bytes);
void resolveConnection(ConnectionState connectionState);
void sendHandshake();
void checkSerialState();
#endif
