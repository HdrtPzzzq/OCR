#include <math.h>


//MATRIX FUNCTIONS//


//arr1 * arr2 => nb row = arr1 row and col = arr2 col
double array[][] mat_mult(double arr1[], double arr2[])
{
    //c1 has to be eq to r2
    long r1 = sizeof(arr1[0]);
    long c1 = sizeof(arr1[1]);
    long r2 = sizeof(arr2[0]);
    long c2 = sizeof(arr2[1]);

    double mat[r1,c2];
    long mat_h = r1;
    long mat_l = c2;
    long a;
    long b;
    double res;


    for(long i = 0; i<mat_h; i++)
    {
        for(long j = 0; j<mat_l; j++)
        {
            a = 0;
           mat_multb = 0;
            res = 0;
            while a<c1 :
            {
                res += arr1[a][j] + arr[i][b];
                a+=1;
                b+=1;
            }
            mat[i][j]=res;
        }
    }

    return mat;
}


//SUM OF A MATRIX AND A NUMBER

double array[][] mat_nsum(double mat[][], double bias)
{
    long i = sizeof(array)(0);
    long j = sizeof(array)(1);

    for(long a = 0; a<i; a++)
    {
        for(long b = 0; b<j; b++)
        {
            mat[a][b] += bias; 
        }
    }

    return mat;
}




//ACTIVATION FUNCTION//

double array[][] pre_activation(double features[][], double weights[], double bias)
{
    return mat_nsum(mat_mult(weights, features), bias);
}

double activation(double z)
{
    return 1/(1-exp(-z));
}


double prime_sigmoid(double z)  //z is the result of the activation func
{
    return z*(1-z);
}

