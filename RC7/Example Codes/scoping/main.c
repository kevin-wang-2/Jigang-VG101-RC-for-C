#include <stdio.h>

int main() {
	int *p;
	{
		int arr[] = {1, 2, 3, 4};
		p = arr;
	}
	int arr2[] = {3, 4, 5, 6};
	printf("%d", p[1]);
	return 0;
}
