#include <stdio.h>
#include <stdlib.h>

int main() {
	double stack[255];
	char temp[255], c;
	int stacktop = 0, temptop = 0;
	while((c = (char)getchar()) != '\n') {
		switch(c) {
			case ' ':
				break;
			case ',':
				if(temptop != 0) {
					temp[temptop++] = 0; // End the string
					stack[stacktop++] = strtod(temp, NULL); // Push stack
					temptop = 0;
				}
				break;
			case '+':
				{ // Create a block to declare temparay variables
					double operand1 = stack[--stacktop], operand2 = stack[--stacktop];
					stack[stacktop++] = operand1 + operand2;
				}
				break;
			case '-':
				{ // Create a block to declare temparay variables
					double operand1 = stack[--stacktop], operand2 = stack[--stacktop];
					stack[stacktop++] = operand2 - operand1;
				}
				break;
			case '*':
				{ // Create a block to declare temparay variables
					double operand1 = stack[--stacktop], operand2 = stack[--stacktop];
					stack[stacktop++] = operand1 * operand2;
				}
				break;
			case '/':
				{ // Create a block to declare temparay variables
					double operand1 = stack[--stacktop], operand2 = stack[--stacktop];
					stack[stacktop++] = operand2 / operand1;
				}
				break;
			default:
				temp[temptop++] = c;
		}
	}
	printf("%lf\n", stack[0]);
	return 0;
}
