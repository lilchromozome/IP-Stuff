#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// put char into a newly created node
Node * create_node(char ch) {
  Node * node = (Node *) malloc(sizeof(Node));
  assert(node); //confirm malloc didn't fail

  node->data = ch;
  node->next = NULL;
  return node;
}

// output the list iteratively
void print_list(const Node * cur) {
  while (cur != NULL) {
    printf("%c ", cur->data);
    cur = cur->next;  // advance to next node
  }
}

// output the list recursively
void print_rec(const Node * head) {
  if (head != NULL) {
    printf("%c ", head->data);
    print_rec(head->next);
  }
}

// output the list in reverse (recursive)
void reverse_print(const Node * head) {
  if (head != NULL) {  // equivalent: if (head)
    reverse_print(head->next);
    printf("%c ", head->data);
  }
}

// count and return the number of elements in the List (recursive)
long length(const Node * head) {
  if (head == NULL)
    return 0;
  return 1 + length(head->next);
}

// get rid of (deallocate) entire list, recursively from end to start
void clear_list(Node ** list_ptr) {
  if (*list_ptr != NULL) {
    clear_list( &((*list_ptr)->next));
    free(*list_ptr);
    *list_ptr = NULL;
  }
}

// add char immediately after existing node
void add_after(Node * node, char val) {
  if (node == NULL)
    return;
  Node * n = create_node(val);
  n->next = node->next;
  node->next = n;
}

// add char to beginning of list
void add_front(Node ** list_ptr, char val) {
  Node * n = create_node(val);
  n->next = *list_ptr;
  *list_ptr = n;
}

// EXERCISE
// remove node after current, return removed char, or '?' if no node
char remove_after(Node * node) {

  if(node->next == NULL){
  return '?';}

  Node * n = node->next;
  char node_removed_val = n->data;
  node->next = n->next;
  n->next = NULL;
  free(n);
  return node_removed_val;
  
}

// EXERCISE
// remove first node, if any, return removed char or '?' if no node
char remove_front(Node ** list_ptr) {
  char removed_char = (*list_ptr)->data;
  Node * node_1 = *list_ptr;
  Node * node_2 = node_1 -> next;

  *list_ptr = node_2;
  node_1->next = NULL;
  free(node_1);
  
  if(*list_ptr == node_1){
    return '?';
  }
  return removed_char;
}

// EXERCISE
// remove all occurrences of a particular character
void remove_all(Node ** list_ptr, char val) {
  if(list_ptr == NULL || *list_ptr == NULL){
    return;
  }

  Node * node = *list_ptr;
  if(node->data == val){
      *list_ptr = node->next;
      free(node);
    remove_all(list_ptr, val);
  }
  else{
    remove_all(&(node->next) , val);
  }
  
}

// EXERCISE
// insert in order (assumes list is ordered)!!
// return the address of the node containing the character inserted
Node * insert(Node ** list_ptr, char val) {
  if(list_ptr == NULL || *list_ptr == NULL){
    add_front(list_ptr, val);
    return *list_ptr;
  }
  if(val < (*list_ptr)->data){
    add_front(list_ptr, val);
    return *list_ptr;
  }
  else{
    insert(&((*list_ptr)->next) , val);
  }
  return NULL;
}



// ---------- Other functions you may want to implement ----------

// insert char at end of list
void add_tail(Node ** list_ptr, char val) {

  Node * cur = *list_ptr;
  while((cur -> next) != NULL){
    cur = cur->next;
  }
  add_after(cur, val);
}


// insert char at end of list (recursive)
void add_tail_rec(Node ** list_ptr, char val) {

  if(*list_ptr == NULL){
    Node * node = create_node(val);
    *list_ptr = node;
    node->next = NULL;
  }
  else{
    Node * cur = *list_ptr;
    add_tail_rec(&(cur->next), val);
  }
}

// find specfied val in the list, return pointer to first node in list
// that contains it, or NULL if val is not present
Node* find(Node * node, char value) {

  if(node == NULL){
    return NULL;
  }
  else if((node -> data) == value){
    return node;
  }
  else {
    return find(node->next, value);
  }
  return NULL;

}

// remove 1st occurrence of char from list if there, return 1 success, 0 failure
int remove_char(Node ** list_ptr, char val) {
  if(list_ptr == NULL || *list_ptr == NULL){
    return 0;
  }
  if(val == (*list_ptr)->data){
    remove_front(list_ptr);
    return 1;
  }
  else{
    return remove_char(&(*list_ptr)->next, val);
  }
  return 0;
}

// recursive version of removing first occurrence
int remove_char_rec(Node ** list_ptr, char val)  {

  if(*list_ptr == NULL){
    return 0;
  }
  else if(((*list_ptr) -> data) == val){
    Node * temp;
    temp = (*list_ptr)->next;
    free(*list_ptr);
    *list_ptr = temp;
    return 1;
  }
  else{
    return remove_char(&(*list_ptr)->next, val);
  }
  // not yet implemented
  return 0;

}


// replace first occurrence of old with new, return 1 success, 0 failure
int replace(Node * head, char old, char n) {

  Node * target = find(head, old);
  if(target == NULL){
    return 0;
  }
  target -> data = n;
  return 1;

}

int do_operation(Node *node, char *p) {
  if (node == NULL || node->next == NULL)
    return 0;

  *p = node->data;
  node->data = node->next->data;
  Node *n = node->next;
  node->next = n->next;
  free(n);

  return 1;
}
