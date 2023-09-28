#include <stdio.h>
#include <string.h>

void replace(char str[], char c1, char c2){
    for (unsigned int i = 0; i < strlen(str); i++){
        if(str[i] == c1){
            str[i] = c2;
        }
    }
}
void strfunc(char s[], int len){
    for (int i = 0; i < len; i++){
        printf("%d\n", i);
        char c = s[i];
        if( c >= 'A' && c <= 'Z'){
            c+= ('a' - 'A');
        }
        else if (c >= 'a' && c<= 'c'){
            c -= ('a' - 'A');
        }
        s[i] = c;
    }
}

int main(){
    char word[] = "AAAAAAAAAA";
    strfunc(word, 4);
    printf("%s\n", word);
}