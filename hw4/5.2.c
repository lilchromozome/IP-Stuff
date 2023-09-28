//DONE

#include <stdio.h>
#include <string.h>

void one(char *str, int c){
    for(; c>0; c--, str--)
        printf("%c", *str);
}

void two(char *str){
    int mid = strlen(str)/2;
    int len = mid + mid /2;
    for (int c = 0; c < len; ++c, ++str);
    one(str, mid);
}

int main(){
    char *word = "happiness";
    two(word);
    printf("\n%s\n", word);
    return 0;
}

/*
Output: 
enip
happiness

*/