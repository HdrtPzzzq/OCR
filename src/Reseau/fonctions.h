#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double sigmoid(double x);
double sigmoid_prime(double x);
void random_weights(double *weight, size_t size, size_t input_size);
void random_biases(double *bias, size_t size);
void transpose_mat(double *M, size_t r, size_t c,double *dst);
void mult_matrix(double *M1, size_t r1, size_t c1, double *M2, size_t c2, double *dst)

#endif
