#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("%d\n",argc);
    while (argc-- > 1){
        printf("%s\n", argv[argc-1]);
        printf("%d\n",argc);
    }
    printf("%d\n",argc);
    for(int i = 0; i < (sizeof(argv))/sizeof(argv[0]);i++){
        printf("%s",argv[i]);
    }
}
