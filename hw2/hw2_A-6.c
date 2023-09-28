#include <stdio.h>

int main(void){
    int x = -1, y = 1;

    while(y-x < 75){
        x -= -x *3;
        y += y * 4;
    }
    printf("x = %d, y = %d\n", x, y);
}
/*
Output:
    x = -64, y = 125
Variable trace:
x = -1, -4, -16, -64
y = 1, 5, 25, 125

*/