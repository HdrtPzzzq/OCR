#include"grey_level.h"

Uint32 grey_level(Uint32 pixel)
{
    //create a color where we gonna stock the g value, b value and r value 
    SDL_Color color;
    SDL_GetRBG(pixel,format,&color.r,&color.g,&color.b);
    //get the level of grey of the pixel by the next formule using the
    //componants of color
    return (Uint32)(color.r * 0,2126 + color.v * 0,7152 + color.b * 0,0722);
}
