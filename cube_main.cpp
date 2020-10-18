#include <iostream>
#include <tuple>
#include <chrono>

#include "Common/CmdArgumentsReader.h"
#include "Common/dataset.h"
#include "Common/hashFuncs.h"
#include "Common/Utils.h"
#include "Common/Distance.h"
#include "Algorithms/ExactNN.h"
#include "Algorithms/AproxNN.h"
#include "Algorithms/RangeSearch.h"
#include "Structures/HyperCube.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char const * argv[]) {

    CubeCmdVariables *cubeCmdVariables = setCubeArguments(argc, argv);
    bool termination;

    do{
        //Ask from user the path of dataset
        if (cubeCmdVariables->inputFileName.empty()) {
            cout << "Insert path of dataset file: ";
            cin >> cubeCmdVariables->inputFileName;
            cout << endl;
        }

        Dataset inputFile(cubeCmdVariables->inputFileName);
        //Structures creation
        double W = calcW(inputFile.getImages(),1, inputFile.getImageNum());
        cout << "W: " << W << endl;
        HyperCube hyperCube(inputFile.getDimensions(),
                            W,
                            pow(2,32/cubeCmdVariables->cubeDim),
                            cubeCmdVariables->cubeDim,
                            inputFile.getImageNum(),
                            inputFile.getImages());

        //Ask from user the path of query file
        if (cubeCmdVariables->queryFileName.empty()) {
            cout << "Insert path of query file: ";
            cin >> cubeCmdVariables->queryFileName;
            cout << endl;
        }

        Dataset queryFile(cubeCmdVariables->queryFileName);

        //Ask from user the path of output file
        if (cubeCmdVariables->outputFileName.empty()) {
            cout << "Insert path of output file: ";
            cin >> cubeCmdVariables->outputFileName;
            cout << endl;
        }

        //Open output file
        ofstream outputFile;
        outputFile.open(cubeCmdVariables->outputFileName);
        if (!outputFile.is_open()) {
            throw runtime_error("File " + string(cubeCmdVariables->outputFileName) + " cannot be opened.");
        }

        //Nearest image tuple -> contains imagePtr, distance and total time of calculation
        tuple<vector<tuple<int,Image*>>, microseconds> exactNearestImages;
        tuple<vector<tuple<int,Image*>>, microseconds> apprNearestImages;
        vector<tuple<int,Image*>> apprRangeSrchImages;
        for(int i = 0; i < queryFile.getImages()->size(); i++) {
            //Run exactNN algorithm
            exactNearestImages = exactNN(queryFile.getImages()->at(i),
                                         inputFile.getImages(),
                                         cubeCmdVariables->numNN);

            //Run approximateNN algorithm
            apprNearestImages = aproxKNN(queryFile.getImages()->at(i),
                                         &hyperCube,
                                         cubeCmdVariables->imgsThresh,
                                         cubeCmdVariables->probes,
                                         cubeCmdVariables->numNN);

            //Run approximate range search algorithm
            apprRangeSrchImages = aproxRangeSrch(queryFile.getImages()->at(i),
                                                 &hyperCube,
                                                 cubeCmdVariables->imgsThresh,
                                                 cubeCmdVariables->probes,
                                                 cubeCmdVariables->radius);

            //Print the algorithms results
            printResults(apprNearestImages,
                         exactNearestImages,
                         apprRangeSrchImages,
                         queryFile.getImages()->at(i),
                         false,
                         outputFile); // bool affects output message
        }

        outputFile.close(); //close output file
        //Ask user if he wants to exit or do another search
        cout << "1. Do another search." << endl;
        cout << "2. Terminate program." << endl;
        cout << "Insert your choice: ";
        int choice;
        cin >> choice;
        if(choice == 1) {
            cubeCmdVariables->inputFileName = "";
            cubeCmdVariables->queryFileName = "";
            cubeCmdVariables->outputFileName = "";
            termination = false;
        }
        else
            termination = true;
    }while (!termination);

    delete cubeCmdVariables;
    return 0;
}
