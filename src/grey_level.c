#include"grey_level.h"
#include"pixelBMP.h"
Uint32 grey_level_pixel(Uint32 pixel, SDL_PixelFormat *fmt )
{
    //create a color where we gonna stock the g value, b value and r value of
    //the pixel in th input. 
    SDL_Color color;
    SDL_GetRGB(pixel,fmt,&color.r,&color.g,&color.b);
    //get the level of grey of the pixel by the next formule using the
    //componants of color.
    Uint8 gris = (color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722);
    return SDL_MapRGB(fmt,gris,gris,gris);    
}

void grey_level(SDL_Surface *surface, SDL_PixelFormat *fmt)
{
    SDL_LockSurface(surface);
    for(int i=0;i<surface->w;i++)
    {
        for(int j=0;j<surface->h;j++)
        {
            putpixel(surface,i,j,grey_level_pixel(getpixel(surface,i,j),fmt));
        }
    }
    SDL_UnlockSurface(surface);
}
