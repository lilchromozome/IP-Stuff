#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ppm_io.h"
#include "puzzle.h"

int main(int argc, char **argv) {
  if (argc > 2) {
    fprintf(stderr, "Usage: ./puzzle [<command file>]\n");
    return 1;
  }

  // opens file
  FILE *fp = argc == 1 ? stdin : fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open input file\n");
    return 1;
  }

  // scans command argument
  Puzzle* puzzle = NULL;
  char command;
  while (fscanf(fp, " %c", &command) != EOF) {
    if (puzzle == NULL && !(command == 'C' || command == 'Q' || command == 'I')) {
      fprintf(stderr, "Invalid command '%c'\n", command); // error cond 1
      return 1;
    }

    // runs through all possible commands and executes accordingly
    switch (command) {
      case 'C': {
        int size;
        if (fscanf(fp, " %d", &size) != 1) {
          fprintf(stderr, "Invalid input\n"); // non-int entered for size
          return 1;
        }
        if (size < 2 || size > 20) {
          fprintf(stderr, "Invalid puzzle size\n"); // error cond 3
          return 1;
        }
        puzzle = puzzle_create(size);
        break;
      }
      case 'T': {
        int cur_val;
        for (int i = 0; i < puzzle->size * puzzle->size; i++) {
          if (fscanf(fp, " %d", &cur_val) != 1) {
            fprintf(stderr, "Invalid input\n"); // non-int entered for tile value
            return 1;
          }
          if (!isValidTileValue(puzzle, cur_val, i)) {
            fprintf(stderr, "Puzzle cannot be moved in specified direction\n");
            return 1;
          }
          puzzle->tiles[i] = cur_val;
        }
        break;
      }
      case 'I': {
        char* img_fname = (char*) malloc(sizeof(char) * 255);
        if (fscanf(fp, " %s", img_fname) != 1) {
          fprintf(stderr, "Invalid input\n");
          free(img_fname); //added
          return 1;
        }
        FILE* fp_img = fopen(img_fname, "rb");
        // free(img_fname);
        if (fp_img == NULL) {
          fprintf(stderr, "Could not open image file '%s'\n", img_fname);
          free(img_fname); //added
          return 1;
        }
        puzzle->img = ReadPPM(fp_img);
        fclose(fp_img);
        free(img_fname); //added
        break;
      }
      case 'P': {
        print_puzzle(puzzle, stdout);
        break;
      }
      case 'W': {
        if (puzzle->img == NULL) {
          fprintf(stderr, "No image\n");
          return 1;
        }
        char* img_fname = (char*) malloc(sizeof(char) * 255);
        char* config_fname = (char*) malloc(sizeof(char) * 255);
        if (fscanf(fp, " %s", img_fname) != 1) {
          fprintf(stderr, "Invalid input\n");
          return 1;
        }
        if (fscanf(fp, " %s", config_fname) != 1) {
          fprintf(stderr, "Invalid input\n");
          return 1;
        }
        FILE* fp_img = fopen(img_fname, "wb");
        //free(img_fname);
        if (fp_img == NULL) {
          fprintf(stderr, "Could not open output image file '%s'\n", img_fname);
          free(img_fname); //added
          free(config_fname);
          return 1;
        }
        FILE* fp_config = fopen(config_fname, "w");
        //free(config_fname);
        if (fp_config == NULL) { // fixed typo
          fprintf(stderr, "Could not open output puzzle file '%s'\n", config_fname);
          free(config_fname); //added
          free(img_fname);
          return 1;
        }

        if (handle_W_command(puzzle, fp_img, fp_config) == -1) {
          fprintf(stderr, "Could not write puzzle data %s\n", img_fname);
          free(img_fname); //added
          free(config_fname);
          return 1;
        }

        fclose(fp_img);
        fclose(fp_config);
        free(img_fname); //added
        free(config_fname);        
        break;
      }
      case 'S': {
        char dir;
        if (fscanf(fp, " %c", &dir) != 1) {
          fprintf(stderr, "must include a single character after the S char");
          return 1;
        }
        if (!(dir == 'u' || dir == 'd' || dir == 'l' || dir == 'r')) {
          fprintf(stderr, "must include a valid character after the S char\n");
          return 1;
        }
        if (!slide_tile(puzzle, dir)) {
          fprintf(stderr, "Puzzle cannot be moved in specified direction");
          return 1;
        }
        break;
      }
      case 'K': {
        if (puzzle_is_solved(puzzle)) {
            printf("Solved\n");
        } else {
            printf("Not solved\n");
        }
        break;
      }
      case 'V': {
        char* steps = (char*) malloc(sizeof(char) * MAX_STEPS);
        int num_steps = handle_V_command(puzzle, steps);
        if (num_steps == -1) {
          printf("No solution found\n");
          free(steps);
        } else {
          for (int i = 0; i < num_steps; i++) {
            printf("S %c\n", steps[i]);
          }
          free(steps);
        }
        break;
      }
      case 'Q': {
        free(puzzle->img->data);
        free(puzzle->img);
        puzzle_destroy(puzzle);
        fclose(fp);
        return 0;
      }
      default: {
        fprintf(stderr, "Invalid command '%c'\n", command);
        return -1;
      }
    }
  }

  if (puzzle != NULL) puzzle_destroy(puzzle);
  fclose(fp);
  return 0;
}
