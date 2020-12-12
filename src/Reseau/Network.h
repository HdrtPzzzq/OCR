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

void Network_Add_Layer(Network *This, size_t size);

void Network_Feed_Forward(Network *This, double input_data[]);

double  Network_Predict(Network *This, double input_data[]);

double  Network_Evaluate(Network *This, size_t len, double input_data[][784], 
        double expected_output[]);

void Network_Backprop(Network *This, double input_data[],double expected_output);

void Network_Train_Batch(Network *This, double input_data[][784], double expected_output[], 
        double lr);

void Network_Train(Network *This, double input_data[][784], double expected_output[], 
        double steps, double lr, size_t batch_size);

void Network_Clear(Network *This);

void Network_Free(Network *This);

#endif 
