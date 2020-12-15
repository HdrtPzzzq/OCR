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
    double input_dim;

    if (This->number_l > 0)
        input_dim = This->layers[This->number_l-1]->size;
    else
        input_dim = This->input_dim;
    
    This->layers[This->number_l] = New_Layer(size, input_dim);

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
    size_t index = 0;
    double max = This->layers[This->number_l-1]->activation_values[0];
    for (size_t i = 1; i < This->layers[This->number_l-1]->size; i++)
    {   
        if (max < This->layers[This->number_l-1]->activation_values[i])
        {
            max = This->layers[This->number_l-1]->activation_values[i];
            index = i;
        }
    }

    return index;
}
/*******************************************************************************/

double  Network_Evaluate(Network *This, size_t len, double input_data[][420], double expected_output[])
{
    double results = 0;

    for(size_t i = 0; i < len; i++)
    {   
        double p = Network_Predict(This,input_data[i]);
        double e = expected_output[i];
        if (p == e)
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
            data[j] = This->layers[i]->activation_values[j];
        }
    }

    double target[62];
    for (size_t x = 0; x < 62; x++){target[x] = 0;}
    target[(size_t)(expected_output)] = 1;
    double delta[62];
    double *deltas[This->number_l];    
    for(size_t x = 0; x < 62; x++)
    {
        delta[x] = This->layers[This->number_l - 1]->activation_values[x] - target[x];
    }
    size_t k = 0;
    deltas[k] = delta;
    k++;

    for(long int l = This->number_l - 2; l >= 0; l--)
    {
        Layer *layer = This->layers[l];
        Layer *next_layer = This->layers[l + 1];
        size_t len_delta = next_layer->size;

        double transpose_weights[layer->size * layer->input_size];
        for(size_t x = 0 ; x < next_layer->size * next_layer->input_size; x++ )
        {
            transpose_weights[x] = next_layer->weights[x];
        }

        
        double delta_p[next_layer->input_size];
        //transpose_mat(next_layer->weights,next_layer->size,next_layer->input_size,transpose_weights);
        mult_matrix(delta,1,len_delta,transpose_weights,next_layer->input_size,delta_p);
        for(size_t i = 0 ; i< next_layer->input_size; i++)
        {
            delta_p[i] = delta_p[i] * layer->activation_primes_values[i];
        }
        
        deltas[k] = delta_p;
        k++;      
    }
    /*for (size_t t = 0; t < k/2; t++)
    {
        doubl *sto = delta[t];
        delta[t] = delta[k-1-t];
        delta[k-t-1] = sto;
    }*/
    for(size_t l = 0; l < This->number_l; l++)
    {
        for(size_t b = 0; b < This->layers[l]->size; b++)
        {
            This->layers[l]->gradient_weights[b] += This->layers[l]->activation_values[b] * deltas[This->number_l -1 -l][b];
            This->layers[l]->gradient_biases[b] += deltas[This->number_l -1 -l][b];
        }
    }

}
/*******************************************************************************/

void Network_Train_Batch(Network *This, double input_data[][420], double expected_output[], 
        double lr, size_t len_Y)
{    
    for(size_t t = 0; t < len_Y; t++)
    {
        Network_Backprop(This,input_data[t],expected_output[t]);
    }

    for (size_t i = 0; i < This->number_l; i++)
    {
        double avg_weight_gradient[This->layers[i]->size];        
        double avg_bias_gradient[This->layers[i]->size];
        for (size_t j = 0; j < This->layers[i]->size ; j++)
        {
            avg_weight_gradient[j] = This->layers[i]->gradient_weights[j]/len_Y;
            avg_bias_gradient[j] = This->layers[i]->gradient_biases[j]/len_Y;
        }
        Layer_Update_All(This->layers[i],avg_weight_gradient,avg_bias_gradient,lr);
    }
}

/*******************************************************************************/

void Network_Train(Network *This, double input_data[][420], double expected_output[], 
        double steps, double lr, size_t batch_size)
{
    for (size_t i = 0 ; i < steps; i++)
    {
        /*for(size_t batch_start = 0; batch_start < n; batch_start  += batch_size)
        {
            double X_batch[batch_size][This->input_dim];
            double Y_batch[batch_size];
            for(size_t j = batch_start; j< batch_start + batch_size; j++)
            {
                for(size_t p = 0; p < This->input_dim; p++){X_batch[j][p] = input_data[j][p];}
                Y_batch[j] = expected_output[j];
                Network_Train_Batch(This,X_batch,Y_batch,lr,n);
            }
        }*/
        Network_Train_Batch(This,input_data,expected_output,lr,batch_size);        
    }
}
/*******************************************************************************/

void Network_Clear(Network *This)
{
    for (size_t i = 0; i<This->number_l;i++)
    {
        Layer_Free(This->layers[i]);
    }
    free(This->layers);
}
/******************************************************************************/
 
void Network_Free(Network *This)
{
        if(This) Network_Clear(This);
        free(This);        
        puts("\nDestruction du reseau .");
}
