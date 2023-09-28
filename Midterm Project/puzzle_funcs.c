#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

/**
 * Creates puzzle of input size
 * 
 * @param int size
 * return puzzle
*/
Puzzle* puzzle_create(int size) {
  Puzzle* puzzle = (Puzzle*) malloc(sizeof(Puzzle));
  puzzle->size = size;
  puzzle->tiles = malloc(size * size * sizeof(int));
  puzzle->img = NULL;
  return puzzle;
}

/**
 * Copies puzzle from p to copy
 * 
 * @param Puzzle* p
 * return Puzzle *copy
*/
Puzzle* copy_puzzle(Puzzle* p) {
  Puzzle* copy = puzzle_create(p->size);
  memcpy(copy->tiles, p->tiles, p->size*p->size * sizeof(int));
  copy->img = p->img;
  return copy;
}

/**
 * Destroys puzzle by freeing dynamically allocated memory
 * 
 * @param Puzzle *p
 * return void
*/
void puzzle_destroy(Puzzle *p) {
  free(p->tiles);
  free(p);
}

/**
 * Prints puzzle in a 1D array
 * 
 * @param Puzzle *p
 * @param FILE* fp
 * return void
*/
void print_puzzle(Puzzle* p, FILE* fp) {
  for(int i = 0; i < p->size * p->size; i++){
    char* to_write = i == 0 ? "%d" : " %d";
    fprintf(fp, to_write, p->tiles[i]);
  }
  fprintf(fp, "\n");
}

/**
 * Checks if puzzle is solved
 * 
 * @param Puzzle *p
 * return 1 if solved
 * return 0 if not solved
*/
int puzzle_is_solved(Puzzle *p) {

  // checks if indices in correct order (e.g. index i has value i + 1)
  for (int i = 0; i < p->size * p->size - 1; i++) {
    if (p->tiles[i] != i + 1) {
      return 0;
    }
  }

  // checks if last index is 0 (e.g. empty index)
  if (p->tiles[p->size * p->size - 1] != 0) {
    return 0;
  }

  return 1;
}

/**
 * Checks if index of puzzle has a valid value
 * 
 * @param Puzzle *p
 * @param val: value of current index
 * @param cur_idx: index to check validity of
 * 
 * return 1 if valid value in specified puzzle index
 * return 0 if invalid value in specified puzzle index
*/
int isValidTileValue(Puzzle* p, int val, int cur_idx) {
  assert (cur_idx < p->size * p->size);
  if (val < 0 || val >= p->size * p->size) return 0;
  for (int i = 0; i < cur_idx; i++) {
    if (p->tiles[i] == val) return 0;
  }
  return 1;
}

/**
 * Handles W (writing) command
 * 
 * @param Puzzle *p
 * @param FILE *fp_img: image file
 * @param FILE *fp_config: config file
 * 
 * return -1 if error occurs
 * return 1 if no error occurs
*/
int handle_W_command(Puzzle *p, FILE *fp_img, FILE *fp_config) {
  
  // checks if image dimensions are valid
  if (p->img->rows % p->size != 0 || p->img->cols % p->size != 0) {
    fprintf(stderr, "Invalid image dimensions\n");
    return -1;
  }

  print_puzzle(p, fp_config);

  int num_pixels = p->img->rows * p->img->cols;

  Image* src_img = p->img;
  //create new image
  Image *dst_img = (Image*) malloc(sizeof(Image));
  dst_img->data = (Pixel*) calloc(sizeof(Pixel), num_pixels);
  dst_img->rows = p->img->rows;
  dst_img->cols = p->img->cols;

  int pixels_per_tile = dst_img->rows / p->size;
  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      int tile_idx = p->tiles[i*p->size + j] - 1;
      if (tile_idx == -1) continue;  // if it's the 0 tile

      int src_img_row_num = tile_idx / p->size;
      int src_img_col_num = tile_idx % p->size;

      int dst_img_row_num = i;
      int dst_img_col_num = j;

      int src_img_start_row = src_img_row_num * pixels_per_tile;
      int src_img_start_col = src_img_col_num * pixels_per_tile;
      int dst_img_start_row = dst_img_row_num * pixels_per_tile;
      int dst_img_start_col = dst_img_col_num * pixels_per_tile;

      for (int x = 0; x < pixels_per_tile; x++) {
        for (int y = 0; y < pixels_per_tile; y++) {
          dst_img->data[(dst_img_start_row+x) * dst_img->cols + dst_img_start_col + y] =
              src_img->data[(src_img_start_row+x) * src_img->cols + src_img_start_col + y];
        }
      }
    }
  }
  WritePPM(fp_img, dst_img);
  free(dst_img->data);
  free(dst_img);

  return 1;
}

/**
 * Slides tile of puzzle in specified direction
 * 
 * @param Puzzle *p
 * @param char direction: direction we want to slide a tile
 * 
 * return 1 if tile slides in specified direction
 * return 0 if tile cannot slide in specified direction
*/
int slide_tile(Puzzle *p, char direction) {


  // finds empty tile in puzzle
  int empty_index = -1;
  for (int i = 0; i < p->size * p->size; i++) {
      if (p->tiles[i] == 0) {
          empty_index = i; 
          break;
      }
  }

  // check if empty tile can move in the specified direction
  int target_index = -1;
  if (direction == 'u' && empty_index < p->size * (p->size - 1)) {
    target_index = empty_index + p->size;
  } else if (direction == 'l' && empty_index % p->size < p->size - 1) {
    target_index = empty_index + 1;
  } else if (direction == 'd' && empty_index >= p->size) {
    target_index = empty_index - p->size;
  } else if (direction == 'r' && empty_index % p->size > 0) {
    target_index = empty_index - 1;
  } else {
      return 0; // invalid character entered as direction
  }

  // swap values from tile we want to slide and tile being slid into
  p->tiles[empty_index] = p->tiles[target_index];
  p->tiles[target_index] = 0;
  return 1;
}

/**
 * Gets parity / reverse direction of specified direction
 * 
 * @param char direction
 * 
 * return char of opposite direction (if valid direction entered)
 * return '\0' if invalid direction was entered
*/
int get_parity(char direction) {
  switch (direction) {
    case 'u': return 'd';
    case 'd': return 'u';
    case 'l': return 'r';
    case 'r': return 'l';
  }
  return '\0';
}

/**
 * Handles V command (solve) by calling its recursive helper function
 * 
 * @param Puzzle *p
 * @param char steps[]: steps to solve puzzle if possible
 * 
 * return 1 if valid, 0 if invalid
*/
int handle_V_command(Puzzle* p, char steps[]) {
  return V_helper(p, steps, 0);
}

/**
 * Recursive helper function for the V command
 * 
 * @param Puzzle *p
 * @param char steps[]: steps to solve puzzle if possible
 * @param int cur_steps
 * 
 * return -1 if unable to be solved in MAX_STEPS 
 * return recursive call for V_helper again
*/
int V_helper(Puzzle *p, char steps[], int cur_steps) {
  if (puzzle_is_solved(p))
    return cur_steps;
    

  if (cur_steps >= MAX_STEPS)
    return -1;

  char directions[4] = {'u', 'd', 'l', 'r'};
  for (int i = 0; i < 4; i++) {
    char direction = directions[i];
    char prev_direction = cur_steps > 0 ? steps[cur_steps-1] : '\0';

    if (direction != get_parity(prev_direction)) {
      Puzzle* copy = copy_puzzle(p);
      if (slide_tile(copy, direction)) {
        steps[cur_steps] = direction;
        int result = V_helper(copy, steps, cur_steps + 1);
        if (result != -1) {
          puzzle_destroy(copy);
          return result;
        }
      }
      puzzle_destroy(copy);
    }
  }
  return -1;
}