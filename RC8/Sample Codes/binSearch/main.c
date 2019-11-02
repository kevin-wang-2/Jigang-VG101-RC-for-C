#include <stdio.h>

int main() {
	int arr[255], length, target;
	scanf("%d", &length);
	for(int i=0;i<length;i++) scanf("%d", arr + i);
	scanf("%d", &target);

	int pivotlow = 0, pivothigh = length - 1, flag = 0;
	while(pivotlow < pivothigh) {
		int mid = (pivotlow + pivothigh) / 2;
		if(target < arr[mid]) pivothigh = mid-1;
		else if(target > arr[mid]) pivotlow = mid+1;
		else {
			printf("arr[%d]=%d;\n", mid, target);
			flag = 1;
			break;
		}
	}
	if(!flag) printf("Can't find %d in arr.\n", target);
	return 0;
}
