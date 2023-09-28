//DONE

#include <stdio.h>
#include <stdlib.h>

int *make_hist(int data[], int num_elts, int maxval){
    //num_elts*sizeofint not maxval*sizeofint
    int *hist = (int *) malloc((maxval+1) * sizeof(int));         
    //initialize i to 0
    int i = 0;
    while(i<= num_elts){
        int val = data[i];
        if(val >= 0 && val <= maxval){
            hist[val]++;
        }
        i++;            //increment i;
    }
    return hist;
}

int main(void){
    int values[20];
    printf("enter 20 integer values in the range 0-10\n");
    for(int i = 0; i < 20; i++){
        scanf("%d", &values[i]);
    }
    int*result = make_hist(values, 20, 10);
    printf("occurences:\n");
    for(int i = 0; i <= 10; i++){                
        printf("%d: %d\n", i, result[i]);
    }
    free(result);
    return 0;
}

/*
1. i is not initialized in make_hist, should be initialized to 0
2. i does not change value in make_hist so there is an infinite loop
3. the dynamic allocation in make_hist should be num_elts * sizeof(int)
4. free result
*/