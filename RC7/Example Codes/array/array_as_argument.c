#include <stdio.h>

void foo(int arr[]);

int main() {
	int arr[] = {1, 2, 3, 4};
	foo(arr);
	printf("%d\n", arr[0]);
	return 0;
}

void foo(int arr[]) {
	arr[0] = 2;
}
