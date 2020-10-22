#include "displayBMP.h"

int displayBMP(SDL_Surface *image)
{
    // Initialize screen and window
    SDL_Surface *screen = NULL;
    SDL_Rect window;

    window.x = 0;
    window.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    // Starting the screen
    screen = SDL_SetVideoMode
    (image->w,image->h, image->format->BitsPerPixel, SDL_ANYFORMAT);

    // Merging image and screen
    SDL_BlitSurface(image, NULL, screen, &window);

    SDL_Flip(screen);
    pause();

    // Free ressources generated for the image
    SDL_FreeSurface(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}
