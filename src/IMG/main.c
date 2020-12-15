#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "displayBMP.h"
#include "pixelBMP.h"
#include "grey_level.h"
#include "binarization.h"
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
  SDL_Matrix mat = segmentation_y(image);
  resize_all(mat);
  size_t nb_arr = mat.nb_arr;
  size_t *len_arr = mat.len_arr;
  SDL_Surface ***lines = mat.lines;
  for(size_t i = 0; i < nb_arr; i ++){
    for(size_t j = 0; j < len_arr[i]; j ++)
      displayBMP(lines[i][j]);
  }
  free(lines);
  free(len_arr);
  SDL_FreeSurface(image);

  return 0;
}
