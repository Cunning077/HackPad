#include "cmdLedger.h"
#include "display.h"
#include "receiver.h"
#include "debugger.h"


void resolveCMD(uint8_t cmd, uint8_t cmdId) { 
    switch (cmd) {
        case CMD_DRAW_IMAGE:
            serialState = SerialBusy;
            Serial.write(0x03);
            Serial.write(cmdId);
            receiveImage();
            Serial.write(0x03);
            break;
        case CMD_CLEAR_DISPLAY:
            serialState = SerialBusy;
            Serial.write(0x04);
            Serial.write(cmdId);
            clearDisplay();
            Serial.write(0x04);
            break;
        case CMD_DISPLAY_TEST:
            serialState = SerialBusy;
            Serial.write(0x05);
            Serial.write(cmdId);
            displayTest();
            Serial.write(0x05);
            break;
        case CMD_DRAW_TEXT:
            serialState = SerialBusy;
            Serial.write(0x06);
            Serial.write(cmdId);
            displayText(); 
            Serial.write(0x06);
            break;
        case CMD_FILL_SCREEN:
            serialState = SerialBusy;
            Serial.write(0x07);
            Serial.write(cmdId);
            displayFillScreen();
            Serial.write(0x07);
            break;
        default:
            break;
    }
}
