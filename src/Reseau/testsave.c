#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Layer.h"
#include "savevalues.h"
#include "getvalues.h"

int main()
{
    printf("Layer 1\n");
    Layer *L = New_Layer(5,1);
    printf("\n\n");

    save_values(L,"Hweights", "Hbiases");

    printf("Layer 2 with random values\n");
    Layer *L2 = New_Layer(5,1);
    printf("\n\n");

    printf("get_values called -> Layer 2 new values: \n");
    get_values(L2,"Hweights", "Hbiases");

    for(int i = 0; i< 5; i++)
    {
        printf("%lf\n", *(L2->weights+i));
    }

    return 0;
}
