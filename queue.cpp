// airport/queue.cpp

#include <iostream>
#include "include/plane.h"
#include "include/queue.h"
#include "include/error.h"

Queue::Queue() {
    count = 0;
    front = 0;
    rear = maxqueue - 1;
}

error_code Queue::serve() {
    if (count <= 0) return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

error_code Queue::append(const Plane &item) {
    if (count >= maxqueue) return overflow;
    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

error_code Queue::retrieve(Plane &item) {
    if (count <= 0) return underflow;
    item = entry[front];
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

bool Queue::empty() const {
    return count == 0;
}

bool Extended_queue::full() const {
    return count == maxqueue;
}

int Extended_queue::size() const {
    return count;
}

void Extended_queue::clear() {
    count = 0;
    front = 0;
    rear = maxqueue - 1;
}

error_code Extended_queue::serve_and_retrieve(Queue_entry &item) {
    // ...
}
