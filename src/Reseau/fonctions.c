#include <math.h>
#include <stdlib.h>
#include <stdio.h>


double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}
/******************************************************************************/

double sigmoid_prime(double x)
{
    return sigmoid(x) * (1.0 - sigmoid(x));
}
/******************************************************************************/

void random_weights(double *weight, size_t size, size_t input_size)
{
    for(double *p = weight; p < weight + size*input_size ; p++ )
    {
        double v = ((double)rand())/((double)RAND_MAX);
        *p = v;
        printf("|%lf;%lf|",v,*p);
    }
}
/******************************************************************************/

void random_biases(double *bias, size_t size)
{
    for(double *p = bias; p < bias + size ; p++ )
    {
        *p = ((double)rand())/((double)RAND_MAX);
    } 
}
/******************************************************************************/

