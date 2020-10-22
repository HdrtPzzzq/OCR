#include "neural_network.h"

//number of neurons
static const int numInputs = 2;
static const int numHiddenNodes = 2;
static const int numOutputs = 1;

//layers
double hiddenLayer[numHiddenNodes];
double outputLayer[numOutputs];

//Bias
double hiddenLayerBias[numHiddenNodes];
double outputLayerBias[numOutputs];

//weights
double hiddenWeights[numInputs][numHiddenNodes];
double outputWeights[numhiddenNodes][numOutputs];


//TRAINING SET

static const int numTrainingSets = 4;
double training_inputs[numTrainingSets][numInputs] = { {0.0f,0.0f},{1.0f,0.0f},
                                                       {0.0f,1.0f},{1.0f,1.0f} };
double training_outputs[numTrainingSets][numOutputs] = { {0.0f},
                                                         {1.0f},
                                                         {1.0f},
                                                         {0.0f} };

// Iterate through the entire training for a number of epochs
for (int n=0; n < epochs; n++) {
  // As per SGD, shuffle the order of the training set
  int trainingSetOrder[] = {0,1,2,3};
  shuffle(trainingSetOrder,numTrainingSets);
  // Cycle through each of the training set elements
  for (int x=0; x<numTrainingSets; x++) {
    int i = trainingSetOrder[x];i

//j'essaye de recopier le site mais je bloque
//https://towardsdatascience.com/simple-neural-network-implementation-in-c-663f51447547
