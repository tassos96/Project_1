#include <iostream>

#include "Common/CmdArgumentsReader.h"

using namespace std;

int main(int argc, char const *argv[]) {
    int test;
    int test5;
    int test4;
    int test3;
    int test2;

    LshCmdVariables *lshCmdVariables = setLshArguments(argc, argv);
    bool termination;

    do {
        //Ask from user the path of dataset
        if (lshCmdVariables->inputFileName.empty()) {
            cout << "Insert path of dataset file: ";
            cin >> lshCmdVariables->inputFileName;
            cout << endl;
        }

//        cout << lshCmdVariables->inputFileName << endl;
//        cout << lshCmdVariables->K << endl;
//        cout << lshCmdVariables->L << endl;
//        cout << lshCmdVariables->N << endl;
//        cout << lshCmdVariables->R << endl;

        //Open dataset file
        ifstream inputFile(lshCmdVariables->inputFileName);
        if (!(inputFile.is_open())) {
            throw runtime_error("File " + string(lshCmdVariables->inputFileName) + " cannot be opened.");
        }

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

        //Open query file
        ifstream queryFile(lshCmdVariables->queryFileName);
        if (!queryFile.is_open()) {
            throw runtime_error("File " + string(lshCmdVariables->queryFileName) + " cannot be opened.");
        }

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
