#include <iostream>
#include <tuple>
#include <chrono>


#include "Common/CmdArgumentsReader.h"
#include "Common/reader.h"
#include "Common/hashFuncs.h"
#include "Common/Distance.h"
#include "Algorithms/ExactNN.h"

using namespace std;
using namespace std::chrono;


int main(int argc, char const *argv[]) {

    LshCmdVariables *lshCmdVariables = setLshArguments(argc, argv);
    bool termination;

    do {
        //Ask from user the path of dataset
        if (lshCmdVariables->inputFileName.empty()) {
            cout << "Insert path of dataset file: ";
            cin >> lshCmdVariables->inputFileName;
            cout << endl;
        }

        cout << "----- Program arguments -----" << endl;
        cout << lshCmdVariables->inputFileName << endl;
        cout << lshCmdVariables->K << endl;
        cout << lshCmdVariables->L << endl;
        cout << lshCmdVariables->N << endl;
        cout << lshCmdVariables->R << endl;

        Reader inputFile(lshCmdVariables->inputFileName);
        //Structures creation here
        //.....
        //.....
        //.....
        //.....
        //End of structures creation

        //Ask from user the path of query file
        if (lshCmdVariables->queryFileName.empty()) {
            cout << "Insert path of query file: ";
            cin >> lshCmdVariables->queryFileName;
            cout << endl;
        }

        Reader queryFile(lshCmdVariables->queryFileName);

        //Ask from user the path of output file
        if (lshCmdVariables->outputFileName.empty()) {
            cout << "Insert path of output file: ";
            cin >> lshCmdVariables->outputFileName;
            cout << endl;
        }

        //Open output file
        ofstream outputFile;
        outputFile.open(lshCmdVariables->outputFileName);
        if (!outputFile.is_open()) {
            throw runtime_error("File " + string(lshCmdVariables->outputFileName) + " cannot be opened.");
        }

        //Nearest image tuple -> contains imagePtr, distance and total time of calculation
        tuple<Image*, int, microseconds> nearestImage;
        for(int i = 0; i < queryFile.getData()->size(); i++) {
            nearestImage = exactNN(queryFile.getData()->at(i), inputFile.getData());


            //Print some results
            cout << "Query_ID: " << queryFile.getData()->at(i)->getId() << endl;
            cout << "Nearest_ID: " << get<0>(nearestImage)->getId() << endl;
            cout << "distanceTrue: " << get<1>(nearestImage) << endl;
            cout << "tTrue: " << get<2>(nearestImage).count() << "μs" << endl;
        }

        //Ask user if he wants to exit or do another search
        cout << "1. Do another search." << endl;
        cout << "2. Terminate program." << endl;
        cout << "Insert your choice: ";
        int choice;
        cin >> choice;
        if(choice == 1) {
            lshCmdVariables->inputFileName = "";
            lshCmdVariables->queryFileName = "";
            lshCmdVariables->outputFileName = "";
            termination = false;
        }
        else
            termination = true;
    } while (!termination);

    delete lshCmdVariables;     //Free allocated memory
    return 0;
}
