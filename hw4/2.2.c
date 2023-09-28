//DONE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char **read_all_lines(FILE *in, int maxlen, int *num_lines){
    *num_lines = 0;
    char **words = malloc(sizeof(char*));
    words[0] = malloc(sizeof(char) * maxlen);
    while(fgets(words[*num_lines], maxlen, in)){
        (*num_lines)++;
        words = realloc(words, (*num_lines +1) * sizeof(char*));
        words[*num_lines] = malloc(sizeof(char) * maxlen);
    }
    return words;
}

int main(){
    int nlines;
    FILE *in = fopen("input.txt", "r");
    char **lines = read_all_lines(in, 72, &nlines);
    fclose(in);

    assert(nlines == 6);
    assert(strcmp(lines[0], "This is an input file.\n")==0);
    assert(strcmp(lines[1], "It has some pretty awesome stuff in it.\n") == 0);
    assert(strcmp(lines[2], "Ok, that's all for now.\n")==0);
    assert(strcmp(lines[3], "a\n")==0);
    assert(strcmp(lines[4], "a\n")==0);
    assert(strcmp(lines[5], "a\n")==0);

    for(int i = 0; i < nlines; i++){
        free(lines[i]);
    }
    free(lines);
}