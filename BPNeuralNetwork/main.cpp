//
//  main.cpp
//  BPNeuralNetwork
//
//  Created by Holden WU on 4/8/15.
//  Copyright (c) 2015 Holden WU. All rights reserved.
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
        
        cout<<"Success!"<<count;
    }
    
    return 0;
}
