#ifndef IMG_FILTER_H
#define IMG_FILTER_H

#include <SDL/SDL.h>
#include "pixelBMP.h"

void filter(SDL_Surface *image);
unsigned int get_9(SDL_Surface *image, int x, int y);
void array_swap(unsigned char array[], size_t i, size_t j);
void array_select_sort(unsigned char array[], size_t len);

/*
int get_x(int x);
int get_range_x(int w, int x);
int get_y(int y);
int get_range_y(int h, int y);
*/
#endif
