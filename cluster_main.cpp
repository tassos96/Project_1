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
    cout << numeric_limits<double>::min() << endl;
//    vector<unsigned char> * ptr = getMedian(inputFile.getImages(),inputFile.getDimensions()); // update step

    // initialization k-means++
    vector<double> t {1,2,3,4,5,6,7,8};
    double look = 1;
    for (int i = 0; i < 7; ++i) {
        int idx = binSearch(t,0,7,look);
        cout << "Index for " << look << " is " << idx << endl;
        look += 1.0;
    }

    vector<Image *> centroid = kMeansPPlus(*inputFile.getImages(), 4);
//    int idx = binSearch(t,0,7,4.5);
    int myints[] = {10,20,40,30,20,10,10,20};
    std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

    std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 40

    std::vector<int>::iterator up;//
    //low=std::lower_bound (v.begin(), v.end(), 13); //          ^
    up= std::upper_bound (v.begin(), v.end(), 40); //                   ^

//    std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
    std::cout << "upper_bound at position " << std::distance(v.begin(), up)  << '\n';

//    delete ptr;
//    cout << "1" << endl;
}
