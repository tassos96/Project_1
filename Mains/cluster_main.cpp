#include <iostream>
#include <tuple>
#include <chrono>

#include "../Common/CmdArgumentsReader.h"
#include "../Common/dataset.h"
#include "../Clustering/algorithm.h"
#include "../Clustering/Silhouette.h"
#include "../Clustering/Config.h"

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
        cout << "Insert path of cluster config file: ";
        cin >> clusterCmdVariables->configFileName;
        cout << endl;
    }

    //Extract config file info
    Config* conf = extractConfInfo(clusterCmdVariables->configFileName);
    if(conf->numClusters < 1)
        throw runtime_error("Num of clusters must be > 0\n Please check "+ clusterCmdVariables->configFileName);

    int clust_threshold, w_smpl_prcnt, w_factor, approx_threshold;
    readParams(w_smpl_prcnt,w_factor, true,&approx_threshold,true,&clust_threshold);

    //Calculate W
    double W = calcW(inputFile.getImages(),w_smpl_prcnt, inputFile.getImageNum());

    cout << "W: " << w_factor*W << endl;

    //Construct structure based on given method
    Lsh *lsh = nullptr;
    HyperCube *hpcb = nullptr;

    string &method = clusterCmdVariables->method;
    if (method.empty()) {
        cout << "Insert method of cluster assignment(Classic or LSH or Hypercube): ";
        cin >> method;
        cout << endl;
    }
    if(method != "LSH" && method != "Hypercube" && method != "Classic")
        throw runtime_error("Wrong assignment method given!");

    if(method == "LSH") {
        lsh = new Lsh(conf->numHashTables, inputFile.getImageNum(), inputFile.getImages(),
            inputFile.getDimensions(), w_factor*W, conf->numHashFunctions);
    }
    else if (method == "Hypercube") {
        hpcb = new HyperCube(inputFile.getDimensions(),
                            w_factor*W,
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
                                              conf->imgsThresh, conf->probes, lsh, hpcb,
                                              approx_threshold, clust_threshold);

    //stop timer
    high_resolution_clock::time_point stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);

    //Calc duration
    string durResult = to_string(timerDuration.count() / 1e6) + "s";

    cout << "Calculating Silhouette" << endl;

    //Calculate silhouette
    vector<double> silhouetteRes = silhouette(*clusters);

    cout << "Finished calculating Silhouette" << endl;


    string &outputFile = clusterCmdVariables->outputFileName;
    if (outputFile.empty()) {
        cout << "Insert path of output file: ";
        cin >> outputFile;
        cout << endl;
    }
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

    if(method == "LSH")
        delete lsh;
    else if(method == "Hypercube")
        delete hpcb;

    return 0;
}