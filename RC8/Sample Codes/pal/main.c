#include <stdio.h>
#include <string.h>

int main() {
	char s[1000];
	scanf("%s", s);
	
	int length = strlen(s);
	char bestchar[1000] = {0};
	int best = 0;
	for(int i=0;s[i]!=0;i++) {
		int k = 0;
		while((i - k >= 0) && (i + k < length) && (s[i-k] == s[i+k])) k++;
		k--;
		if((2*k+1)>best) {
			int j;
			for(j=0;j<(2*k+1);j++) {
				bestchar[j] = s[i-k+j];
			}
			bestchar[j] = 0;
			best = 2*k+1;
		}
		if(s[i] == s[i+1]) {
			k = 0;
			while((i - k >= 0) && (i + k + 1 < length) && (s[i-k] == s[i+k+1])) k++;
			k--;
			if((2*k+2)>best) {
				int j;
				for(j=0;j<(2*k+2);j++) {
					bestchar[j] = s[i-k+j];
				}
				bestchar[j] = 0;
				best = 2*k+2;
			}
		}
	}

	printf("%s\n", bestchar);
	return 0;
}	
