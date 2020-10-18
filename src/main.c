#include <stdio.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"

int main()
{
    char *path = "images/LAND2.BMP";
    SDL_Surface *image = loadBMP(path);
    displayBMP(image);
}
