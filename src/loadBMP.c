#include "loadBMP.h"

SDL_Surface *loadBMP(char *path)
{
    // Initialize the image
    SDL_Surface *image = NULL;
    // Load the image into image
    image = SDL_LoadBMP(path);
    // Return the image as a SDL_Surface
    return image;
}
