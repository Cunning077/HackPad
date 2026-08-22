#include "buttons.h"
#include "queue.h"
#include "debugger.h"
#include "receiver.h"
#include "cmdLedger.h"

void readButtons() {
    int value = analogRead(A0);
    if (value >= 90 && value <= 100) {
        //button 0 for display 0 is pressed
        setColor(0,0,1);
        Packet packet;
        packet.command = 0x08;
        packet.cmdId = 0;
        Queue.push(packet);
    }
    else if (value >= 340 && value <= 360) {
        setColor(1,0,0);
        Packet packet;
        packet.command = 0x08;
        packet.cmdId = 2;
        Queue.push(packet);
    }
}
