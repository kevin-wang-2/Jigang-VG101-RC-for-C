#include <stdio.h>
#include <stdlib.h>

//Equivalent to including <stdbool.h>
typedef int bool;

bool isOp(char letter){
    return letter == '+' || letter == '-' || letter == '*' || letter == '/' || letter == '(';
}

int prio(char op){
    if(op == '+' || op == '-') return 0;
    return 1;
}

double calc(double num1, double num2, char op){ // Remember to reverse
    switch(op){
        case '+':
            return num2 + num1;
        case '-':
            return num2 - num1;
        case '*':
            return num2 * num1;
        default:
            return num2 / num1;
    }
}

int main() {
    double nums[100];
    int numtop = 0;
    char cur, last = 0;
    char stack[100], temp[100]; //Symbol stack and temp string
    char stacktop = 0, temptop = 0; // Top pointer (can also be implemented by using pointers
    while((cur = (char)getchar()) != '\n'){
		if(cur == ' ') continue;
        if(cur == ')'){ // Proccess )
            if(temptop != 0){
                temp[temptop++] = 0;
                nums[numtop++] = strtod(temp, NULL);
                temptop = 0;
            }
            char op;
            while((stacktop != 0) && (op = stack[--stacktop]) != '('){
                double num1, num2;
                num1 = nums[--numtop];
                num2 = nums[--numtop];
                nums[numtop++] = calc(num1, num2, op);
            }
        } else if(cur == '('){
            stack[stacktop++] = cur;
        } else if(isOp(cur)) {
            if(temptop != 0) {
                temp[temptop++] = 0;
                nums[numtop++] = strtod(temp, NULL);
                temptop = 0;
            } else if(last != ')') nums[numtop++] = 0;
            if((stacktop != 0) && (stack[stacktop - 1] != '(')) {
                while ((stacktop != 0) && (stack[stacktop - 1] != '(') && (prio(stack[stacktop - 1]) >= prio(cur))) {
                    char op = stack[--stacktop];
                    double num1, num2;
                    num1 = nums[--numtop];
                    num2 = nums[--numtop];
                    nums[numtop++] = calc(num1, num2, op);
                }
            }
            stack[stacktop++] = cur;
        } else {
            temp[temptop++] = cur;
        }
		last = cur;
    }
    if(temptop != 0){
        temp[temptop++] = 0;
        nums[numtop++] = strtod(temp, NULL);
    }
    while(stacktop != 0){
        char op = stack[--stacktop];
        double num1, num2;
        num1 = nums[--numtop];
        num2 = nums[--numtop];
        nums[numtop++] = calc(num1, num2, op);
    }
    printf("= %g\n", nums[0]);
    return 0;
}
