#include<stdlib.h>
#include<stdio.h>
#include<math.h>


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
/******************************************************************************/
void Network_Clear(Network *This)
{ 
    free(This->layers);
}
/******************************************************************************/
 
void Network_Free(Network *This)
{
        if(This) Network_Clear(This);
        free(This);        
        puts("Destruction du reseau .\n");
}
