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

void transpose_mat(double *M, size_t r, size_t c,double *dst)
{

    for(size_t i = 0; i<r; i++)
    {
        for(size_t j = 0; j<c; j++)
        {
            dst[j*r + i] = M[i*c+j];
        }
    }
}



/******************************************************************************/
void mult_matrix(double *M1, size_t r1, size_t c1, double *M2, size_t c2, double *dst)
{
    for(size_t i = 0; i<r1; i++)       //newM rows path (vertical)
    {
        for(size_t j=0; j<c2; j++)     //new M columns path (horizontal)
        {
            double sum = 0;
            for(size_t k = 0; k < c1; k++)
            {
                sum += M1[i*c1 + k] * M2[k*c2+j];
            }

            dst[i*r1+j] = sum;
        }
    }
}

