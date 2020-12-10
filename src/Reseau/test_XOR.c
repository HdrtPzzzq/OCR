#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "Layer.h"
#include "fonctions.h"

int main()
{
    long epoch;
    long Maxepoch = 1000;
    double lr = 1;//learning rate    

    double data[4];
    data[0] = 1;
    data[1] = 0;
    data[2] = 1;
    data[3] = 0;
    double results[2];
    results[0] =

    Layer *hiddenlayer = New_Layer(2,2);
    Layer *outputlayer = New_Layer(1,2);

    for(epoch=0; epoch < Maxepoch; epoch++)
    {
      Layer_Forward(hiddenlayer,data);
      Layer_Forward(outputlayer,hiddenlayer->activation_values);
    
    }
}
