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


// MAIN TRAINING LOOP

// Iterate through the entire training for a number of epochs
int main()
{

    long Maxepoch = 3000;
    double lr = 0.1;                //learning rate
    for (long epoch=0; epoch < Maxepoch; epoch++)
    {

        double Error;//print each 100 epoch

        // As per SGD(stochastic gradient descent),
        // we have to randomize the order of the training set
        int trainingSetOrder[] = {0,1,2,3};
        RandArray(trainingSetOrder, numTrainingSets);

        // For each epoch we use each element of the training set (4 for XOR)
        for (int x=0; x<numTrainingSets; x++) 
        {
            int i = trainingSetOrder[x];

            // Compute hidden layer activation
            for (int j=0; j<numHiddenNodes; j++) 
            {
                double activation=hiddenLayerBias[j];
                for (int k=0; k<numInputs; k++) 
                {
                    activation+=training_inputs[i][k]*hiddenWeights[k][j];
                }
                hiddenLayer[j] = sigmoid(activation);
            }

            // Compute output layer activation
            for (int j=0; j<numOutputs; j++) 
            {
                double activation=outputLayerBias[j];
                for (int k=0; k<numHiddenNodes; k++) 
                {
                    activation+=hiddenLayer[k]*outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);
            }

            // Compute change in output weights
            double deltaOutput[numOutputs];
            for (int j=0; j<numOutputs; j++) 
            {
                double dError = (training_outputs[i][j]-outputLayer[j]);
                deltaOutput[j] = dError*dSigmoid(outputLayer[j]);
            }
            Error = ;

            // Compute change in hidden weights
            double deltaHidden[numHiddenNodes];
            for (int j=0; j<numHiddenNodes; j++) 
            {
                double dError = 0.0f;
                for(int k=0; k<numOutputs; k++) 
                {
                    dError+=deltaOutput[k]*outputWeights[j][k];
                }
                deltaHidden[j] = dError*dSigmoid(hiddenLayer[j]);
            }


            // Apply change in output weights
            for (int j=0; j<numOutputs; j++) 
            {
                outputLayerBias[j] += deltaOutput[j]*lr;
                for (int k=0; k<numHiddenNodes; k++) 
                {
                    outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
                }
            }


            // Apply change in hidden weights
            for (int j=0; j<numHiddenNodes; j++)
            {
                hiddenLayerBias[j] += deltaHidden[j]*lr;
                for(int k=0; k<numInputs; k++)
                {
                    hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
                }
            }

        }

        if( epoch%100 == 0 ) fprintf(stdout, "\nEpoch %-5lu :   Error = %f", epoch, Error) ;
        //if( Error < 0.0004 ) break ;  /* stop learning when 'near enough' */
    }

    return 0;
}


