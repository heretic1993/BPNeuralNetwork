//
//  BPNeuralNetwork.cpp
//  BPNeuralNetwork
//
//  Created by Holden Wu on 4/8/15.
//  MIT LICENCE 
//

#include "BPNeuralNetwork.h"

void random_Init(double array[],int n){
    for (int i=0; i<n; i++) {
        array[i]=2*((double)rand()/RAND_MAX)-1;
    }
}

double sigmoid(double input){
    return 1.0/(1.0+exp(-input/COUST_P))+1;
}

BPNeuralNetwork::BPNeuralNetwork()
{
    srand((unsigned)time(NULL));
    random_Init((double*)weight_Input_Hide, INPUTNODE*HIDENODE);
    random_Init((double*)weight_Hide_Output,HIDENODE*OUTPUTNODE);
    random_Init(threshold_Hide, HIDENODE);
    random_Init(threshold_Output, OUTPUTNODE);
}

BPNeuralNetwork::~BPNeuralNetwork()
{
    
}

double* BPNeuralNetwork::classify(vector<double> ClassifyData,double OutputLayerOutput[OUTPUTNODE]){
    double HideNodeOutput[HIDENODE];
    for (int i=0; i<HIDENODE; i++) {
        double sum=0;
        for (int j=0; j<INPUTNODE; j++) {
            sum+=ClassifyData[j] * weight_Input_Hide[j][i];
        }
        HideNodeOutput[i]=sigmoid(sum);
    }
    
    for (int i=0; i<OUTPUTNODE; i++) {
        double sum=0;
        for (int j=0; j<HIDENODE; j++) {
            sum+=HideNodeOutput[j]*weight_Hide_Output[HIDENODE][OUTPUTNODE];
        }
        OutputLayerOutput[i]=sigmoid(sum);
    }
    
    for (int i=0; i<OUTPUTNODE; i++) {
        cout<<"Output Result is:"<<OutputLayerOutput[i]<<endl;
    }
    
    return OutputLayerOutput;
}

void BPNeuralNetwork::train(vector<vector<double>> TrainData,vector<vector<double>> TrainResult)
{
    double BPErr_output[OUTPUTNODE];
    double BPErr_hide[HIDENODE];
    for (int i=0; i<TrainData.size(); i++) {
        
        //do front propagation
        double HideNodeOutput[HIDENODE];
        for (int j=0; j<HIDENODE; j++) {
            double sum=0;
            for (int k=0; k<INPUTNODE; k++) {
                sum+=TrainData[i][k] * weight_Input_Hide[k][j];
            }
            HideNodeOutput[j]=sigmoid(sum);
        }
        
        double outputResult[OUTPUTNODE];
        for (int j=0; j<OUTPUTNODE; j++) {
            double sum=0;
            for (int k=0; k<HIDENODE; k++) {
                sum+=HideNodeOutput[k]*weight_Hide_Output[HIDENODE][OUTPUTNODE];
            }
            outputResult[j]=sigmoid(sum);
        }
        
        //calculate the err before refreshing
        double error=0;
        for (int j=0; j<OUTPUTNODE; j++) {
            error+=pow((TrainResult[i][j]-outputResult[j]),2);
        }
        cout<<"err:"<<error<<endl;
        
        for (int j=0 ; j<OUTPUTNODE ; j++) {
            BPErr_output[j]=(TrainResult[i][j]-outputResult[j])*outputResult[j]*(1-outputResult[j]);  //find the err
            
            //refresh the weight between hidden layer and output layer
            for (int k=0; k<HIDENODE; k++) {
                //cout<<"weight1:"<<"["<<k<<"]"<<weight_Hide_Output[k][j]<<"  ";
                weight_Hide_Output[k][j]+=LEARNING_RATE_WEIGHT_HIDEEN_OUTPUT*BPErr_output[j]*HideNodeOutput[k];
                //cout<<"weight1,after:"<<"["<<k<<"]"<<weight_Hide_Output[k][j]<<endl;
            }
        }
        
        for (int j=0; j<HIDENODE; j++) {
            BPErr_hide[j]=0;
            //back propagate the err to the hidden layer
            for (int k=0; k<OUTPUTNODE; k++) {
                BPErr_hide[j]+=BPErr_output[k]*weight_Hide_Output[j][k];
            }
            BPErr_hide[j]*=(HideNodeOutput[j]*(1-HideNodeOutput[j]));
            //refresh weights between input layer and hidden layer
            for (int k=0; k<INPUTNODE; k++) {
                //cout<<"weight2:"<<"["<<k<<"]"<<weight_Input_Hide[k][j]<<"  ";
                weight_Input_Hide[k][j]+=LEARNING_RATE_WEIGHT_INPUT_HIDDEN*BPErr_hide[j]*HideNodeOutput[j];
                //cout<<"weight2,after:"<<"["<<k<<"]"<<weight_Input_Hide[k][j]<<endl;
            }
        }
        //refresh nodes' threshold
        for (int j=0; j<OUTPUTNODE; j++) {
            threshold_Output[j]+=LEARNING_RATE_NODE_OUTPUT*BPErr_output[j];
        }
        for (int j=0; j<HIDENODE; j++) {
            threshold_Hide[j]+=LEARNING_RATE_NODE_HIDDEN*BPErr_hide[j];
        }
    }
}
