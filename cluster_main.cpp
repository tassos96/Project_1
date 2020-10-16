#include <iostream>
#include <tuple>
#include <chrono>

#include "Common/CmdArgumentsReader.h"
#include "Common/dataset.h"
#include "Common/hashFuncs.h"
#include "Common/Utils.h"
#include "Clustering/UtilsCluster.h"
#include "Common/Distance.h"
#include "Algorithms/ExactNN.h"
#include "Algorithms/AproxNN.h"
#include "Algorithms/RangeSearch.h"
#include "Structures/HyperCube.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    string inputFileName(argv[1]);
    Dataset inputFile(inputFileName);
    vector<Image *> imgs(*inputFile.getImages());
//    vector<unsigned char> * ptr = getMedian(inputFile.getImages(),inputFile.getDimensions()); // update step
    cout << "size before" << imgs.size() << endl;
    vector<Image *> centroids = kMeansPPlus(&imgs, 5);
    cout << "size after" << imgs.size() << endl;
}