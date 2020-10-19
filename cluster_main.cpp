#include <iostream>
#include <tuple>
#include <chrono>

#include "Common/CmdArgumentsReader.h"

#include "Common/dataset.h"
#include "Clustering/algorithm.h"
#include "Clustering/Silhouette.h"
#include "Clustering/Config.h"

#define SAMPLE_PRCNT 10

using namespace std;
using namespace std::chrono;

int main(int argc, char const *argv[]) {
    ClusterCmdVariables *clusterCmdVariables = setClusterArguments(argc, argv);

    //Ask from user the path of dataset
    if (clusterCmdVariables->inputFileName.empty()) {
        cout << "Insert path of dataset file: ";
        cin >> clusterCmdVariables->inputFileName;
        cout << endl;
    }
    Dataset inputFile(clusterCmdVariables->inputFileName);

    //Ask from user the path of config file
    if (clusterCmdVariables->configFileName.empty()) {
        cout << "Insert path of dataset file: ";
        cin >> clusterCmdVariables->configFileName;
        cout << endl;
    }

    //Extract config file info
    Config* conf = extractConfInfo(clusterCmdVariables->configFileName);
    if(conf->numClusters < 1)
        throw runtime_error("Num of clusters must be > 0\n Please check "+ clusterCmdVariables->configFileName);

    //Calculate W
    double W = calcW(inputFile.getImages(),SAMPLE_PRCNT, inputFile.getImageNum());

    //Construct structure based on given method
    Lsh *lsh = nullptr;
    HyperCube *hpcb = nullptr;

    string method = clusterCmdVariables->method;
    if(method == "LSH") {
        lsh = new Lsh(conf->numHashTables, inputFile.getImageNum(), inputFile.getImages(),
            inputFile.getDimensions(), W, conf->numHashFunctions);
    }
    else if (method == "Hypercube") {
        hpcb = new HyperCube(inputFile.getDimensions(),
                            W,
                            pow(2, 32 / conf->cubeDim),
                            conf->cubeDim,
                            inputFile.getImageNum(),
                            inputFile.getImages());
    }

    //Start clustering algorithm
    //start timer
    high_resolution_clock::time_point startTimer = high_resolution_clock::now();

    //Run cluster algorithm
    vector<Cluster *> * clusters = clustering(method,*inputFile.getImages(),
                                              inputFile.getImages(), conf->numClusters,
                                              conf->imgsThresh, conf->probes, lsh, hpcb);

    //stop timer
    high_resolution_clock::time_point stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);

    //Calc duration
    string durResult = to_string(timerDuration.count() / 1000000.0) + "s";

    //Calculate silhouette
    vector<double> silhouetteRes = silhouette(*clusters);

    //Print cluster results
    printClstrRslts(clusterCmdVariables->outputFileName, clusterCmdVariables->method,
                    clusters, durResult, &silhouetteRes,
                    clusterCmdVariables->complete);

    //Free allocated memory
    for (Cluster * clst: *clusters) {
        delete clst;
    }
    delete clusters;
    delete clusterCmdVariables;
    delete conf;

    return 0;
}