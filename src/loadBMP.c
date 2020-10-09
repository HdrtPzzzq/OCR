#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>

int displayBMP(char *path)
{
    // Initialize screen, image and window
    SDL_Surface *screen = NULL;
    SDL_Surface *image = NULL;
    SDL_Rect window;

    window.x = 0;
    window.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    // Starting the screen
    screen = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE);

    // Loading a BMP in a surface
    image = SDL_LoadBMP(path);

    // Merging image and screen
    SDL_BlitSurface(image, NULL, screen, &window);

    SDL_Flip(screen);
    pause();

    // Free ressources generated for the image
    SDL_FreeSurface(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}

int hello ()
{
    printf ("Hello World\n");
    return 0;
}
