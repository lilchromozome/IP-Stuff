//DONE
#include <stdio.h>

void func(float *s, int n, float *t){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("t[%d] = s[%d]\n", i*n+j, j*n + i);
            t[i*n + j] = s[j*n+i];
        }
    }
}

int main(){
    float m1[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    float m2[3][3];
    func((float*) m1, 3, (float*) m2);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%f ", m2[i][j]);
        }
        printf("\n");
    }
}
/*
*func copies, s, another 2D array, t, that swaps each array element along the unit 
matrix diagonal. if both s and t are square arrays, and n is equal to the dimensions
of the array, t becomes the a array with the rows and columns switched. Each element at 
position (i,j) in array s becomes position (j,i) in array t.

*@param s: input 2d array
*@param n: number of rows and columns
*@param t: output 2d array
*/