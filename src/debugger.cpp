#include "debugger.h"

static uint8_t LED_R;
static uint8_t LED_G;
static uint8_t LED_B;
// color map 
// red 1,0,0
// green 0,1,0
// blue 0,0,1
// yellow 1,1,0

void initDebugger(uint8_t r, uint8_t g, uint8_t b) {
    LED_R = r;
    LED_G = g;
    LED_B = b;
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void setColor(bool r, bool g, bool b) {
    digitalWrite(LED_R, r);
    digitalWrite(LED_G, g);
    digitalWrite(LED_B, b);
}
