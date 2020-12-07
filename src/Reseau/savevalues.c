#include <stdio.h>
#include <stdlib.h>
#include <maths.h>
#include <err.h>

#include "Layer.h"
#include "savevalues.h"


void save_values(struct Layer* layer)
{
    FILE* Weights = NULL;
    Weights = fopen("weights", "w");

    if(HiddenWeights == NULL)
        return errx(1, "Weights file not found");

    for(size_t i = 0; i < layer->size * layer->input_size; i++)
    {
        fprintf(Weights, "%lf\n", *(layer->weights+i));
    }

    fclose Weights;

    //**********************************************************

    FILE* Biases = NULL;
    Biases = fopen("biases", "w");

    if(Biases == NULL)
        return errx(1, "Biases file not found");

    for(size_t i = 0; i < layer->size; i++)
    {
        fprintf(Biases, "%lf\n", *(layer->biases+i));
    }

    fclose Biases;
}
