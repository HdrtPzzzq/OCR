#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <SDL/SDL.h>
#include "pixelBMP.h"

typedef struct SDL_Matrix{
  SDL_Surface ***lines;
  size_t nb_arr;
  size_t *len_arr;
} SDL_Matrix;

SDL_Matrix segmentation_y(SDL_Surface *image);

SDL_Surface **segmentation_x(SDL_Surface *image, int start_y, int end_y, size_t *len);

void resize_all(SDL_Matrix mat);

int is_line_white(SDL_Surface *image, int y);

int is_column_white(SDL_Surface *image, int x, int start_y, int end_y);

void draw_line(SDL_Surface *image, int y);

void draw_column(SDL_Surface *image, int x, int start_y, int end_y);

#endif
