//
//  BPNeuralNetwork.h
//  BPNeuralNetwork
//
//  Created by Holden Wu on 4/8/15.
//  MIT LICENCE 
//

#ifndef BPNeuralNetwork_BPNeuralNetwork_h
#define BPNeuralNetwork_BPNeuralNetwork_h

#define INPUTNODE 2
#define HIDENODE  5
#define OUTPUTNODE 1

#define COUST_P 0.5

#define LEARNING_RATE_WEIGHT_INPUT_HIDDEN 0.9
#define LEARNING_RATE_WEIGHT_HIDEEN_OUTPUT 0.9
#define LEARNING_RATE_NODE_HIDDEN 0.9
#define LEARNING_RATE_NODE_OUTPUT 0.9

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BPNeuralNetwork
{
protected:
    static int sampleNumber;
    double weight_Input_Hide[INPUTNODE][HIDENODE];
    double weight_Hide_Output[HIDENODE][INPUTNODE];
    double threshold_Hide[HIDENODE];
    double threshold_Output[OUTPUTNODE];
public:
    void train(vector<vector<double>> TrainData,vector<vector<double>> TrainResult);
    double* classify(vector<double> ClassifyData,double OutputLayerOutput[OUTPUTNODE]);
    BPNeuralNetwork();
    virtual ~BPNeuralNetwork();
};


#endif
