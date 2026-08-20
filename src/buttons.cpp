#include "buttons.h"
#include "queue.h"
#include "debugger.h"

void readButtons() {
    int value = analogRead(A0);
    if (value >= 90 && value <= 100) {
        setColor(1,0,0);
    }
    else if (value >= 340 && value <= 360) {
        setColor(0,0,1);
    }
}
