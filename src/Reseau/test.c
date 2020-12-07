#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "Layer.h"
#include "fonctions.h"

int main()
{
    double data[4];
    data[0] = 1;
    data[1] = 0;
    data[2] = 1;
    data[3] = 0;

    Layer *layer = New_Layer(2,2);
    printf("Layer cree\n");
    printf("****************************************************************\n");
    printf("Forward not Done:\n");
    printf("weights: \n");
    for (size_t i = 0;i<layer->size*layer->input_size;i++)
    {
        printf("%lf\n",*(layer->weights+i));
    }
    printf("biases: \n");
    for (size_t i = 0;i<layer->size;i++)
    {
        printf("%lf\n",*(layer->biases+i));
    }
    printf("activated: \n");
    for (size_t i = 0;i<layer->size;i++)
    {
        printf("%lf\n",*(layer->activation_values+i));
    }
    printf("activated prime: \n");
    for (size_t i = 0;i<layer->size;i++)
    {
        printf("%lf\n",*(layer->activation_primes_values+i));
    } 
    printf("****************************************************************\n");
    Layer_Forward(layer,data);
    printf("Forward Done:\n");
    printf("weights: \n");
    for (size_t i = 0;i<layer->size*layer->input_size;i++)
    {
        printf("%lf\n",*(layer->weights+i));
    }
    printf("biases: \n");
    for (size_t i = 0;i<layer->size;i++)
    {
        printf("%lf\n",*(layer->biases+i));
    }
    printf("activated: \n");
    for (size_t i = 0;i<layer->size;i++)
    {
        printf("%lf\n",*(layer->activation_values+i));
    }
    printf("activated prime: \n");
    for (size_t i = 0;i<layer->size;i++)
    {
        printf("%lf\n",*(layer->activation_primes_values+i));
    }  
    printf("****************************************************************\n");
    Layer_Free(layer);
}

