#include <stdio.h>

int frotz(int x){
    int p = (x >= 0);
    int s = -1 + (2 * p);
    int n = x * s;
    int q = n -1;
    x = q * -s;
    printf("%d, %d, %d, %d, %d\n", p, s, n, q, x);
    return x;
}

int main(void){
    int a = 4;
    do {
        // printf("a = %d\n", a);
        a = frotz(a);
    } while(a);

    printf("%d", a);
    return 0;
}
/*
p = sign?
s = multiplier
n = make x positive
q = n-- == x--
x = (posx-1)(-mult)

Output:
    a = 4
    a = -3
    a = 2
    a = -1
Function Calls:
    main calls frotz with parameter value 4
    main calls frotz with parameter value -3
    main calls frotz with parameter value 2
    main calls frotz with parameter value -1
Variable trace:
    a in main: 4, -3, 2, -1, 0
    p in frotz: 1, 0, 1, 0
    s in frotz: 1, -1, 1, -1
    n in frotz: 4, 3, 2, 1
    q in frotz: 3, 2, 1, 0
    x in frotz: 4 -> -3
                -3 -> 2
                2 -> -1
                -1 -> 0

*/
