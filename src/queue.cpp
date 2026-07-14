#include "queue.h"

PacketQueue Queue;

PacketQueue::PacketQueue() {
    head = 0;
    tail = 0;
    count = 0;
}

bool PacketQueue::push(const Packet& packet) {
    if (count == QUEUE_SIZE)
        return false;

    queue[tail] = packet;
    tail = (tail + 1) % QUEUE_SIZE;
    count++;
    return true;
}

bool PacketQueue::pop(Packet& packet) {
    if (count == 0)
        return false;

    packet = queue[head];
    head = (head + 1) % QUEUE_SIZE;
    count--;
    return true;
}

bool PacketQueue::empty() const {
    return count == 0;
}

bool PacketQueue::full() const {
    return count == QUEUE_SIZE;
}

uint8_t PacketQueue::size() const {
    return count;
}
