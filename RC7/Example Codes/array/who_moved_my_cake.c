// Cite VE280 RC6
#include <stdio.h>

int setFirst(int x[][5], int size) {
	int cheese = 0;
	while (size >= 0) x[--size][0] = size;
	printf("%d\n", cheese);
}

int main() {
	int arr[10][5] = {0};
	setFirst(arr, 10);
}
