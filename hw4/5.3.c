
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char wordle(char words, int size){
char** wordle(char** words, int size){
    // char *result = malloc(sizeof(char) * size);
    char **result = malloc(sizeof(char *) *size);

    for (int i = 0; i < size; i++){
        int wlen = strlen(words[i]) * (i + 1) + 1;
        result[i] = malloc(wlen);
        strcpy(result[i], words[i]);
        for(int j = 1; j <= i; j++){
            strcat(result[i], words[i]);
        }
    }
    return result;
}

int main(){
    char *list[] = {"one", "two", "three", "four"};
    char **result = wordle(list, 4);
    for(int i = 0; i < 4; i++){
        printf("%s\n", result[i]);
        //free result
        free(result[i]);
    }
    free(result);
    return 0;
}

/*
Output:
Error

Correct Output:
one
twotwo
threethreethree
fourfourfourfour

1. No freeing of dynamically allocated memore in result or the string stored in result.
    You could fix this by freeing result[i] after printing it and freeing result right
    before the return statement in main.
2. In wordle, the declared return value is a char, however return result actually returns
    a pointer to a char array (a string). It is supposed to return an array of strings.
    Fix this by declaring result as {char **result = malloc(sizeof(char *) *size);}
    It should also be {sizeof(char *) * size} instead of {sizeof(char) * size} because the
    result array actually directly stores character pointers, not the actual characters 
    of the strings.
3. In main, char**result = wordle(list, 4); have conflicting datatypes due to the problem
    above. result is a 2d array while wordle returns a 1D array. You could fix this by
    declaring result in wordle as a 2D array like {char **result = }. Additionally, the
    function declaration should be {char** wordle(char** words, int size)} to return the 
    correct datatype.
4. In wordle, the words parameter is of type char. However, in main, list is an array
    of strings, meaning {wordle(list, 4)} is the wrong datatype for words. The parameter
    for wordle should be {char** words}.
*/