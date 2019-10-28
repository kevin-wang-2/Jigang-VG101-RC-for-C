#include <stdio.h>

int nums[1000] = {0};
int cntNums = 0;
int stack[100] = {0}; // Stores the index of numbers
int top = 0;
int result[100] = {0};
int resultTop = 0;

void dfsHelper(int);

int main() {
	scanf("%d", &cntNums);
	
	int target;
	scanf("%d", &target);

	for(int i=0;i<cntNums;i++) {
		scanf("%d", &nums[i]); // This could also be written as nums + i
	}
	
	dfsHelper(target);

	for(int i=0;i<resultTop;i++) {
		printf("%d ", nums[result[i]]);
	}
	printf("\n");
	return 0;
}

void dfsHelper(int target) {
	if(target == 0) { // Recursion end condition
		if((resultTop == 0) || (top < resultTop) || (stack[top - 1] < result[resultTop - 1])) {
			for(int i=0;i<top;i++) { // Copy the array, can be replaced by memcpy
				result[i] = stack[i];
			}
			resultTop = top;
		}
	}

	for(int i=stack[top - 1];i<cntNums;i++) {
		if((nums[i] > target) || ((resultTop != 0) && (top >= resultTop))) break; // Branch Cutoff
		stack[top++] = i; // Push Stack
		dfsHelper(target - nums[i]);
		top--; // Pop
	}
}
