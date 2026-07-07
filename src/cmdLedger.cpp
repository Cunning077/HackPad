#include "cmdLedger.h"
#include "display.h"


void resolveCMD(Command cmd, uint8_t display) {
    switch (cmd) {
        case CMD_DRAW_IMAGE:
            Serial.println("Draw Image Requested");
            receiveImage(display);
            break;
        case CMD_CLEAR_DISPLAY:
            Serial.println("Clear Display Requested");
            clearDisplay(display);
            break;
        case CMD_DISPLAY_TEST:
            Serial.println("Display Test Requested");
            displayTest(display);
            break;
        case CMD_DRAW_TEXT:
            Serial.println("Draw Text Requested");
            displayText(display); 
            break;
        case CMD_FILL_SCREEN:
            Serial.println("Fill Screen Requested");
            displayFillScreen(display);
            break;
        default:
            Serial.print("Uknown Command: ");
            Serial.println(cmd);
            break;
    }
}
