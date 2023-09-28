//William Li
//wli128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"


#define MAX_WORD_NUM 1024
#define MAX_INPUT_SIZE 128
#define DEFAULT_RESTRICTION 10
/*
This program accepts a file name on the command line with an optional restriction limit
  ./hw3 <filename> <OPTIONAL: restriction_length>
It will search the file for words with regular expressions
  'a*': a can appear 0 to any number of times in a row
  'a?': a can appear 0 or 1 times in a row
  '~': any character can appear restriction times
Once the file is inputed, the user can pass strings into the command prompt
which will be the regex that the program searches for
Exit with ctrl+d
*/

typedef struct _node{
  char data;              //any data type
  struct _node * next;    //self reference
} Node;

Node *create_node(char ch){
  Node * node = (Node *) malloc(sizeof(Node));
  node -> data = ch;
  node -> next = NULL;
  return node;
}
void print(const Node * cur);
long length(const Node * cur);
void add_after(Node *node, char val);

int main(int argc, const char *argv[]) {
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ] = {{"\0"}}; 
  // // TODO: Implement me!
  /*make sure the command prompt lines are adequate*/
  int restriction = DEFAULT_RESTRICTION;
  if(argc < 2){
    fprintf(stderr, "No input\n");
  }
  if (argc >= 2){
    if (argc == 3) {restriction = atoi(argv[2]);}
    if(restriction < 1){
      fprintf(stderr, "Invalid resitrction length\n");
      return 1;
    }
  }

  /*open and read file into words*/
  FILE *fp = fopen(argv[1], "r");
  if(read_file(fp, words, MAX_WORD_NUM) == 0){
    fclose(fp);
    return 1;
  }
  fclose(fp);

  /*Run the program for as long as the user inputs the regex*/
  char regex[MAX_INPUT_SIZE];
  while(scanf(" %s",regex) != EOF){
    int found = 0;
    int length = sizeof(words)/MAX_INPUT_SIZE;
    for(int i = 0;  i < length ; i++){
      if(match(regex ,words[i], restriction)){
        printf("%s\n", words[i]);
        found++;
      }
      if(!strcmp(words[i], "")){ 
        break;
      }
    }
    if (!found){
      printf("No match found for regex '%s'\n", regex);
    }
  }
}