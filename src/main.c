#include <stdio.h>
#include <SDL/SDL.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"

char *path = "../images/LAND2.BMP";

int main()
{
    char *path = "images/LAND2.BMP";
    SDL_Surface *image = loadBMP(path);
    displayBMP(image);
}
