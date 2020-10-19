#include "weight.h"

#define RAND_MAX = 30

double init_weight()
{
    return ((double)rand(RAND_MAX) / (double)RAND_MAX);

}
