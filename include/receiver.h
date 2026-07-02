#ifndef RECEIVER_H
#define RECEIVER_H
#include <Arduino.h>

struct Packet {
    uint8_t command;
};

bool receivePacket(Packet &packet);
bool waitForPayload(uint16_t length);
void flushPayload(uint16_t bytes);
#endif
