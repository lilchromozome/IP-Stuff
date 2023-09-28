//DONE

#include <stdio.h>

int main(){
    int a = 57687;
    int b = 546576879;
    int num = 6;
    int *ip = &a;
    int *iq = &b;


    // ip = *num;
    /*
    a. ip = *num;
        it is illegal because you cannot dereference an integer and assign it to a pointer. 
        num is not a pointer and cannot be assigned a memory address.
    */

    // printf("%p\n", iq);
    // printf("%p\n", &num);
    // iq = &num;
    // printf("%p\n", iq);
    /*
    b. the pointer iq now points to num;
    */

    // printf("%p\n", ip);
    // printf("%p\n", iq);
    // ip = iq;
    // printf("%p\n", ip);
    // printf("%p\n", iq);
    /*
    c. the pointer ip now points to the same location as what iq pointed to, in the case
    above, num.
    */

    printf("%d\n", *ip);
    printf("%d\n", num);
    num = *ip;
    printf("%d\n", *ip);
    printf("%d\n", num);
    //
    /*
    num gets the value of whatever ip was pointing to in memory.
    */
    return 0;
}