#include "queue.h"

void enqueue(int queue[], int top, int elt) {queue[top++] = elt;}

int dequeue(int queue[], int top) {
	int ret = queue[0];
	for(int i=0;i<top - 1;i++) {
		queue[i] = queue[i+1];
	}
	top--;
	return ret;
}
