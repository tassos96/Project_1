#include <iostream>
#include <tuple>
#include <chrono>

#include "Common/CmdArgumentsReader.h"

#include "dataset.h"
#include "Clustering/algorithm.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char const *argv[]) {
//    ClusterCmdVariables *clusterCmdVariables = setClusterArguments(argc, argv);
//
//    //Ask from user the path of dataset
//    if (clusterCmdVariables->inputFileName.empty()) {
//        cout << "Insert path of dataset file: ";
//        cin >> clusterCmdVariables->inputFileName;
//        cout << endl;
//    }
//
//    Dataset inputFile(clusterCmdVariables->inputFileName);
//
//    //Ask from user the path of config file
//    if (clusterCmdVariables->configFileName.empty()) {
//        cout << "Insert path of dataset file: ";
//        cin >> clusterCmdVariables->configFileName;
//        cout << endl;
//    }


    string inputFileName(argv[1]);
    Dataset inputFile(inputFileName);
    int numClusters = 5;
    vector<Cluster *> * clusters = clustering("lloyd",*inputFile.getImages(), numClusters);
    for (Cluster * clst: *clusters) {
        delete clst;
    }
    delete clusters;
}