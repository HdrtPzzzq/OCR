#ifndef PIXELBMP_H
#define PIXELBMP_H

#include <SDL/SDL.h>

Uint32 getpixel(SDL_Surface *image, int x, int y);
void putpixel(SDL_Surface *image, int x, int y, Uint32 pixel);

#endif
