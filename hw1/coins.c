//Hopkins ID: 345A36

/*
    A coin purse program to keep track of custom coins.
    Intermediate Programming hw1
*/

#include <stdio.h>

int add(char coin_type, int num, char coin_types[], int count[], int denoms);
int rem(char coin_type, int num, char coin_types[], int count[], int denoms);
void sum(int coinvals[], char cointypes[], int count[], int denoms);

int main(){
    int d = 0;
    //ask for denoms
    printf("How many denominations? ");
    if(scanf(" %d", &d) != 1){
        fprintf(stderr, "Invalid input\n");
        return 1;
    };

    char coin_types[d];
    int coin_vals[d];
    int count[d];
    //sets value of all elements of all arrays to 0
    for (int i = 0; i < d; i++){
        coin_types[i] = 0;
        coin_vals[i] = 0;
        count[i] = 0;
    }

    //ask for identifier and coin values
    for (int i = 0; i < d; i++){
        printf("Enter coin identifier and value in cents: ");
        if (scanf(" %c %d", &coin_types[i], &coin_vals[i]) != 2) {
            fprintf(stderr, "Invalid input\n");
            return 1;}
    }
    
    char action;
    char coin_type;
    int num = 0;

    int input = 0;

    //loop for user commands to edit purse
    do {
        printf("Enter a command: ");
        if((input = scanf(" %c", &action)) == EOF){
            printf("Bye!\n");
            return 0;};
        switch (action){
            case 'q':
                printf("Bye!\n");
                return 0;
            case 's':
                sum(coin_vals, coin_types, count, d);
                break;
            case 'a':
                scanf(" %c %d", &coin_type, &num);
                if(add(coin_type, num, coin_types, count, d)==2) {return 2;}
                break;
            case 'r':
                scanf(" %c %d", &coin_type, &num);
                if(rem(coin_type, num, coin_types, count, d)==2) {return 2;}
                break;
            
            //error handling
            default: fprintf(stderr, "Invalid command\n");
                return 3;
        }
    }while(input == 1);

    if (scanf("%d", &num)== EOF){ 
        printf("Bye!\n");
        return 0;}
    return 0;
}

/*function that removes a given amount of coins of a specific type
inputs: char coin_types[]       identifier for coin types
        int num                 amount of coins to remove
        char cointypes[]        identifiers for each coin type
        int count[]             how many of each coin
        int denoms              length of arrays
output: none
*/

int add(char coin_type, int num, char coin_types[], int count[], int denoms){
    //find index of coin
    int index = -1;
    for (int i = 0; i < denoms; i++){
        if (coin_types[i] == coin_type){
            index = i;
        }
    }
    //error handling if coin_type is not in coin_types[]
    if (index == -1){
        fprintf(stderr, "Unknown coin identifier\n");
        return 2;
    }
    count[index] += num;
    return 0;
}

/*function that removes a given amount of coins of a specific type
inputs: char coin_types[]       identifier for coin types
        int num                 amount of coins to remove
        char cointypes[]        identifiers for each coin type
        int count[]             how many of each coin
        int denoms              length of arrays
output: none
*/
int rem(char cointype, int num, char cointypes[], int count[], int denoms){
    //find index of coin
    int index = -1;
    for (int i = 0; i < denoms; i++){
        if (cointypes[i] == cointype){
            index = i;
        }
    }
    //error handling if coin_type is not in coin_types[]
    if (index == -1){
        fprintf(stderr, "Unknown coin identifier\n");
        return 2;
    }
    count[index] -= num;
    return 0;
}

/*function that gives a summary of the coins
inputs: int coinvals[]          value of each coin
        char coin_types[]       identifier for coin types
        int count[]             how many of each coin
        int denoms              length of arrays
output: a summary of each cointype, coin value, coin count, and value of all of each coin
        a sum of all coins
*/
void sum(int coin_vals[], char coin_types[], int count[], int denoms){
    float totalval = 0;
    printf("Identifier,Face Value,Count,Total Value\n");
    //cycles through coin_vals[], coin_types[], and count[] and prints their values
    for (int i = 0; i<denoms; i++){
        int sum = count[i]*coin_vals[i];
        printf("%c,%d,%d,%d\n", coin_types[i], coin_vals[i], count[i], sum);
        totalval += sum;
    }
    printf("Overall value of collection: $%.2f\n", totalval/100);
}