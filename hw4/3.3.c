#include <stdio.h>
#include <stdlib.h>

float *func(float a, float b, int n){

    float *p = malloc(n*sizeof(float));
    for (int i = 0; i < n; i++){
        p[i] = (a*(n-1-i) + b*i)/(n-1);
        printf("i = %d, p[i] = %lf\n", i, p[i]);
    }
    return p;
}

int main(){
    float *a = func(2.0, 8.0, 10);
    free(a);
}

/*
*func creates an array of floats containing n elements that are equally spaced apart
between a and b inclusively.

*@param a is the minimum value
*@param b is the maximum value
*@param n is the number of numbers between 2 and 8 inclusive\

*@return p is array of floats
*/
