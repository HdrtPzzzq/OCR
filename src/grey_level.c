#include"grey_level.h"

Uint32 grey_level(Uint32 pixel)
{
    //create a color where we gonna stock the g value, b value and r value of
    //the pixel in th input. 
    SDL_Color color;
    SDL_GetRBG(pixel,format,&color.r,&color.g,&color.b);
    //get the level of grey of the pixel by the next formule using the
    //componants of color.
    Uint8 = (color.r * 0,2126 + color.v * 0,7152 + color.b * 0,0722);
    return SDL_MapRGB(s->format,gris,gris,gris);
}
