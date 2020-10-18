#ifndef LOADBMP_H
#define LOADBMP_H

#include <unistd.h>
#include <SDL/SDL.h>

SDL_Surface *loadBMP(char *path);
int displayBMP();

#endif
