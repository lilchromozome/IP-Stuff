#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ppm_io.h"
#include "puzzle.h"

// also tests puzzle_destroy
void test_puzzle_create(void) {

  Puzzle *p3 = puzzle_create(3);
  Puzzle *p5 = puzzle_create(5);

  assert(p3->size == 3);
  for (int i = 0; i < 9; ++i) {
    assert(p3->tiles[i].index == 0);
  }

  assert(p5->size == 5);
  for (int i = 0; i < 25; ++i) {
    assert(p5->tiles[i].index == 0);
  }

  puzzle_destroy(p3);
  puzzle_destroy(p5);
}

// also tests puzzle_get_tile
void test_puzzle_set_tile(void) {
  int init[4][4] = {
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 10, 12 },
  };
  Puzzle *p4 = puzzle_create(4);
  FILE *fp = fopen("ingo.ppm", "r");
  p4->image = ReadPPM(fp);

  for (int i = 0; i < 4; ++i){
    for (int j = 0; j < 4; ++j){
      assert(puzzle_create_tile(p4, i, j, init[i][j]));
    }
  }
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      // Tile * t = puzzle_get_tile(p4, i, j);
      // printf("%d\n", t->tile->data->r);
      assert(puzzle_get_tile(p4, i, j)->index == init[i][j]);
    }
  }

  puzzle_destroy(p4);
  fclose(fp);
}

void test_print_tile(void){
    int init[4][4] = {
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 10, 12 },
  };

      // { 0, 1, 2, 3 },            
      // { 4, 5, 6, 7 },
      // { 8, 9, 10, 11 },
      // { 12, 13, 14, 15 },
  Puzzle *p4 = puzzle_create(4);
  FILE *fp = fopen("ingo.ppm", "r");
  p4->image = ReadPPM(fp);


  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      assert(puzzle_create_tile(p4, i, j, init[i][j]));


  FILE * image;
  image = fopen("cat1111.ppm", "w");

  /*EDIT THIS TO PRINT OUT SPECIFIC TILE*/
  print_tile(p4, image, 3, 3);
  Tile *t = puzzle_get_tile(p4, 0, 0);
  // printf("%d\n", t->index);

  fclose(image);
  puzzle_destroy(p4);
}

void test_handle_K(void){
  //       int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
  //   { 5, 7, 1, 2 },
  //   { 13, 9, 3, 4 },
  //   { 0, 8, 6, 11 },
  //   { 14, 15, 10, 12 },
  // };

  //     int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
  //   { 0, 1, 2, 3 },
  //   { 4, 5, 6, 7 },
  //   { 8, 9, 10, 11 },
  //   { 12, 13, 14, 15 },
  // };
  int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 },
    { 13, 14, 15, 0 },
  };


  Puzzle *p4 = puzzle_create(4);
  FILE *fp = fopen("ingo.ppm", "r");
  p4->image = ReadPPM(fp);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      assert(puzzle_create_tile(p4, i, j, init[i][j]));

  handle_K_command(p4);

  fclose(fp);
  printf("----------\n");
  puzzle_destroy(p4);
}

void test_handle_W(void){
  //   int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
  //   { 5, 7, 1, 2 },
  //   { 13, 9, 3, 4 },
  //   { 0, 8, 6, 11 },
  //   { 14, 15, 10, 12 },
  // };

  // //     int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
  // //   { 0, 1, 2, 3 },
  // //   { 4, 5, 6, 7 },
  // //   { 8, 9, 10, 11 },
  // //   { 12, 13, 14, 15 },
  // // };
  int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 },
    { 13, 14, 15, 0 },
  };


  Puzzle *p4 = puzzle_create(4);
  FILE *fp = fopen("ingo.ppm", "r");
  p4->image = ReadPPM(fp);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      assert(puzzle_create_tile(p4, i, j, init[i][j]));

  
  // for(int i = 0; i < p4->size; i++){   
  //   for(int j = 0; j < p4->size; j++){
  //     int row = p4->tiles[i * p4->size +j].index / p4->size;
  //     int col = p4->tiles[i * p4->size +j].index % p4->size;     //finds row/col of next tile
  //     printf("%d %d, %d\n", row, col, init[i][j]);
  //   }
  // }


  FILE * image;
  image = fopen("cat.ppm", "w");
  FILE * config;
  config = fopen("config.txt", "w");

  handle_W_command(p4, image, config);

  image = fopen("cat1111.ppm", "w");
  print_tile(p4, image, 0, 0);

  puzzle_destroy(p4);

  fclose(image);
  fclose(config);

}


void test_handle_S(void){
      int init[4][4] = {      // 5 7 1 2 13 9 3 4 0 8 6 11 14 15 10 12
    { 5, 7, 1, 2 },
    { 13, 9, 3, 4 },
    { 0, 8, 6, 11 },
    { 14, 15, 10, 12 },
  };


  Puzzle *p4 = puzzle_create(4);
  FILE *fp = fopen("ingo.ppm", "r");
  p4->image = ReadPPM(fp);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      assert(puzzle_create_tile(p4, i, j, init[i][j]));
  
}

int main(void) {
  test_puzzle_create();
  test_puzzle_set_tile();
  test_print_tile();
  test_handle_W();
  test_handle_K();
  // ...call other test functions...

  printf("All tests passed!\n");
  return 0;
}