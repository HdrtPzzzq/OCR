#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "displayBMP.h"
#include "pixelBMP.h"
#include "grey_level.h"
#include "binarization.h"
#include "img_filter.h"
#include "segmentation.h"

int main()
{
  //char *colored = "images/text_with_color.bmp";
  char *raw = "images/no_preprocess.bmp";

  SDL_Surface *image = SDL_LoadBMP(raw);
/*
  // |==DISPLAY_TEST==|
  image = loadBMP(colored);
  displayBMP(image);

  // |==GRAY_LEVEL==|
  image = loadBMP(colored);
  grey_level(image);
  displayBMP(image);

  //filter(image);
  // |==BINARIZATION==|
  image = loadBMP(colored);
  grey_level(image);
  binarization(image, 128);
  displayBMP(image);

  // |==SEGMENTATION_TEST==|
  image = loadBMP(raw);
  displayBMP(image);
*/
  //|==SEGMENTED_TEST==|
  SDL_Surface ***lines = segmentation_y(image);
  for(int i = 0; i < 3; i ++){
    for(int j = 0; j < 3; j ++)
      displayBMP(lines[i][j]);
  }
  free(lines);
  SDL_FreeSurface(image);

  return 0;
}
