#include "displayBMP.h"

SDL_Surface *displayBMP(SDL_Surface *image)
{
    // Initialize screen and window
    SDL_Surface *screen = NULL;
    SDL_Rect window;

    window.x = 0;
    window.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    // Starting the screen
    screen = SDL_SetVideoMode(image->w, image->h, image->format->BitsPerPixel, SDL_HWSURFACE);

    // Merging image and screen
    SDL_BlitSurface(image, NULL, screen, &window);

    SDL_Flip(screen);
    pause();

    // Free ressources generated for the image
    SDL_FreeSurface(image);
    SDL_Quit();

    return screen;
}

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}
