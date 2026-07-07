#ifndef CMDLEDGER_H
#define CMDLEDGER_H
#include <Arduino.h>


enum Command : uint8_t {
    CMD_DRAW_IMAGE = 0x01,
    CMD_CLEAR_DISPLAY = 0x02,
    CMD_DISPLAY_TEST = 0x03,
    CMD_DRAW_TEXT = 0x04,
    CMD_FILL_SCREEN = 0x05
};

void resolveCMD(Command cmd, uint8_t display);
#endif

