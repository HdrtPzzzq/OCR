#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "fonctions.h"
#include "Network.h"

/******************************************************************************/

void Network_Init(Network *This, size_t input_dim, size_t number_layer)
{
    This->input_dim = input_dim;
    This->number_l = 0;
    This->layers = malloc(number_layer*sizeof(Layer*));  
}
/******************************************************************************/

Network* New_Network( size_t input_dim, size_t number_layer)
{
       Network *This = malloc(sizeof(Network));
       if(!This) return NULL;
       Network_Init(This, input_dim, number_layer);
       return This;
}
/******************************************************************************/

void Network_Add_Layer(Network *This, size_t size)
{
    if (This->number_l > 0)
        This->input_dim = This->layers[This->number_l-1]->size;
    else
        This->input_dim = This->input_dim;
    
    *(This->layers) = New_Layer(size, This->input_dim);

    This->number_l++;
}
/*******************************************************************************/

void Network_Feed_Forward(Network *This, double input_data[])
{
    double activation[This->input_dim];
    for (size_t d = 0; d < This->input_dim; d++)
        {
            activation[d] = input_data[d];
        }    
    for (size_t i = 0; i < This->number_l;i++)
    {
        Layer_Forward(This->layers[i],activation);
        for (size_t v = 0; v < This->layers[i]->size; v++)
        {
            activation[v] = This->layers[i]->activation_values[v];
        }
    }
}
/*******************************************************************************/

double  Network_Predict(Network *This, double input_data[])
{
    Network_Feed_Forward(This,input_data);
    double max = This->layers[This->number_l]->activation_values[0];
    for (size_t i = 1; i < 62; i++)
    {
        if (max < This->layers[This->number_l]->activation_values[i])
        {
            max = This->layers[This->number_l]->activation_values[i];
        }
    }
    return max;
}
/*******************************************************************************/

double  Network_Evaluate(Network *This, size_t len, double input_data[][784], double expected_output[])
{
    double results = 0;
    for(size_t i = 0; i < len; i++)
    {
        if (Network_Predict(This,input_data[i]) == expected_output[i])
        {
            results ++;
        }
    }
    double accuracy = results / len;
    return accuracy;
}
/*******************************************************************************/

void Network_Backprop(Network *This, double input_data[],double expected_output)
{
    double data[This->input_dim];
    for(size_t j = 0; j < This->input_dim; j++)
        {
            data[j] = input_data[j];
        } 
    for (size_t i = 0; i < This->number_l; i++)
    {
        Layer_Forward(This->layers[i],data);
        for(size_t j = 0; j < This->layers[i]->size; j++)
        {
            data[j] = *This->layers[i]->activation_values;
        }
    }

    double target[62];
    for (size_t x = 0; x < 62; x++){target[x] = 0;}
    target[(size_t)(expected_output)] = 1;
    double *delta[62];
    double **deltas[This->number_l];
    for(size_t x = 0; x < 62; x++)
    {
        *delta[x] = This->layers[This->number_l - 1]->activation_values[x] - target[x];
    }
    size_t k = 0;
    deltas[k] = delta;
    k++;

    for(size_t l = This->number_l - 2; l >= 0; l--)
    {
        Layer *layer = This->layers[l];
        Layer *next_layer = This->layers[l + 1];
        size_t len_delta = sizeof(delta)/sizeof(delta[0]);

        double transpose_weights[layer->size * layer->input_size];
        for(size_t x = 0 ; x < layer->size * layer->input_size; x++ )
        {
            transpose_weights[x] = layer->weights[x];
        }
        
        double *delta_p[layer->input_size * layer->size];
        transpose_mat(next_layer->weights,layer->size,layer->input_size,transpose_weights);
        mult_matrix(transpose_weights,layer->input_size,layer->size,*delta,len_delta,*delta_p);
        for(size_t i = 0 ; i< layer->size * layer->input_size; i++)
        {
            *delta_p[i] = *delta_p[i] * layer->activation_primes_values[i];
        }
        
        deltas[k] = delta_p;
        k++;
       
    }
    
    for (size_t t = 0; t < k/2; t++)
    {
        double *sto = delta[t];
        delta[t] = delta[k-1-t];
        delta[k-t-1] = sto;
    }

    for(size_t l = 0; l < This->number_l; l++)
    {
        for(size_t b = 0; b < This->layers[l]->size* This->layers[l]->input_size; b++)
        {
            This->layers[l]->gradient_weights[b] = This->layers[l]->activation_values[b] * *deltas[l][b];
        }
    }

}
/*******************************************************************************/

void Network_Train_Batch(Network *This, double input_data[][784], double expected_output[], double lr)
{    
    size_t len_Y = sizeof(*expected_output)/sizeof(double);
    for(size_t t = 0; t < len_Y; t++)
    {
        Network_Backprop(This,input_data[t],expected_output[t]);
    }

    for (size_t i = 0; i < This->number_l; i++)
    {
        double avg_weight_gradient[This->layers[i]->size*This->layers[i]->input_size];        
        double avg_bias_gradient[This->layers[i]->size];
        for (size_t j = 0; j < This->layers[i]->size * This->layers[i]->input_size; j++)
        {
            avg_weight_gradient[j] = This->layers[i]->gradient_weights[j]/len_Y;
        }
        for (size_t j = 0; j < This->layers[i]->size; j++)
        {
            avg_bias_gradient[j] = This->layers[i]->gradient_biases[j]/len_Y;
        }
        Layer_Update_All(This->layers[i],avg_weight_gradient,avg_bias_gradient,lr);
    }
}

/*******************************************************************************/

void Network_Train(Network *This, double input_data[][784], double expected_output[], 
        double steps, double lr, size_t batch_size)
{
    double n = sizeof(*(expected_output))/sizeof(expected_output[0]);
    for (size_t i = 0 ; i < steps; i++)
    {
        for(size_t batch_start = 0; batch_start < n; i += batch_size)
        {
            double X_batch[batch_size];
            double Y_batch[batch_size];
            for(size_t j = batch_start; j< batch_start + batch_size; j++)
            {
                X_batch[j] = *(input_data[j]);
                Y_batch[j] = expected_output[j];
                Network_Train_Batch(This,X_batch,Y_batch,lr);
            }
        }
    }
}
/*******************************************************************************/

void Network_Clear(Network *This)
{ 
    free(This->layers);
}
/******************************************************************************/
 
void Network_Free(Network *This){
        if(This) Network_Clear(This);
        free(This);        
        puts("Destruction du reseau .\n");
}
