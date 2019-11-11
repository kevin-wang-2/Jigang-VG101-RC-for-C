//
// A simple structure of queue
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <stdlib.h>

struct queue_typedef;
typedef struct queue_typedef *queue_t;

queue_t make_queue(int elt);

int sizeof_queue(queue_t queue);

queue_t enqueue(queue_t queue, int elt);

int dequeue(queue_t *queue);

void free_queue(queue_t queue);

#endif //QUEUE_QUEUE_H
