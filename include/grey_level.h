#ifndef LEVEL_GREY_H
#define LEVEL_GREY_H

#include<SDL/SDL.h>
Uint32 grey_level_pixel(Uint32 pixel, SDL_PixelFormat *fmt);
void grey_level(SDL_Surface *surface);
#endif
