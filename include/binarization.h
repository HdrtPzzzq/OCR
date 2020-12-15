#ifndef BINARIZATION_H
#define BINARIZATION_H

#include<SDL/SDL.h>
unsigned int binarization_pixel(unsigned int pixel, SDL_PixelFormat *fmt, int threshold);
void binarization(SDL_Surface *surface, int threshold);

#endif
