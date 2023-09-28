//William Li
//wli128

#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size) {
  // TODO: Implement Me!
  int k = 0;
  fscanf(fp, "%d", &size);
  for (int i = 0; i < size; i++) {
    if (fscanf(fp, "%s", words[i]) == 1) {
      k++;
    }
    else{
      break;
      }
  }
    if (k < size){
      fprintf(stdout, "There are fewer words in the document then indicated\n");
      return 0;
    } else return k;
}

int match(const char *regex, const char *word, int restriction) {
  // TODO: Implement me!
  if (*regex == '\0' && *word == '\0'){ return 1;}
  
  if(*regex != '\0' || *word != '\0'){
    /*
    If the next character is *, the previous character can repeat 0 or more times
    */
    if(*(regex+1) == '*'){
      // printf("next is * %c\n", *word);
      /*checks if the regex character matches word character*/
      if(*regex == *word){
        // printf("match %c*\n", *word);
        /*try letting the 'a*' match the initial 'a' in the word*/
        if(match(regex, word+1,restriction)){
          return 1;
          }
        /*if there is another regex, try the next 'a*' matches a in word */
        if(match(regex+2, word, restriction)){
          return 1;
          }
        else {return 0;}
      }
      // try assuming that the 'a*' matches nothing
      if(match(regex+2,word ,restriction)) {
        // printf("no  match *\n");
        return 1;
      }
      else {return 0;}
    }
    /*
    If the next character is ?, the character can repeat 0 or 1 times 
    */
    if(*(regex+1) == '?'){
      // printf("match %c ?\n", *word);
      /*checks if the regex character matches word character*/
      if(*regex == *word){
        /*try letting 'a?' match the the initial 'a' in word*/
        if(match(regex+2, word+1, restriction)){
          return 1;
        }
        /*if there is another regex, try letting the next 'a?' match 'a'*/
        if(match(regex+2, word, restriction)){
          return 1;
        }
      }
      else{return match(regex+2, word, restriction);}
    }
    /*
    If the next chracter is ~, can repeat 0 or restriction times
    */
    if (*regex == '~') {
        for (int k = 0; k < (int)strlen(word) && k < restriction; k++) {
          // printf("regex: %c, word: %c, k: %d\n", *regex, *(word + k), k);
          /*try letting character after ~ match word*/
          if (match((regex + 1), (word + k + 1), restriction)) {
            // printf("word matches after ~\n");
            return 1;
          }
        }
        /*else return first match after ~*/
        if (match((regex + 1), word, restriction)) {
            return 1;
        }
    }
    
    /*
    no regex term
    */
    if(*regex == *word){
      // printf("no regex! %c\n", *word);
      return match(regex+1, word+1, restriction);
    }
      // printf("no match\n");
      return 0;
  }
  return 1;
}

