#include "segmentation.h"

void segmentation_y(SDL_Surface *image)
{
    int start_y = 0;
    int end_y = 0;
    int start = 0;
    int end = 0;
    for(int y = 0; y < image->h; y ++)
    {
        if(is_line_white(image, y))
        {
            draw_line(image, y);
            if(start && !end)
            {
                end = 1;
                end_y = y - 1;
            }
        }
        else
        {
            if(!start)
            {
                start = 1;
                start_y = y;
            }
        }
        if(start && end)
        {
            segmentation_x(image, start_y, end_y);
            start = 0;
            end = 0;
        }
    }
}

void segmentation_x(SDL_Surface *image, int start_y, int end_y)
{
    for(int x = 0; x < image->w; x ++)
    {
        if(is_column_white(image, x, start_y, end_y))
            draw_column(image, x, start_y, end_y);
    }
}


int is_line_white(SDL_Surface *image, int y)
{
    unsigned int pixel;
    SDL_Color c;
    for(int x = 0; x < image->w; x ++)
    {
        pixel = getpixel(image, x, y);
        SDL_GetRGB(pixel, image->format, &c.r, &c.g, &c.b);
        if(c.r != 255 || c.g != 255 || c.b != 255)
            return 0;

    }
    return 1;
}

int is_column_white(SDL_Surface *image, int x, int start_y, int end_y)
{
    unsigned int pixel;
    SDL_Color c;
    for(; start_y < end_y; start_y ++)
    {
        pixel = getpixel(image, x, start_y);
        SDL_GetRGB(pixel, image->format, &c.r, &c.g, &c.b);
        if(c.r != 255 || c.g != 255 || c.b != 255)
            return 0;

    }
    return 1;
}

void draw_line(SDL_Surface *image, int y)
{
    SDL_LockSurface(image);
    unsigned int pixel;
    for(int x = 0; x < image->w; x ++)
    {
        pixel = SDL_MapRGB(image->format, 255, 0, 0);
        putpixel(image, x, y, pixel);
    }
    SDL_UnlockSurface(image);
}

void draw_column(SDL_Surface *image, int x, int start_y, int end_y)
{
    SDL_LockSurface(image);
    unsigned int pixel;
    for(; start_y < end_y; start_y ++)
    {
        pixel = SDL_MapRGB(image->format, 255, 0, 0);
        putpixel(image, x, start_y, pixel);
    }
    SDL_UnlockSurface(image);
}
