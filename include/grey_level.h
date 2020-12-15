#ifndef GREY_LEVEL_H
#define GREY_LEVEL_H

#include"pixelBMP.h"
Uint32 grey_level_pixel(Uint32 pixel, SDL_PixelFormat *fmt);
void grey_level(SDL_Surface *surface);
#endif
