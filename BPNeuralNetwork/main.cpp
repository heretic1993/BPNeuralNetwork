//
//  main.cpp
//  BPNeuralNetwork
//
//  Created by Holden Wu on 4/8/15.
//  MIT LICENCE 
//

#include <iostream>
#include <vector>
#include <String>

#include "BPNeuralNetwork.h"

using namespace std;

int main(int argc, const char * argv[]) {
    string path;
    if (!strcmp(argv[1],"-l")) {
        if (argv[2]) {
            path = argv[2];
        }else{
            path = argv[0];
            path+="/traindata.txt";
        }
        FILE *stream;
        if ((stream=::fopen(path.c_str(), "r"))==NULL) {
            cout<<"Fail to read train data!"<<endl;
            exit(1);
        }
        vector<vector<double>> TrainData;
        vector<vector<double>> TrainResult;
        vector<double> input,output;
        double finput,foutput;
        int count=0;
        while (!feof(stream)) {
            for (int i=0; i<INPUTNODE; i++) {
                fscanf(stream,"%lf",&finput);
                input.push_back(finput);
            }
            TrainData.push_back(input);
            for (int i=0; i<OUTPUTNODE; i++) {
                fscanf(stream,"%lf",&foutput);
                output.push_back(foutput);
            }
            TrainResult.push_back(output);
            input.clear();
            output.clear();
            count++;
        }
        
        for(int i=0;i<TrainData.size();i++){
            cout<<"(";
            for (int b=0; b<TrainData[i].size(); b++) {
                cout<<TrainData[i][b]<<",";
            }
            cout<<")"<<endl;
        }
        
        if(TrainData.size()!=TrainResult.size()){
            cout<<"Data Error!"<<endl;
            exit(1);
        }
        
        cout<<"Successfully read data from file!"<<count<<" piece(s) train data!"<<endl;
        
        
        
        vector<double> classifyData;
        double a=1.119,b=-1.388;
        classifyData.push_back(a);
        classifyData.push_back(b);
        double outputResult[OUTPUTNODE];
        BPNeuralNetwork network;
        network.train(TrainData,TrainResult);
        
        network.classify(classifyData, outputResult);
    }
    
    return 0;
}
