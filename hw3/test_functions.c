//William Li
//wli128

#include <assert.h>
#include <stdio.h>

#include "functions.h"

#define TEST_RESTRICTION_1 10
#define TEST_RESTRICTION_2 2
#define TEST_RESTRICTION_3 5
#define TEST_RESTRICTION_4 30

#define MAX_WORD_NUM 1024

void test_read_files() {
  // TODO:
  char words[ MAX_WORD_NUM ][ MAX_WORD_SIZE + 1 ] = {{'\0'}};

  FILE *fp = fopen("input.txt", "r");

  assert(read_file(fp, words, 5) != 0);
  fp = fopen("input1.txt", "r");
  assert(read_file(fp, words, 5) == 0);

}

void test_match_regex() {
  assert(match("abc", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("abcd", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("", "", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("intermediate", "intermediate", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_star() {
  assert(match("a*", "aaa", TEST_RESTRICTION_1) == 1);
  assert(match("a*b", "ba", TEST_RESTRICTION_1) == 0);
  assert(match("abcd*", "abc", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("abc*d", "abcccccccd", TEST_RESTRICTION_1) == 1);
  assert(match("abc*de", "abcccccccd", TEST_RESTRICTION_1) == 0);
  assert(match("int*e*r*me*diate*", "intermediate", TEST_RESTRICTION_1) == 1); 
  assert(match("int*e*r*me*diate*", "inttterrmeediateeee", TEST_RESTRICTION_1) == 1); 
  assert(match("a*a*", "aaaaaa", TEST_RESTRICTION_3)==1);
}

void test_match_regex_question() {
  assert(match("a?", "", TEST_RESTRICTION_1) == 1);
  assert(match("a?", "b", TEST_RESTRICTION_1) == 0);
  assert(match("a?", "a", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("a?a?a?a?a?a?aaa", "aaa", TEST_RESTRICTION_1) == 1);
  assert(match("a?a?a?a?a?a?a?aa", "aaa", 10) == 1);
}

void test_match_regex_tilde() {
  assert(match("~", "aaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~", "", TEST_RESTRICTION_1) == 1);
  assert(match("~", "a", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("~", "program", TEST_RESTRICTION_1) == 1);
  assert(match("~h*j?k*a*a?l*", "", TEST_RESTRICTION_2) == 1);
}

void test_match_regex_multiple() {
  assert(match("!2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("!~2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("~abc", "sda12!$2", TEST_RESTRICTION_1) == 0);
  
  // TODO: Write your own tests!
  assert(match("ina?ttt?t*e*r*ms?e*diate*", "inttterrmeediateeee", TEST_RESTRICTION_1) == 1);
  assert(match("a?a*a?a?a*a?a?aa", "aaa", 10) == 1);
}

void test_match_regex_tilde_restriction() {
  // TODO: Write your own tests!
  assert(match("~", "!2222keKerCCCaeRRRT", TEST_RESTRICTION_1) == 0);
  assert(match("~a", "aaaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~~", "!2222keKerCCCaeRRRT", TEST_RESTRICTION_1) == 1);
  assert(match("~~", "!2222keKerCCbCaeRRRT", TEST_RESTRICTION_1) == 1);
  assert(match("!~a~", "!2222keKeeaeRRRT", TEST_RESTRICTION_1) == 1);
  }

int main() {
  printf("Starting Tests...\n");
  FILE* fptr1 = fopen("input.txt", "w");
  fprintf(fptr1, "5\nintermediate\ninttterrmeediateeee\nprogram\nppproograaamm\naaa");
  fclose(fptr1);

  FILE* fptr2 = fopen("input1.txt", "w");
  fprintf(fptr2, "30\nintermediate\ninttterrmeediateeee\nprogram\nppproograaamm\naaa\nmonket\nmmoooonnkkkeeyyy");
  fclose(fptr2);

  test_read_files();
  test_match_regex();
  test_match_regex_star();
  test_match_regex_question();
  test_match_regex_tilde();
  test_match_regex_multiple();
  test_match_regex_tilde_restriction();
  printf("All tests passed!!!\n");
}