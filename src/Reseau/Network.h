#ifndef Network_H

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "Layer.h"

typedef struct Network
{
    size_t input_dim;
    size_t number_l;
    Layer **layers;

}Network;

void Network_Init(Network *This, size_t input_dim, size_t number_layer);

Network* New_Network(size_t input_dim, size_t number_layer);

void Network_Clear(Network *This);

void Network_Free(Network *This);

#endif 
