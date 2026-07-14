#ifndef QUEUE_H
#define QUEUE_H
#include <Arduino.h>
#include "receiver.h"

const expr uint8_t QUEUE_SIZE = 8;

class PacketQueue {
    private:
        Packet queue[QUEUE_SIZE];
        uint8_t head;
        uint8_t tail;
        uint8_t count;

    public:
        PacketQueue();
        bool push (const Packet& packet);
        bool pop(Packet& packet);
        bool empty() const       bool full() const;
        uint8_t size() const;
};
extern PacketQueue Queue;
#endif
