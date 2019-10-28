#include <stdio.h>
#include <math.h>

int getDigitCount(int);

int main() {
	int x; // The number to process
	scanf("%d", &x); // Input
	if(x == 0) { printf("0 \n"); } // Process Boundary cases
	else {
		while(x > 0) { // Start to process a number
			int curNumber = x;
			int sum = 0, i = 0, digitCnt = getDigitCount(curNumber);
			while(curNumber > 0) {
				sum += pow(curNumber % 10, digitCnt - i);
				i++;
				curNumber /= 10;
				if(sum > x) continue;
			}
			if(sum == x) { printf("%d ", x); }
			x--;
		}
		printf("0 ");
		printf("\n");
	}
	return 0;
}

int getDigitCount(int x) {
	// REQUIRES: Positive integer x
	// EFFECTS: get the number of digits of x
	int ret = 0;
	while(x > 0) {
		ret++;
		x /= 10;
	}
	return ret;
}
