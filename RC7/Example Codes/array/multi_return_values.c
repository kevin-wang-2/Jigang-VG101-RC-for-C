#include <stdio.h>

void foo(int arr[]);

int main() {
	int arr[2];
	foo(arr);
	printf("%d, %d\n", arr[0], arr[1]);
	return 0;
}

void foo(int arr[]) {
	scanf("%d %d",arr, arr+1);
}
