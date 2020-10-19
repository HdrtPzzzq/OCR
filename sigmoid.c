#include "sigmoid.h"

float sigmoid(float f)
{
    //1/(1-exp(-x))
}


float prime_sigmoid(float f)
{
    return sigmoid(f)*(1-sigmoid(f));
}

/*
float second_sigmoid(float f)
{
    return sigmoid(f)*(prime_sigmoid(f))+prime_sigmoid(f)*(1-sigmoid(f))
}
*/
