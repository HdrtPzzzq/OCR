#include <SDL/SDL.h>
#include "img_filter.h"
#include "pixelBMP.h"

void filter(SDL_Surface *image)
{
    SDL_LockSurface(image);
    for(int y = 0; y < image->h; y ++)
    {
        for(int x = 0; x < image->w; x ++)
        {
            putpixel(image, x, y, sum_9(image, x, y));
        }
    }
    SDL_UnlockSurface(image);
}

Uint32 sum_9(SDL_Surface *image, int x, int y)
{
    Uint32 sum;
    int i = get_x(x);
    int j = get_y(y);
    int range_i = get_range_x(image->w, x);
    int range_j = get_range_y(image->h, y);

    for(; j <= range_j; j ++)
    {
        for(; i <= range_i; i ++)
        {
            sum += getpixel(image, i, j);
        }
    }
    return sum / 9;
}

int get_x(int x)
{
    int i = x - 1;
    if(x == 0)
        i ++;
    return i;
}

int get_range_x(int w, int x)
{
    int range_i = x + 1;
    if(x == w - 1)
        range_i --;
    return range_i;
}

int get_y(int y)
{
    int j = y - 1;
    if(y == 0)
        j ++;
    return j;
}

int get_range_y(int h, int y)
{
    int range_y = y + 1;
    if (y == h - 1)
        range_y --;
    return range_y;
}
