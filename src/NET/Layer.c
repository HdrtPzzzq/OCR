#include<stdlib.h>
#include<stdio.h>
#include<math.h>


#include "fonctions.h"
#include "Layer.h"

/******************************************************************************/

void Layer_Init(Layer *This, size_t size, size_t input_size)
{
    This->size = size;
    This->input_size = input_size;
    This->weights = malloc(size*input_size*sizeof(double));
    random_weights(This->weights, This->size, This->input_size);
    This->biases = malloc(size*sizeof(double));
    random_biases(This->biases,This->size);
    This->aggregation = malloc(size*sizeof(double));
    This->activation_values = malloc(size*sizeof(double));
    This->activation_primes_values = malloc(size*sizeof(double));
    This->gradient_weights = malloc(size*sizeof(double));
    This->gradient_biases = malloc(size*sizeof(double));
}
/******************************************************************************/

Layer* New_Layer(size_t size, size_t input_size)
{
       Layer *This = malloc(sizeof(Layer));
       if(!This){return NULL;}
       Layer_Init(This, size, input_size);
       return This;
}
/******************************************************************************/

void Layer_Aggregation(Layer *This, double training_inputs[])
{ 
    for (size_t j=0; j<This->size; j++) 
    {
        double activationval = This->biases[j];
        for (size_t k=0; k<This->input_size; k++) 
        {
            activationval += training_inputs[k]* This->weights[j*This->input_size + k];
        }
        This->aggregation[j] = activationval;    
    }
 }
/******************************************************************************/

void Layer_Activation(Layer *This)
{ 
    for (size_t j=0; j<This->size; j++) 
    {    
        This->activation_values[j] = sigmoid(This->aggregation[j]);
    }
}
/******************************************************************************/

void Layer_Activation_prime(Layer *This)
{
    for (size_t j = 0; j < This->size; j++)
    {
        This->activation_primes_values[j] = sigmoid_prime(This->aggregation[j]);
    }
}
/******************************************************************************/

void Layer_Forward(Layer *This, double data[])
{
    Layer_Aggregation(This, data);
    Layer_Activation(This);
    Layer_Activation_prime(This);
}
/******************************************************************************/

void Layer_Update_weights(Layer *This, double gradient[], double learning_rate)
{ 
    for(size_t i = 0; i< This->size; i++)
    {
        for(size_t j = 0; j< This->input_size; j++)
        {
            This->weights[i*This->input_size + j] -= 
                learning_rate * gradient[i];
        }
    }
}
/******************************************************************************/

void Layer_Update_biases(Layer *This, double gradient[], double learning_rate)
{ 
    for(size_t i = 0; i< This->size; i++)
    {
        This->biases[i] -= learning_rate * gradient[i];
    }
}

void Layer_Update_All(Layer *This, double gradient_weights[], double gradient_biases[]
        , double learning_rate)
{ 
    Layer_Update_weights(This,gradient_weights,learning_rate);
    Layer_Update_biases(This,gradient_biases,learning_rate);
}
/******************************************************************************/
 
void Layer_Clear(Layer *This)
{   
    free(This->weights);
    free(This->biases);
    free(This->activation_values);
    free(This->activation_primes_values);
}
/******************************************************************************/
 
void Layer_Free(Layer *This)
{
        if(This) Layer_Clear(This);
        free(This);        
        puts("\nDestruction de la layer .");
}



