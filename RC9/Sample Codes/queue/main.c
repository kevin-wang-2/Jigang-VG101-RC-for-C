#include <stdio.h>
#include <string.h>
#include "queue.h"

int main() {
    char input[100];
    queue_t queue = NULL;
    fgets(input, 100, stdin);

    while (strcmp(input, "exit\n") != 0) {
        char *ptr = input;
        while (*ptr != ' ' && *ptr != '\n') ptr++;

        char command[100], *commandptr = command;
        int num;
        if (*ptr == '\n') {
            for (char *temp = input; temp < ptr; temp++) {
                *(commandptr++) = *temp;
            }
            *commandptr = 0;
            if (strcmp(command, "dequeue") == 0) {
                printf("elt = %d\n", dequeue(&queue));
            } else if (strcmp(command, "size") == 0) {
                printf("size = %d\n", sizeof_queue(queue));
            }
        } else {
            int operand = (int) strtol(ptr + 1, NULL, 10);
            for (char *temp = input; temp < ptr; temp++) {
                *(commandptr++) = *temp;
            }
            *commandptr = 0;
            if (strcmp(command, "enqueue") == 0) {
                queue = enqueue(queue, operand);
            }
        }
        fgets(input, 100, stdin);
    }
    free_queue(queue);
    return 0;
}