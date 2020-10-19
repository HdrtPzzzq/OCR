#include <stdio.h>
#include <SDL/SDL.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"
#include"grey_level.h"

char *path = "../images/LAND2.BMP";

int main()
{
    char *path = "images/LAND2.BMP";
    SDL_Surface *image = loadBMP(path);
    SDL_PixelFormat *fmt = image->format;
    grey_level(image,fmt);
    displayBMP(image);
}
