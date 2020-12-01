#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <SDL/SDL.h>
#include "pixelBMP.h"

SDL_Surface ***segmentation_y(SDL_Surface *image);

SDL_Surface **segmentation_x(SDL_Surface *image, int start_y, int end_y);

int is_line_white(SDL_Surface *image, int y);

int is_column_white(SDL_Surface *image, int x, int start_y, int end_y);

void draw_line(SDL_Surface *image, int y);

void draw_column(SDL_Surface *image, int x, int start_y, int end_y);

#endif
