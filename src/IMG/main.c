#include <stdio.h>
#include <SDL/SDL.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"
#include "grey_level.h"
#include "binarization.h"
#include "img_filter.h"

int main()
{
    char *path = "images/LAND2.BMP";
    SDL_Surface *image = loadBMP(path);
    grey_level(image);
    filter(image);
    binarization(image, 128);
    displayBMP(image);
}
