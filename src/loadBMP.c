#include "loadBMP.h"

SDL_Surface *loadBMP(char *path)
{
    // Initialize the image
    SDL_Surface *image = NULL;
    // Load the image into image
    image = SDL_LoadBMP(path);
    // Return the image as a SDL_Surface
    return image;
}

int displayBMP(SDL_Surface *image)
{
    // Initialize screen and window
    SDL_Surface *screen = NULL;
    SDL_Rect window;

    window.x = 0;
    window.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    // Starting the screen
    screen = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE);

    // Merging image and screen
    SDL_BlitSurface(image, NULL, screen, &window);

    SDL_Flip(screen);
    pause();

    // Free ressources generated for the image
    SDL_FreeSurface(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}

Uint32 getpixel(SDL_Surface *image, int x, int y)
{
    int pixel_bytes = image->format->BytesPerPixel;
    // Here pixel is the address to the pixel we want to retrieve
    Uint8 *pixel = (Uint8 *)image->pixels + y * image->pitch + x * pixel_bytes;

    switch (pixel_bytes)
    {
        case 1:
            return *pixel;
            break;

        case 2:
            return *(Uint16 *)pixel;
            break;

        case 3:
            // If most significant byte is pixel[0] shift it.
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                // Return one Uint32 due to bitwise or
                return pixel[0] << 16 | pixel[1] << 8 | pixel[2];
            else
                return pixel[0] | pixel[1] << 8 | pixel[2] << 16;
            break;

        case 4:
            return *(Uint32 *)pixel;
            break;

        default:
            // To avoid warnings
            return 0;
    }
}
