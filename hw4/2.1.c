//DONE

#include <stdio.h>
#include <stdlib.h>

void printarr(float arr[], int nelts){
    for(int i = 0; i < nelts; i++){
        printf("%f, ", arr[i]);
    }
}

void sort_desc(float arr[], int nelts){
    // int i = 0;
    // for(i = 0; i < nelts-1; i = i){
    //     i++;
    //     printf("%d ", i);
    //     if(*(arr+i-1) < *(arr+i)){
    //         float temp = *(arr+i-1);
    //         *(arr+i-1) = *(arr+i);
    //         *(arr+i) = temp;
    //         i = 0;
    //     }
    //     printarr(arr, 7);
    //     printf("%d \n", i);
    // }
    for (int i = 0; i < nelts-1; i++ ){
        for(int j = 0; j < nelts - i; j++){
            if(arr[j]< arr[j+1]){
                float temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void nth_largest_in_each_row(const float grid[][10], int nrows, int n, float result[]){
    for(int i = 0; i< nrows; i++){
        result[i] = 0;
        float row[10] = {0};
        for(int j = 0; j < 10; j++){
            row[j] = grid[i][j];
        }
        sort_desc(row, 10);
        result[i] = row[n-1];
    }
}


int main(){
    float arr[10][10];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            arr[i][j] = rand();
        }
    }
    float res[10];
    for(int i = 0; i<10; i++){
        sort_desc(arr[i], 10);
    }
    
    printarr(arr[0], 10);
    printf("\n");
    printarr(arr[1], 10);
    printf("\n");
    printarr(arr[2], 10);
    printf("\n");
    nth_largest_in_each_row(arr, 10, 1, res);
    for(int i = 0; i < 10; i++){
        printf("%f\n", res[i]);
    }
    return 0;
}