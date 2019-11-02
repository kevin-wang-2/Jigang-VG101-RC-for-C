#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int length);
void sortHelper(int arr[], int L, int R);
void merge(int arr[], int L, int mid, int R);

int main() {
	int arr[255], length;
	scanf("%d", &length);
	for(int i=0;i<length;i++) scanf("%d", arr + i);
	sort(arr, length);
	for(int i=0;i<length;i++) printf("%d ", arr[i]);
	putchar('\n');
	return 0;
}

void sort(int arr[], int length) {
	sortHelper(arr, 0, length - 1);
}

void sortHelper(int arr[], int L, int R) {
	if(L == R) return;
	int mid = L +((R - L) >> 1); // x >> 1 is (int)(x/2)
	sortHelper(arr, L, mid);
	sortHelper(arr, mid + 1, R);
	merge(arr, L, mid, R);
}

void merge(int arr[], int L, int mid, int R) {
	int *temp = (int *)malloc(sizeof(int) * (R - L + 1));
	int temptop = 0;
	int p1 = L, p2 = mid+1;
	while((p1 <= mid) && (p2 <= R)) {
		if(arr[p1] < arr[p2]) {
			temp[temptop++] = arr[p1++];
		} else {
			temp[temptop++] = arr[p2++];
		}
	}
	while(p1 <= mid) temp[temptop++] = arr[p1++];
	while(p2 <= R) temp[temptop++] = arr[p2++];
	for(int i=0;i<R-L+1;i++) arr[L+i] = temp[i];
	free(temp);
}
