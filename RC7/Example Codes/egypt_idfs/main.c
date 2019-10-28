#include <stdio.h>

#define max(a, b) ((a>b)?a:b)
#define min(a, b) ((a>b)?b:a)

#define maxResNum 100000

#define true 1
#define false 0

typedef long long LL;
typedef int bool;

//Declare some global variables in the heap to avoid stack overflow
LL fMin, maxDepth, ans[maxResNum], partial[maxResNum];
bool flag;

/*Proccess the DFS
 *x,y is the fraction left to proccess, depth isthe current depth
 */
void proccess(LL x, LL y, LL depth) {
    LL cMin, cMax;
    if(depth == 0)
        cMin = y/x;
    else cMin = max(partial[depth - 1] + 1, y / x);//Most lower bound
    cMax = min((y / x) * (maxDepth - depth + 1), fMin - 1);//Least upper bound
    for (LL cur = cMin; cur <= cMax; cur++) {
        LL xNext, yNext;
        partial[depth] = cur;
        xNext = x * cur - y;
        yNext = y * cur;
        if (x >= 0 && depth < maxDepth) proccess(xNext, yNext, depth + 1);
        if (xNext == 0 && cur < fMin) {
            fMin = cur;
            flag = true;
            for (LL j = 0; j < maxDepth + 1; j++) ans[j] = partial[j];
        }
    }
}

int main() {
    //Do some input stuff
    int a, b;
    scanf("%d %d", &a, &b);
    //Initialization
    flag = false;
    maxDepth = 0;
    //Iteration increase depth
    while (!flag) {
        fMin = 9223372036854775807;//max of long long
        proccess(a, b, 0);
        maxDepth++;
    }
    //Output the ans
    for (LL i = 0; i < maxDepth; i++) printf("%lld ", ans[i]);
    printf("\n");
    return 0;
}