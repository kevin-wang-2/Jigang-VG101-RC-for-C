//
// An implementation of queue
//

#include "queue.h"

// We put this in C file because we don’t want others to reach this
typedef struct queueNode_typedef {
    int data;
    struct queueNode_typedef *next;
} queueNode_t;

queue_t make_queue(int elt) {
    queueNode_t *node = (queueNode_t *) malloc(sizeof(queueNode_t));
    node->data = elt;
    node->next = NULL;
    return (queue_t) node;
}

int sizeof_queue(queue_t queue) {
    queueNode_t *head = (queueNode_t *) queue;
    int ret = 0;
    while (head != NULL) {
        ret++;
        head = head->next;
    }
    return ret;
}

queue_t enqueue(queue_t queue, int elt) {
    queueNode_t *head = (queueNode_t *) queue;
    if (head == NULL) return make_queue(elt);
    while (head->next != NULL) head = head->next;
    head->next = (queueNode_t *) malloc(sizeof(queueNode_t));
    head = head->next;
    head->data = elt;
    head->next = NULL;
    return queue;
}

int dequeue(queue_t *queue) {
    queueNode_t *head = (queueNode_t *) (*queue);
    int ret = head->data;
    *queue = (queue_t) (head->next);
    free(head);
    return ret;
}

void free_queue(queue_t queue) {
    queueNode_t *head = (queueNode_t *) queue;
    while (head != NULL) {
        queueNode_t *temp = head;
        head = head->next;
        free(temp);
    }
}
