#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double sigmoid(double x);
double sigmoid_prime(double x);
void random_weights(double *weight, size_t size, size_t input_size);
void random_biases(double *bias, size_t size);

#endif
