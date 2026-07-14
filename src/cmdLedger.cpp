#include "cmdLedger.h"
#include "display.h"
#include "receiver.h"


void resolveCMD(uint8_t cmd, uint8_t display) {
    switch (cmd) {
        case CMD_DRAW_IMAGE:
            serialState = SerialBusy;
            Serial.write(0x03)
            receiveImage(display);
            break;
        case CMD_CLEAR_DISPLAY:
            serialState = SerialBusy;
            Serial.write(0x04)
            clearDisplay(display);
            break;
        case CMD_DISPLAY_TEST:
            serialState = SerialBusy;
            Serial.write(0x05)
            displayTest(display);
            break;
        case CMD_DRAW_TEXT:
            serialState = SerialBusy;
            Serial.write(0x06)
            displayText(display); 
            break;
        case CMD_FILL_SCREEN:
            serialState = SerialBusy;
            Serial.write(0x07)
            displayFillScreen(display);
            break;
        default:
            Serial.println(cmd);
            break;
    }
}
