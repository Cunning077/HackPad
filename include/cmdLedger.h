#ifndef CMDLEDGER_H
#define CMDLEDGER_H
#include <Arduino.h>


enum Command : uint8_t {
    CMD_HANDSHAKE = 0x00,
    CMD_HANDSHAKE_ACK = 0x01,
    CMD_HEARTBEAT = 0x02,
    CMD_DRAW_IMAGE = 0x03,
    CMD_CLEAR_DISPLAY = 0x04,
    CMD_DISPLAY_TEST = 0x05,
    CMD_DRAW_TEXT = 0x06,
    CMD_FILL_SCREEN = 0x07
};

void resolveCMD(uint8_t cmd, uint8_t display);
#endif

