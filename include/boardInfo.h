#ifndef BOARDINFO_H
#define BOARDINFO_H
#include <Arduino.h>

struct BoardInfo {
    char magic[4];
    uint8_t protocolVersion;
    uint8_t firmwareMajor;
    uint8_t firmwareMinor;
    uint8_t displayCount;
    uint8_t buttonCount;
};
extern const BoardInfo BOARD_INFO;
#endif
