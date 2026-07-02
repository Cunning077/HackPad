#include "cmdLedger.h"
#include "display.h"
#include "receiver.h"

void resolveCMD(Command cmd) {
    switch (cmd) {
        case CMD_DRAW_IMAGE:
            Serial.println("Draw Image Requested");
            receiveImage();
            break;
        case CMD_CLEAR_DISPLAY:
            Serial.println("Clear Display Requested");
            clearDisplay();
            break;
        case CMD_DISPLAY_TEST:
            Serial.println("Display Test Requested");
            displayTest();
            break;
        case CMD_DRAW_TEXT:
            Serial.println("Draw Text Requested");

            break;
        case CMD_FILL_SCREEN:
            Serial.println("Fill Screen Requested");
            displayFillScreen();
            break;
        default:
            Serial.print("Uknown Command: ");
            Serial.println(cmd);
            break;
    }
}
