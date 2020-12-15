#include "pixelBMP.h"
/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
unsigned int getpixel(SDL_Surface *image, int x, int y)
{
    // This represents the length of a pixel.
    int pixel_bytes = image->format->BytesPerPixel;
    /* Here pixel is the address to the pixel we want to retrieve.
     * We move in matrix using adress not index.
     * To illustrate :
     *                (pixel + x) access the adress of the xth element in array
     *                Then (pixel + x * row) access the xth row in a matrix
     *                etc...*/
    unsigned char *pixel = (unsigned char *)image->pixels + y * image->pitch + x * pixel_bytes;
    // Treat any color depth
    switch (pixel_bytes)
    {
        // 256 colors
        case 1:
            return *pixel;
            break;
        // 65 536 colors
        case 2:
            return *(Uint16 *)pixel;
            break;
        // RGB color
        case 3:
            // If most significant byte is pixel[0] shift it.
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                // Return one unsigned int due to bitwise or
                return pixel[0] << 16 | pixel[1] << 8 | pixel[2];
            else
                    // BLUE       GREEN           RED
                return pixel[0] | pixel[1] << 8 | pixel[2] << 16;
            break;
        // SHOULDNT HAPPEN, this depth doesn't exist for BMP format.
        case 4:
            return *(unsigned int *)pixel;
            break;

        default:
            // Avoid warnings
            return 0;
    }
}
/* If anything is confused check getpixel
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *image, int x, int y, unsigned int pixel)
{
    int pixel_bytes = image->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    unsigned char *n_pix = (unsigned char *)image->pixels + y * image->pitch + x * pixel_bytes;

    switch(pixel_bytes) {
    case 1:
      *n_pix = pixel;
      break;

    case 2:
      *(Uint16 *)n_pix = pixel;
      break;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      {
        // Only keep the less significants bytes
        n_pix[0] = (pixel >> 16) & 0xff;
        n_pix[1] = (pixel >> 8) & 0xff;
        n_pix[2] = pixel & 0xff;
      }
      else
      {
        n_pix[0] = pixel & 0xff; // Blue
        n_pix[1] = (pixel >> 8) & 0xff; // Green
        n_pix[2] = (pixel >> 16) & 0xff; // Red
      }
      break;

    case 4:
      *(unsigned int *)n_pix = pixel;
      break;
      // No need default since type is void
    }
}
