#include <stdio.h>
#include <SDL/SDL.h>

int loadBMP()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *image = NULL;
  image = SDL_LoadBMP("../images/LAND2.BMP");
  printf("%s", image);
  SDL_Quit();
  return 0;
}

int hello ()
{
    printf ("Hello World\n");
    return 0;
}
