#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <err.h>

//#include "Layer.h"
#include "Network.h"
#include "fonctions.h"
//#include "savevalues.h"

#include <SDL/SDL.h>
#include "loadBMP.h"
#include "displayBMP.h"
#include "pixelBMP.h"
#include "grey_level.h"
#include "binarization.h"
#include <SDL/SDL_image.h>


int main()
{
    //char file[4][5] = { "1.bmp" , "2.bmp" , "3.bmp" , "4.bmp"};
    
    
    
    SDL_Surface *image1 = SDL_LoadBMP("1.bmp");
    binarization(image1, image1->format, 128);
    
    double data[4][image1->h * image1->w];        
    
    for(int i = 0; i < image1->h; i ++)
    {
        for(int j = 0; j < image1->w; j ++)
        {
            SDL_Color color;
            Uint32 pixel  = getpixel(image1, i, j);
            SDL_GetRGB(pixel, image1->format, &color.r, &color.g, &color.b);
            if(color.r == 0){data[0][i*image1->w + j] = 1;}
            else{data[0][i*image1->w + j] = 0;}
        }
    }

    SDL_Surface *image2 = SDL_LoadBMP("2.bmp");
    binarization(image2, image2->format, 128);
            
    for(int i = 0; i < image2->h; i ++)
    {
        for(int j = 0; j < image2->w; j ++)
        {
            SDL_Color color;
            Uint32 pixel  = getpixel(image2, i, j);
            SDL_GetRGB(pixel, image2->format, &color.r, &color.g, &color.b);
            if(color.r == 0){data[1][i*image2->w + j] = 1;}
            else{data[1][i*image2->w + j] = 0;}
        }
    }
    
    SDL_Surface *image3 = SDL_LoadBMP("3.bmp");
    binarization(image3, image3->format, 128);
            
    for(int i = 0; i < image3->h; i ++)
    {
        for(int j = 0; j < image3->w; j ++)
        {
            SDL_Color color;
            Uint32 pixel  = getpixel(image3, i, j);
            SDL_GetRGB(pixel, image3->format, &color.r, &color.g, &color.b);
            if(color.r == 0){data[2][i*image3->w + j] = 1;}
            else{data[2][i*image3->w + j] = 0;}
        }
    }
    
    SDL_Surface *image4 = SDL_LoadBMP("4.bmp");
    binarization(image4, image4->format, 128);
            
    for(int i = 0; i < image4->h; i ++)
    {
        for(int j = 0; j < image4->w; j ++)
        {
            SDL_Color color;
            Uint32 pixel  = getpixel(image4, i, j);
            SDL_GetRGB(pixel, image4->format, &color.r, &color.g, &color.b);
            if(color.r == 0){data[3][i*image4->w + j] = 1;}
            else{data[3][i*image4->w + j] = 0;}
        }
    }

    double result[4] = {14,30,26,28};
    
    Network *net = New_Network(420,2);
    Network_Add_Layer(net,400);
    Network_Add_Layer(net,62);

    double accuracy = Network_Evaluate(net, 4, data, result);
    printf("\nPerformance initiale: %lf\n\n",accuracy);

    for (size_t e = 0; e < 20; e ++)
    {
       Network_Train(net, data, result, 1, 1, 4);
        printf("------------------------------------\n");
        double accuracy = Network_Evaluate(net, 4, data, result);
        printf("Nouvelle performance : %lf\n\n",accuracy);
    }

    Network_Free(net);

}

