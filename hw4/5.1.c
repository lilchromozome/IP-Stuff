//DONE
#include <stdio.h>

void print_array(int ** foo, const int r, const int c){
    for(int y = 0; y < r; ++y){
        for(int x = 0; x < c; ++x){
            printf("%d ", *(*(foo) + y * 3 + x));
        }
        printf("\n");
    }
}

int main(){
    int a[][3] = { {9,8,7}, {6, 5, 4}, {3, 2, 1}};
    int *b = a[0];
    int **c = &b;
    print_array(c, 3, 3);


    return 0;
}