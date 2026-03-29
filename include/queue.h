// airport/include/queue.h

#ifndef QUEUE_H
#define QUEUE_H

#include "plane.h"
#include "error.h"

const int maxqueue = 10; 

struct Queue_entry {
    struct Queue_entry *next;
    struct Queue_entry *prev;
};

typedef struct Queue_entry    *queue_t;
typedef struct Queue_entry    queue_head_t;
typedef struct Queue_entry    queue_chain_t;
typedef struct Queue_entry    *queue_entry_t;

class Queue {
public:
    Queue();
    bool empty() const;
    error_code serve();
    error_code append(const Plane &item);
    error_code retrieve(Plane &item);
    typedef Plane Plane_queue_entry;
protected:
    int count;
    int front, rear;
    Plane entry[maxqueue];
};

class Extended_queue: public Queue {
public:
    bool full() const;
    int size() const;
    void clear();
    error_code serve_and_retrieve(Queue_entry &item);
};

#endif