#ifndef DISPLAYBMP_H
#define DISPLAYBMP_H

#include <unistd.h>
#include <err.h>
#include <SDL/SDL_image.h>

void displayBMP(SDL_Surface *image);
void update_surface(SDL_Surface* screen, SDL_Surface* image);
void wait_for_keypressed();
void init_sdl();

#endif
