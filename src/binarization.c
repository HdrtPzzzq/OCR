#include"binarization.h"
#include"pixelBMP.h"
Uint32 binarization_pixel(Uint32 pixel, SDL_PixelFormat *fmt, int seuil)
{
    SDL_Color color;
    SDL_GetRGB(pixel,fmt,&color.r,&color.g,&color.b);
    if(color.r>seuil)
    {
        return SDL_MapRGB(fmt,255,255,255);
    }
    return SDL_MapRGB(fmt,0,0,0);
}
void binarization(SDL_Surface *surface,SDL_PixelFormat *fmt,int seuil)
{
    SDL_LockSurface(surface);
    for(int i=0;i<surface->w;i++)
    {
        for(int j=0;j<surface->h;j++)
        {
            putpixel
            (surface,i,j,binarization_pixel(getpixel(surface,i,j),fmt,seuil));
        }
    }
    SDL_UnlockSurface(surface);
}
