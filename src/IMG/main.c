#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"
#include "grey_level.h"
#include "binarization.h"
#include "segmentation.h"
#include "noise_reduction.h"

int main()
{
  char *colored = "images/text_with_color.bmp";
  char *raw = "images/no_preprocess.bmp";

  SDL_Surface *image;

  // |==DISPLAY_TEST==|
  image = loadBMP(colored);
  displayBMP(image);

  // |==GRAY_LEVEL==|
  image = loadBMP(colored);
  grey_level(image);
  displayBMP(image);

  // |==BINARIZATION==|
  image = loadBMP(colored);
  grey_level(image);
  binarization(image, 128);
  displayBMP(image);

  // |==SEGMENTATION_TEST==|
  image = loadBMP(raw);
  displayBMP(image);

  // |==SEGMENTED_TEST==|
  image = loadBMP(raw);
  segmentation_y(image);
  displayBMP(image);

  return 0;
}
