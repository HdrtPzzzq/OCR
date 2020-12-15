#ifndef LAYER_H
#define LAYER_H

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

typedef struct Layer
{
    size_t size; 
    size_t input_size;
    double *weights;
    double *biases;
    double *aggregation;
    double *activation_values;
    double *activation_primes_values;
    double *gradient_weights;
    double *gradient_biases;

}Layer;

void Layer_Init(Layer *This, size_t size, size_t input_size);

Layer* New_Layer(size_t size, size_t input_size);

void Layer_Aggregation(Layer *This, double training_inputs[]);

void Layer_Activation(Layer *This);

void Layer_Activation_prime(Layer *This);

void Layer_Forward(Layer *This, double data[]);

void Layer_Update_weights(Layer *This, double gradient[], double learning_rate);

void Layer_Update_biases(Layer *This, double gradient[], double learning_rate);

void Layer_Update_All(Layer *This, double gradient_weights[], double gradient_biases[]
        , double learning_rate);

void Layer_Clear(Layer *This);

void Layer_Free(Layer *This);

#endif 
