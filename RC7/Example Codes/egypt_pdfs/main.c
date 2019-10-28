#include <stdio.h>

#define max(a,b) (a>b?a:b)
#define min(a, b) (a<b?a:b)

typedef long long LL;

LL best[100000] = {0}; // The best egyptian
LL topbest = 0; // Actually can be replaced, but for concenience we add this here
LL stack[100000] = {0}; // The current recursive stack
LL top = 0; // Stack top pointer

void helper(LL, LL);
void testbest();

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	helper(a, b);
	for(LL i=0;i<topbest;i++) { // Think of a way to realize without using i
		printf("%lld ", best[i]);
	}
	printf("\n");
	return 0;
}

void helper(LL a, LL b) {
	if(b % a == 0) { // Recursive endpoint
		int flag = 0;
		for(LL i=0;i<top;i++)
			if(b/a == stack[i]) flag = 1;
		if(flag || (b/a < stack[top - 1])) return; // Test repeated number
		stack[top++] = b/a; // Push stack
		testbest();
		top--; // Pop
		return;
	}

	for(LL cur=max(stack[top - 1] + 1, b/a);cur < 9223372036854775807;cur++) {
		if((topbest != 0) && ((cur > min((b/a) * (topbest - top + 1), best[topbest - 1] - 1)) || (top >= topbest)) || (top > 100000)) break; // Branch cutoff
		
		LL newa, newb =b*cur; // Calculate the fraction substraction
		newa = a*cur - b;

		stack[top++] = cur; // Push stack
		helper(newa, newb); // Recursion
		top--; // Pop
	}
}

void testbest() {
	if((topbest == 0) || (top <= topbest)) {
		for(LL i=0;i<top;i++) best[i] = stack[i];
		topbest = top;
	}
}

