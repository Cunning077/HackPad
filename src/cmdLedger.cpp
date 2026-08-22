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
            serialState = SerialIdle;
            break;
        case CMD_CLEAR_DISPLAY:
            serialState = SerialBusy;
            Serial.write(0x04);
            Serial.write(cmdId);
            clearDisplay();
            Serial.write(0x04);
            serialState = SerialIdle;
            break;
        case CMD_DISPLAY_TEST:
            serialState = SerialBusy;
            Serial.write(0x05);
            Serial.write(cmdId);
            displayTest();
            Serial.write(0x05);
            serialState = SerialIdle;
            break;
        case CMD_DRAW_TEXT:
            serialState = SerialBusy;
            Serial.write(0x06);
            Serial.write(cmdId);
            displayText(); 
            Serial.write(0x06);
            serialState = SerialIdle;
            break;
        case CMD_FILL_SCREEN:
            serialState = SerialBusy;
            Serial.write(0x07);
            Serial.write(cmdId);
            displayFillScreen();
            Serial.write(0x07);
            serialState = SerialIdle;
            break;
        case CMD_BTN_PRESS: {
            setColor(1,1,0);
            serialState = SerialBusy;
            Serial.write(0x08);
            Serial.write(cmdId);
            delay(1);
            if (!waitForPayload(1)) {
                setColor(1,1,0);
                delay(2000);
                return;
            }
            uint8_t resp = Serial.read();
            if (resp != CMD_BTN_PRESS) {
                setColor(0,1,0);
            }
            serialState = SerialIdle;
        }
        default:
            break;
    }
}
