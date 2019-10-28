#include <stdio.h>

int foo(int arr[]);

int main() {
	int i= 5;
	int arr[] = {1, 2, 3, 4};
	foo(arr);
	printf("%d\n", i);
	return 0;
}

int foo(int arr[]) {
	arr[-1] = 6;
}
