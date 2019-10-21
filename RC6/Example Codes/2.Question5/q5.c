#include <stdio.h>
#include <math.h>

void recursive_helper(int, int);

int main() {
	int layers;
	scanf("%d", &layers);
	int total_length = pow(3, layers);
	for(int i=0;i<layers + 1;i++) {
		recursive_helper(total_length, i);
		printf("\n\n\n");
	}
	return 0;
}

void recursive_helper(int length, int layer) {
	// REQUIRES: length > 0, layer >= 0
	// MODIFIES: printf
	// EFFECTS: print a cantor line with $(length) and $(layer)
	if(layer == 0) {
		for(int i=0;i<length;i++) printf("-");
	}
	else {
		recursive_helper(length / 3, layer - 1);
		for(int i=0;i<length / 3;i++) printf(" ");
		recursive_helper(length / 3, layer - 1);
	}
}
