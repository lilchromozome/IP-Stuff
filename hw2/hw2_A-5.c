#include <stdio.h>

int foo(int n, int sum){
    if (n==0) {return sum;};
    int d = (n%2) == 1;
    return foo(n/10, sum +d);
}

int main(void){
    int q = 90125;
    int x = foo(q, 0);
    printf("x = %d\n", x);
    return 0;
}

/*
Output:
    x = 3
Function calls:
    main calls foo with parameter values 90125, 0
        n = 90125
        sum = 0
        d = 1
    foo calls foo with parameter values 9012, 1
        n = 9012
        sum = 1
        d = 0
    foo calls foo with parameter values 901, 1
        n = 901
        sum = 1
        d = 1
    foo calls foo with parameter values 90, 2
        n = 90
        sum = 2
        d = 0
    foo calls foo with parameter values 9, 2
        n = 9
        sum = 2 
        d = 1
    foo calls coo with parameter values 0, 3
        n = 0
        sum = 3 

Variable trace
    q in main: 90125
    x in main: 3
    d in foo: 1,0,1,0,1
    
*/