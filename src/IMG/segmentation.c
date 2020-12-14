#include "segmentation.h"
#include "displayBMP.h"
#include <stdlib.h>

SDL_Matrix segmentation_y(SDL_Surface *image)
{
  size_t size = sizeof(SDL_Surface*); // Value used for realloc'ing memory.
  SDL_Surface ***lines = NULL; // Array to store surfaces of lines.
  size_t nb_arr = 0; // Length of the array.
  size_t *len_arr = NULL;
  size_t size_len = sizeof(size_t);
  // Temporary variables to get y coordinates of characters.
  int start_y = 0;
  int end_y = 0;

  // Simulates boolean values to determinate if characters are present or not.
  int start = 0;
  int end = 0;

  for(int y = 0; y < image->h; y ++) // Parse image's y coordinates.
  {
    if(is_line_white(image, y)) // No trace of characters.
    {
      draw_line(image, y); // Visual way to split lines of characters.
      if(start && !end) // If the drawn line is just after a line.
      {
        end = 1;
        end_y = y - 1; // Get the end of line coordinate.
      }
    }
    else
    {
      if(!start) // We just met the beginning of a line.
      {
        start = 1;
        start_y = y; // Get the start of the line.
      }
    }
    if(start && end) // We have a whole line
    {
      size += sizeof(SDL_Surface**);
      size_len += sizeof(size_t);
      lines = realloc(lines, size);
      len_arr = realloc(len_arr, size_len);

      // Call the same function on x.
      size_t len;
      SDL_Surface **line = segmentation_x(image, start_y, end_y, &len);
      lines[nb_arr] = line;
      len_arr[nb_arr] = len;
      (nb_arr) ++;
      start = 0; // Start over with a new line.
      end = 0;
    }
  }
  SDL_Matrix mat = {lines, nb_arr, len_arr};
  return mat;
}

SDL_Surface **segmentation_x(SDL_Surface *image, int start_y, int end_y, size_t *len)
{
  size_t size = sizeof(SDL_Surface); // Value used for realloc'ing memory.
  SDL_Surface **characters = NULL; // Array to store surfaces of characters.
  *len = 0; // Length of the array.
  // Temporary variables to get x coordinates of characters.
  int start_x = 0;
  int end_x = 0;

  // Simulates boolean values to determinate if characters are present or not.
  int start = 0;
  int end = 0;

  for(int x = 0; x < image->w; x ++)
  {
    if(is_column_white(image, x, start_y, end_y))
    {
      draw_column(image, x, start_y, end_y); // Visual characters identification.
      if(start && !end)
      {
        end = 1;
        end_x = x - 1;
      }
    }
    else
    {
      if(!start)
      {
        start = 1;
        start_x = x;
      }
    }
    if(start && end)
    {
      // Initialize new surface.
      SDL_Surface *dst = SDL_CreateRGBSurface(0, end_x - start_x, end_y - start_y, 32, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask);
      SDL_Rect srcrect;
      srcrect.x = start_x;
      srcrect.y = start_y;
      srcrect.w = end_x - start_x;
      srcrect.h = end_y - start_y;
      // Copy a character in the new surface.
      SDL_BlitSurface(image, &srcrect, dst, NULL);
      // Add the surface in an array.
      size += sizeof(SDL_Surface*);
      characters = realloc(characters, size);
      characters[*len] = dst;
      (*len) ++;

      start = 0;
      end = 0;
    }
  }
  return characters;
}


int is_line_white(SDL_Surface *image, int y)  // Well entitled function...
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

int is_column_white(SDL_Surface *image, int x, int start_y, int end_y) //...
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

void draw_line(SDL_Surface *image, int y) //...
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

void draw_column(SDL_Surface *image, int x, int start_y, int end_y)//...
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
