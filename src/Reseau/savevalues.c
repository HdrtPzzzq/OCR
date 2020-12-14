#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

#include "Layer.h"

void save_values(Layer* layer, char strw[20], char strb[20])
{
    FILE* Weights = NULL;
    Weights = fopen(strw, "w");

    if(Weights == NULL)
        return errx(1, "Weights file not found");

    for(size_t i = 0; i < layer->size * layer->input_size; i++)
    {
        fprintf(Weights, "%lf\n", *(layer->weights+i));
    }

    fclose(Weights);

    //**********************************************************

    FILE* Biases = NULL;
    Biases = fopen(strb, "w");

    if(Biases == NULL)
        return errx(1, "Biases file not found");

    for(size_t i = 0; i < layer->size; i++)
    {
        fprintf(Biases, "%lf\n", *(layer->biases+i));
    }

    fclose(Biases);
}
