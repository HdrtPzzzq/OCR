#include"binarization.h"
#include"pixelBMP.h"
unsigned int binarization_pixel(unsigned int pixel, SDL_PixelFormat *fmt, int threshold)
{
    SDL_Color color;
    SDL_GetRGB(pixel, fmt, &color.r, &color.g, &color.b);
    // We create a color where we stock the r,g,b values of the pixel.
    if(color.r > threshold)
    {
        return SDL_MapRGB(fmt, 255, 255, 255);
    //Because every r,g,b values are equal(because we have already grey_level
    //the surface) we just have to compare a value for example the r value to
    //the threshold. If it is over the threshold, it will be a black pixel.
    }
    return SDL_MapRGB(fmt, 0, 0, 0);
    //Otherwise, it will be a black pixel.
}
void binarization(SDL_Surface *surface, int threshold)
{
    SDL_LockSurface(surface);
    //We lock the surface to modify the pixel in it.
    for(int i = 0; i < surface->w; i ++)
    {
        for(int j = 0; j < surface->h; j ++)
        {
            putpixel
            (surface, i, j, binarization_pixel
            (getpixel(surface, i, j), surface->format, threshold));
    //We parse through the matrix of pixel to do the binarizaion function 
    //on every pixelof the surface.
        }
    }
    //We unlock the surface when we have finished our modification
    SDL_UnlockSurface(surface);
}
