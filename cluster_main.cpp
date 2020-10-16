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

//    vector<unsigned char> * ptr = getMedian(inputFile.getImages(),inputFile.getDimensions()); // update step


    vector<Image *> centroid = kMeansPPlus(*inputFile.getImages(), 4);
    cout << "end" <<endl;
}
