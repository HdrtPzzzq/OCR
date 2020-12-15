#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "displayBMP.h"
#include "pixelBMP.h"
#include "grey_level.h"
#include "binarization.h"
#include "segmentation.h"
#include "Network.h"
#include "getvalues.h"
#include "savevalues.h"

int main()
{
  //---------------------------------------------------------------------------

  //char *colored = "images/text_with_color.bmp";
  char *raw = "images/no_preprocess.bmp";

  SDL_Surface *image_r = SDL_LoadBMP(raw);

  // |==DISPLAY_TEST==|
  //displayBMP(image);

  // |==GRAY_LEVEL==|
  grey_level(image_r);
  //displayBMP(image);

  // |==BINARIZATION==|
  //grey_level(image);
  binarization(image_r, 128);
  //displayBMP(image);

  //|==SEGMENTED_TEST==|
  SDL_Matrix mat = segmentation_y(image_r);
  resize_all(mat);

  size_t nb_arr = mat.nb_arr;
  size_t *len_arr = mat.len_arr;
  SDL_Surface ***lines = mat.lines;

  size_t total_length = 0;

  for(size_t x = 0; x < nb_arr; x ++)
  {
    for(size_t y = 0; y < len_arr[x]; y ++)
    {
      total_length += 1;
    }
  }
  struct size max = get_max(mat);
  double data[total_length][max.h * max.w];
  size_t where = 0;

  for(size_t i = 0; i < nb_arr; i ++){
    for(size_t j = 0; j < len_arr[i]; j ++)
    {
      SDL_Surface *image = lines[i][j];
      for(int k = 0; k < image->h; k ++)
      {
        for(int l = 0; l < image->w; l ++)
        {
          SDL_Color color;
          Uint32 pixel  = getpixel(image, k, l);
          SDL_GetRGB(pixel, image->format, &color.r, &color.g, &color.b);
          if(color.r == 0){data[0][k * image->w + l] = 1;}
          else{data[where][k * image->w + l] = 0;}
        }
      }
      where ++;
    }
  }
  free(lines);
  free(len_arr);
  SDL_FreeSurface(image_r);

  //---------------------------------------------------------------------------
  SDL_Surface *image1 = SDL_LoadBMP("images/1.bmp");
  binarization(image1, 128);

  double donnee[4][image1->h * image1->w];

  for(int i = 0; i < image1->h; i ++)
  {
    for(int j = 0; j < image1->w; j ++)
    {
      SDL_Color color;
      Uint32 pixel  = getpixel(image1, i, j);
      SDL_GetRGB(pixel, image1->format, &color.r, &color.g, &color.b);
      if(color.r == 0){donnee[0][i*image1->w + j] = 1;}
      else{donnee[0][i*image1->w + j] = 0;}
    }
  }

  SDL_Surface *image2 = SDL_LoadBMP("images/2.bmp");
  binarization(image2, 128);

  for(int i = 0; i < image2->h; i ++)
  {
    for(int j = 0; j < image2->w; j ++)
    {
      SDL_Color color;
      Uint32 pixel  = getpixel(image2, i, j);
      SDL_GetRGB(pixel, image2->format, &color.r, &color.g, &color.b);
      if(color.r == 0){donnee[1][i*image2->w + j] = 1;}
      else{donnee[1][i*image2->w + j] = 0;}
    }
  }

  SDL_Surface *image3 = SDL_LoadBMP("images/3.bmp");
  binarization(image3, 128);

  for(int i = 0; i < image3->h; i ++)
  {
    for(int j = 0; j < image3->w; j ++)
    {
      SDL_Color color;
      Uint32 pixel  = getpixel(image3, i, j);
      SDL_GetRGB(pixel, image3->format, &color.r, &color.g, &color.b);
      if(color.r == 0){donnee[2][i*image3->w + j] = 1;}
      else{donnee[2][i*image3->w + j] = 0;}
    }
  }

  SDL_Surface *image4 = SDL_LoadBMP("images/4.bmp");
  binarization(image4, 128);

  for(int i = 0; i < image4->h; i ++)
  {
    for(int j = 0; j < image4->w; j ++)
    {
      SDL_Color color;
      Uint32 pixel  = getpixel(image4, i, j);
      SDL_GetRGB(pixel, image4->format, &color.r, &color.g, &color.b);
      if(color.r == 0){donnee[3][i*image4->w + j] = 1;}
      else{donnee[3][i*image4->w + j] = 0;}
    }
  }

  double result[4] = {14,30,26,28};
  char print[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  Network *net = New_Network(420,2);
  Network_Add_Layer(net,400);
  Network_Add_Layer(net,62);

  for (size_t e = 0; e < 20; e ++)
  {
    Network_Train(net, donnee, result, 1, 1, 4);
  }
  save_values(net->layers[0], "Oweights", "Obiases");
  save_values(net->layers[1], "Oweights", "Obiases");
  get_values(net->layers[0], "Hweights", "Hbiases");
  get_values(net->layers[1], "Oweights", "Obiases");
  for(size_t t = 0; t < total_length; t ++)
    printf("character = %c\n", print[(int)Network_Predict(net, data[t])]);
  Network_Free(net);
  return 0;
}
