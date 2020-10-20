#ifndef SEGMENTATION__H
#define SEGMENTATION__H

#include<SDL/SDL.h>

void segmentation_line(SDL_Surface *image, SDL_PixelFormat *fmt);
void segmentation_columns(SDL_Surface* img, int begin_line, int end_line,
SDL_PixelFormat *fmt);
#endif
