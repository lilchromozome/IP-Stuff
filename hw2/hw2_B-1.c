#include <stdio.h>

unsigned int sum_digits(unsigned int n){
    if (n == 0) {
        return 0;
    }
    else {
        return n%10 + sum_digits(n/10);
    }
}

int main(){
    printf("%d\n", sum_digits(1));
    printf("%d\n", sum_digits(12));
    printf("%d\n", sum_digits(123));
    printf("%d\n", sum_digits(1234));
}