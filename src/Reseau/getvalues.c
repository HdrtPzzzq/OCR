#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

#include "Layer.h"

void get_values(Layer* layer)
{
    //create a new neural network 


    FILE* Weights = NULL;
    Weights = fopen("weights", "r");

    if(Weights == NULL)
        return errx(1, "Weights file not found");

    //we want to get a double
    size_t size = 15;
    char* val = calloc(size, sizeof(char));


    for(size_t i = 0; i < layer->size * layer->input_size; i++)
    {
        fgets(val, size, Weights);
        strtok(val, "\n");
        layer->weights = atof(val);
    }

    fclose(Weights);

    //**********************************************************

    FILE* Biases = NULL;
    Biases = fopen("biases", "r");

    if(Biases == NULL)
        return errx(1, "Biases file not found");

    for(size_t i = 0; i < layer->size; i++)
    { 
        fgets(val, size, Biases);
        strtok(val, "\n");
        layer->biases = atof(val);
    }

    fclose(Biases);

}
