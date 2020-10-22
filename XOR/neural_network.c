#include "neural_network.h"
#include "activation.h"


//NUMBER OF NEURONS
//in XOR we have 2 inputs, 2 neurons in hidden layer, and 1 output
static const int numInputs = 2;
static const int numHiddenNodes = 2;
static const int numOutputs = 1;

//LAYERS
//(1 hidden of 2 neurons, and 1 output layer of 1 node)
double hiddenLayer[numHiddenNodes];
double outputLayer[numOutputs];

//BIAS
double hiddenLayerBias[numHiddenNodes];
double outputLayerBias[numOutputs];

//WEIGHTS
//the weights of a node is the are the values of the links between it and
//nodes of the precedent layer
double hiddenWeights[numInputs][numHiddenNodes];
double outputWeights[numhiddenNodes][numOutputs];


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


//TRAINING SET

static const int numTrainingSets = 4;   //(0,0),(0,1),(1,0),(1,1) for XOR

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

for (int n=0; n < epochs; n++) 
{
  // As per SGD(stochastic gradient descent),
  //shuffle the order of the training set
  int trainingSetOrder[] = {0,1,2,3};
  shuffle(trainingSetOrder,numTrainingSets);

  // Cycle through each of the training set elements
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



