#include <iostream>
#include <tuple>
#include <chrono>

#include "dataset.h"
#include "Clustering/algorithm.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    string inputFileName(argv[1]);
    Dataset inputFile(inputFileName);
    int numClusters = 5;
    vector<Cluster *> * clusters = clustering("lloyd",*inputFile.getImages(), numClusters);
    for (Cluster * clst: *clusters) {
        delete clst;
    }
    delete clusters;
}