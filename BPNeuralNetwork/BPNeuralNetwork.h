//
//  BPNeuralNetwork.h
//  BPNeuralNetwork
//
//  Created by 吳行方 on 4/8/15.
//  Copyright (c) 2015 Holden WU. All rights reserved.
//

#ifndef BPNeuralNetwork_BPNeuralNetwork_h
#define BPNeuralNetwork_BPNeuralNetwork_h

#define INPUTNODE 2
#define HIDENODE  5
#define OUTPUTNODE 1

#define LEARNING_RATE_WEIGHT_INPUT_HIDDEN 0.9
#define LEARNING_RATE_WEIGHT_HIDEEN_OUTPUT 0.9
#define LEARNING_RATE_NODE_HIDDEN 0.9
#define LEARNING_RATE_NODE_OUTPUT 0.9

#include <iostream>

using namespace std;

class BPNeuralNetwork
{
private:
    static int sampleNumber;
    
public:
    void train(double sample[sampleNumber][INPUTNODE+OUTPUTNODE]);
    BPNeuralNetwork(int sampleNumber);
    virtual ~BPNeuralNetwork();
    
};


#endif
