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
    double W = calcW(inputFile.getImages(),10, inputFile.getImageNum());

    Lsh *lsh = nullptr;
    HyperCube *hpcb = nullptr;

    string method = "Hypercube";
    if(method == "Lsh") {
        lsh = new Lsh(3, inputFile.getImageNum(), inputFile.getImages(),
            inputFile.getDimensions(), W, 6);
    }
    else if (method == "Hypercube") {
        hpcb = new HyperCube(inputFile.getDimensions(),
                            W,
                            pow(2, 32 / 3),
                            3,
                            inputFile.getImageNum(),
                            inputFile.getImages());
    }

    vector<Cluster *> * clusters = clustering("Classic",*inputFile.getImages(),
                                              inputFile.getImages(), numClusters,
                                              100, 4, lsh, hpcb);
    for (Cluster * clst: *clusters) {
        delete clst;
    }
    delete clusters;
}