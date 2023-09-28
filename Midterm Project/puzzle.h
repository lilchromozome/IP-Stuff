#ifndef PUZZLE_H
#define PUZZLE_H

#include "ppm_io.h" // for Image data type

#define MAX_STEPS 31

typedef struct {
  int size;
  int* tiles;
  Image* img;
} Puzzle;

Puzzle* puzzle_create(int size);
Puzzle* copy_puzzle(Puzzle* p);

void puzzle_destroy(Puzzle *p);
void print_puzzle(Puzzle* p, FILE* fp);
int puzzle_is_solved(Puzzle *p);
int isValidTileValue(Puzzle* p, int val, int cur_idx);
int handle_W_command(Puzzle *p, FILE *image, FILE *config);
int slide_tile(Puzzle *p, char direction);
int get_parity(char direction);
int handle_V_command(Puzzle *p, char steps[]);
int V_helper(Puzzle *p, char steps[], int cur_steps);

#endif // PUZZLE_H