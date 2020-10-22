#include "activation.h"

// Activation functions and derivatives

// SIGMOID

double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double dSigmoid(double x) { return x * (1 — x); }
