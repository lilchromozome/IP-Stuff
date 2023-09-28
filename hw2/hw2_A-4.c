#include <stdio.h>

int main(void) {
    int a = 0, c = -4, q = 0;
    while (c) {
        printf("%d\n", c++);
    }
    if (c++) {q +=5;}
    if (++a) {q += 11;}
    printf("q = %d\n", q);
    return 0;
}

/*
Output:
    -4
    -3
    -2
    -1
    q = 11
Variable trace:
    a = 0, 1
    c = -4, -3, -2, -1, 0, 1
    q = 0, 11
*/