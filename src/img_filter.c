#include <SDL/SDL.h>
#include "img_filter.h"
#include "pixelBMP.h"

// Filter is trying to parse a matrix, and to put a pixel from the color
// returned by get_9
void filter(SDL_Surface *image)
{
    SDL_LockSurface(image);
    for(int x = 1; x < image->w - 1; x ++)
    {
        for(int y = 1; y < image->h - 1; y ++)
        {
            putpixel(image, x, y, get_9(image, x, y));
        }
    }
    SDL_UnlockSurface(image);
}

// Get_9 is a function designed to return the middle value of an array,
// of len 9, which represents the 8 pixel around and the current pixel,
// so that the noise on the image is reduced
unsigned int get_9(SDL_Surface *image, int x, int y)
{
    unsigned char list_of_grey[9];
    SDL_Color c;
    /* Temp var designed to deal with the border of the image,
     * doesnt work yet
    int i = get_x(x);
    int j = get_y(y);
    int range_i = get_range_x(w, x);
    int range_j = get_range_y(h, y);
    */
    // Parsing the 9th pixels
    for(int i = x - 1; i <= x + 1 ; i ++)
    {
        for(int j = y - 1; j <= y + 1; j ++)
        {
            // Getting current color, anyway the image is supposed to already
            // be grey so that r = b = g
            SDL_GetRGB(getpixel(image, i, j), image->format, &c.r, &c.g, &c.b);
            // Moving in array with 2 parameter x and y, trust me it works
            list_of_grey[(i - x + 1)  * (j - y + 2)] = c.r;
        }
    }
    // Sort the array so that the middle value is the average of the array.
    array_select_sort(list_of_grey, 9);
    c.r = list_of_grey[sizeof(list_of_grey) / 2];
    // Return the average color in unsigned int format
    return SDL_MapRGB(image->format, c.r, c.r, c.r);
}

void array_swap(unsigned char array[], size_t i, size_t j)
{
    unsigned char temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void array_select_sort(unsigned char array[], size_t len)
{
  size_t index;
  unsigned char min;
  for(size_t i = 0; i < len; i ++)
  {
    index = i;
    min = array[i];
    for (size_t j = i; j < len; j ++)
    {
      if (array[j] < min)
      {
        index = j;
        min = array[j];
      }
    }
    array_swap(array, i, index);
  }
}

/* Related to the previous fields, to be fixed
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
*/
