#include <stdio.h>
#include <SDL/SDL.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"
#include"grey_level.h"
#include"binarization.h"
#include"segmentation.h"

int main()
{
    char *path = "images/lorem.bmp";
    SDL_Surface *image = loadBMP(path);
    //printf("%d,%d,%u",image->w,image->h,image->format->BytesPerPixel);
    SDL_PixelFormat *fmt = image->format;
    grey_level(image,fmt);
    binarization(image,fmt,128);
    segmentation_ligne(image,fmt);
    displayBMP(image);
}
