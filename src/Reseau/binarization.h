#ifndef BINARIZATION_H
#define BINARIZATION_H

#include<SDL/SDL.h>
Uint32 binarization_pixel(Uint32 pixel,SDL_PixelFormat *fmt, int threshold);
void binarization(SDL_Surface *surface, SDL_PixelFormat *fmt, int threshold);

#endif
