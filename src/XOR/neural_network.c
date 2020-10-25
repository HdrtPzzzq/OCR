#include <stdio.h>
#include <stdlib.h>
#include "activation.h"

#define numInputs 2
#define numHiddenNodes 2
#define numOutputs 1

#define numTrainingSets 4

//======INIT PART======//

//NUMBER OF NEURONS
//in XOR we have 2 inputs, 2 neurons in hidden layer, and 1 output
//static const int numInputs = 2;         //2 inputs nodes
//static const int numHiddenNodes = 2;    //2 neurones
//static const int numOutputs = 1;        //1 output node

//LAYERS
//(1 hidden of 2 neurons, and 1 output layer of 1 node)
double hiddenLayer[numHiddenNodes];     //1 hidden layer of 2 neurons
double outputLayer[numOutputs];         //1 output layer with 1 neuron

//BIAS
double hiddenLayerBias[numHiddenNodes]; //2 neurons -> 2 biases
double outputLayerBias[numOutputs];     //1 ouput   -> 1 bias

//WEIGHTS
//the weights of a node is the are the values of the links between it and
//nodes of the precedent layer
double hiddenWeights[numInputs][numHiddenNodes];
double outputWeights[numHiddenNodes][numOutputs];



//======FUNCTIONS CALLS=======//

//ACTIVATION functions call
//If I want to change the type of activation function,
//I just have to change the call here instead of doing it for each call

double activation(double x)     //activation function
{
    return sigmoid(x);
}

double dactivation(double x)    //derivative of activation function
{
    return dSigmoid(x);
}

//returns an size_t between 0 and a
size_t RandomSizet(size_t a)
{
    return (size_t)rand() % a;
}


//Shuffle an int array
void RandArray(int arr[], int l)
{
    size_t nshuffle = l*3;  //shuffles array length*3 times
    size_t rand1;
    size_t rand2;
    int val;

    size_t i;
    for(i = 0; i < nshuffle; i++)
    {
        rand1 = RandomSizet(l);
        rand2 = RandomSizet(l);
        val = arr[rand1];
        arr[rand1] = arr[rand2];
        arr[rand2] = val;
    }

}


//=======TRAINING SET======//


//static const int numTrainingSets = 4;   //(0,0),(0,1),(1,0),(1,1) for XOR

//in each "tuple", the first element is for the first input node
//and the second element for the second input
double training_inputs[numTrainingSets][numInputs] = {{0.0f,0.0f},{1.0f,0.0f},
    {0.0f,1.0f},{1.0f,1.0f}};

//1 output, 4 training sets
double training_outputs[numTrainingSets][numOutputs] = { {0.0f},
    {1.0f},
    {1.0f},
    {0.0f} };

double trained_outputs[numTrainingSets];


// MAIN TRAINING LOOP

// Iterate through the entire training for a number of epochs
int main()
{
    int i,j,k,t,x;
    long Maxepoch = 2000;
    double lr = 0.5;//learning rate    
    double Error = 0.0;//print each 100 epoch
    for (long epoch=0; epoch < Maxepoch; epoch++)
    {


        // As per SGD(stochastic gradient descent),
        // we have to randomize the order of the training set
        int trainingSetOrder[] = {0,1,2,3};
        RandArray(trainingSetOrder, numTrainingSets);


        Error = 0;

        // For each epoch we use each element of the training set (4 for XOR)
        for (x=0; x<numTrainingSets; x++) 
        {
            i = trainingSetOrder[x];

            // Compute hidden layer activation
            for (j=0; j<numHiddenNodes; j++) 
            {
                double activation=hiddenLayerBias[j];
                for (k=0; k<numInputs; k++) 
                {
                    activation+=training_inputs[i][k]*hiddenWeights[k][j];
                }
                hiddenLayer[j] = sigmoid(activation);
            }

            // Compute output layer activation
            for (j=0; j<numOutputs; j++) 
            {
                double activation=outputLayerBias[j];
                for (k=0; k<numHiddenNodes; k++) 
                {
                    activation+=hiddenLayer[k]*outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);

            }

            trained_outputs[x] = outputLayer[0]; //get value for each case to print

            // Compute change in output weights
            double deltaOutput[numOutputs];
            for (j=0; j<numOutputs; j++) 
            {
                double dError = (training_outputs[i][j]-outputLayer[j]);
                deltaOutput[j] = dError*dSigmoid(outputLayer[j]);
            }

            // Compute change in hidden weights
            double deltaHidden[numHiddenNodes];
            for (j=0; j<numHiddenNodes; j++) 
            {
                double dError = 0.0f;
                for(k=0; k<numOutputs; k++) 
                {
                    dError+=deltaOutput[k]*outputWeights[j][k];
                }
                deltaHidden[j] = dError*dSigmoid(hiddenLayer[j]);
            }

            double targetout = training_outputs[i][0];
            double realout = outputLayer[0];

            Error += 0.5*(targetout-realout)*(targetout-realout);


            // Apply change in output weights
            for (j=0; j<numOutputs; j++)
            {
                outputLayerBias[j] += deltaOutput[j]*lr;
                for (k=0; k<numHiddenNodes; k++)
                {
                    outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
                }
            }


            // Apply change in hidden weights
            for (j=0; j<numHiddenNodes; j++)
            {
                hiddenLayerBias[j] += deltaHidden[j]*lr;
                for(k=0; k<numInputs; k++)
                {
                    hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
                }
            }

        }

        if( epoch%100 == 0 ) fprintf(stdout, "\nEpoch %-5lu :   Error = %f", epoch, Error) ;
        if( Error < 0.0004 ) break ;  /* stop learning when 'near enough' */
    }

    printf("\n");
    printf("Pat\t");
    for(i = 0; i<numInputs; i++)
    {
        printf("Input%-4d\t", i+1);
    }

    for(i = 0; i<numOutputs; i++)
    {
        printf("Target%-4d\t", i+1);
        printf("Output%-4d\t", i+1);
    }

    for(t = 0; t<numTrainingSets; t++)
    {
        printf("\n%d\t", t);

        for(i = 0; i<numInputs; i++)
        {
            printf("%f\t", training_inputs[t][i]);
        }

        printf("%f\t%f\t", training_outputs[t][0], trained_outputs[t]);

    }

    printf("\n");

    return 0;
}


